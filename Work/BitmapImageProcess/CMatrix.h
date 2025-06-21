// 
/////** 
////*description   : CMatrix.h / 행렬 클래스 정의 파일
////* 
////*/
#pragma once
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <type_traits>
#include <tuple>
#include "BasicBone.h"

namespace UserDefinedMatrix {

    constexpr double EPSILON = 1e-10; // 허용 오차 범위

    template<typename T, typename Enable = void>
    class CMatrix {

    private:
        std::vector<T> m_vData;
        size_t m_nRows;
        size_t m_nCols;

        void bounds_check(size_t row, size_t col) const {
            if (row >= m_nRows || col >= m_nCols) {
                throw std::out_of_range("CMatrix index out of bounds");
            }
        }

        // 행 스왑 함수 (행렬 내 행 위치 변경)
        void swap_rows(size_t row1, size_t row2) {
            for (size_t col = 0; col < m_nCols; ++col) {
                std::swap((*this)(row1, col), (*this)(row2, col));
            }
        }

    public:
        explicit CMatrix(size_t rows = 0, size_t cols = 0, const T& defaultValue = T())
            : m_vData(rows* cols, defaultValue), m_nRows(rows), m_nCols(cols) {
            // Initialize()가 필요 없으므로 제거
        }

        // 역행렬 계산 (가우스-조던 소거법, 정사각행렬만)
        CMatrix<T> inverse() const {
            if (!is_square())
                throw std::runtime_error("정사각 행렬만 역행렬 계산 가능");

            size_t n = m_nRows;
            CMatrix<T> result(n, n, T(0));
            CMatrix<T> temp(*this);

            // 단위행렬 생성
            for (size_t i = 0; i < n; ++i)
                result(i, i) = T(1);

            for (size_t i = 0; i < n; ++i) {
                // 피벗 찾기 (partial pivoting 적용)
                T pivot = temp(i, i);
                if (std::abs(pivot) < EPSILON) {
                    bool found_non_zero_pivot = false;
                    for (size_t j = i + 1; j < n; ++j) {
                        if (std::abs(temp(j, i)) > EPSILON) {
                            swap_rows(i, j);  // 행 스왑
                            swap_rows(i, j);  // 결과 행렬에도 적용
                            pivot = temp(i, i);
                            found_non_zero_pivot = true;
                            break;
                        }
                    }
                    if (!found_non_zero_pivot)
                        throw std::runtime_error("역행렬 계산 중 피벗이 0에 가까움");
                }

                // 피벗 행 나누기
                for (size_t j = 0; j < n; ++j) {
                    temp(i, j) /= pivot;
                    result(i, j) /= pivot;
                }

                // 다른 행에서 피벗 열 제거
                for (size_t k = 0; k < n; ++k) {
                    if (k == i) continue;
                    T factor = temp(k, i);
                    for (size_t j = 0; j < n; ++j) {
                        temp(k, j) -= factor * temp(i, j);
                        result(k, j) -= factor * result(i, j);
                    }
                }
            }

            return result;
        }

        // 복사 생성자
        CMatrix(const CMatrix& rhs) {
            m_nRows = rhs.m_nRows;
            m_nCols = rhs.m_nCols;
            m_vData = rhs.m_vData;
        }

        // 복사 대입 연산자
        CMatrix& operator=(const CMatrix& rhs) {
            if (this == &rhs) return *this;
            m_nRows = rhs.m_nRows;
            m_nCols = rhs.m_nCols;
            m_vData = rhs.m_vData;
            return *this;
        }

        // 이동 생성자
        CMatrix(CMatrix&& rhs) noexcept
            : m_vData(std::move(rhs.m_vData)), m_nRows(rhs.m_nRows), m_nCols(rhs.m_nCols) {
            rhs.m_nRows = 0;
            rhs.m_nCols = 0;
        }

        // 이동 대입 연산자
        CMatrix& operator=(CMatrix&& rhs) noexcept {
            if (this != &rhs) {
                m_vData = std::move(rhs.m_vData);
                m_nRows = rhs.m_nRows;
                m_nCols = rhs.m_nCols;
                rhs.m_nRows = 0;
                rhs.m_nCols = 0;
            }
            return *this;
        }

        // 1차원 인덱스 접근용 operator[]
        T& operator[](size_t index) {
            return m_vData[index];
        }

        const T& operator[](size_t index) const {
            return m_vData[index];
        }

        bool Cleanup() {
            m_vData.clear();
            m_nRows = 0;
            m_nCols = 0;
            return true;
        }

        inline bool clear() { return Cleanup(); }

        size_t get_rows() const noexcept { return m_nRows; }
        size_t get_columns() const noexcept { return m_nCols; }

        T& operator()(size_t row, size_t col) {
            bounds_check(row, col);
            return m_vData[row * m_nCols + col];
        }

        const T& operator()(size_t row, size_t col) const {
            bounds_check(row, col);
            return m_vData[row * m_nCols + col];
        }

        bool empty() const noexcept { return m_vData.empty(); }
        bool is_square() const noexcept { return m_nRows == m_nCols && m_nRows > 0; }

        T* data() noexcept { return m_vData.data(); }
        const T* data() const noexcept { return m_vData.data(); }

        std::vector<T>& vector_data(void) noexcept { return m_vData; }
        const std::vector<T>& vector_data(void) const noexcept { return m_vData; }

        // 행렬 크기 조정. 단 기존 자료 전체 초기화
        bool resize(size_t szRows, size_t szCols) {
            if (m_nRows != szRows || m_nCols != szCols) {
                m_vData.clear();
                m_nRows = szRows;
                m_nCols = szCols;
                m_vData.resize(szRows * szCols);
                return true;
            }
            return false;
        }

        // 행렬 크기 조정. 단 기존 자료는 일부라도 보존
        bool resize_and_preserve(size_t newRows, size_t newCols) {
            if (newRows == m_nRows && newCols == m_nCols)
                return false;

            std::vector<T> newData(newRows * newCols, T());

            size_t minRows = std::min(m_nRows, newRows);
            size_t minCols = std::min(m_nCols, newCols);

            for (size_t r = 0; r < minRows; ++r) {
                for (size_t c = 0; c < minCols; ++c) {
                    newData[r * newCols + c] = (*this)(r, c);
                }
            }

            m_vData = std::move(newData);
            m_nRows = newRows;
            m_nCols = newCols;

            return true;
        }

        // Scalar 연산자
        CMatrix& operator+=(const T& rhs) {
            for (auto& val : m_vData) val += rhs;
            return *this;
        }
        CMatrix& operator-=(const T& rhs) {
            for (auto& val : m_vData) val -= rhs;
            return *this;
        }
        CMatrix& operator*=(const T& rhs) {
            for (auto& val : m_vData) val *= rhs;
            return *this;
        }
        CMatrix& operator/=(const T& rhs) {
            if (std::abs(rhs) < EPSILON) throw std::invalid_argument("Division by zero");
            for (auto& val : m_vData) val /= rhs;
            return *this;
        }

        // Matrix 연산자
        CMatrix& operator+=(const CMatrix& rhs) {
            if (m_nRows != rhs.m_nRows || m_nCols != rhs.m_nCols)
                throw std::invalid_argument("Matrix dimension mismatch for addition");
            for (size_t i = 0; i < m_vData.size(); ++i)
                m_vData[i] += rhs.m_vData[i];
            return *this;
        }
        CMatrix& operator-=(const CMatrix& rhs) {
            if (m_nRows != rhs.m_nRows || m_nCols != rhs.m_nCols)
                throw std::invalid_argument("Matrix dimension mismatch for subtraction");
            for (size_t i = 0; i < m_vData.size(); ++i)
                m_vData[i] -= rhs.m_vData[i];
            return *this;
        }
        CMatrix& operator*=(const CMatrix& rhs) {
            if (m_nCols != rhs.m_nRows)
                throw std::invalid_argument("Matrix dimension mismatch for multiplication");
            CMatrix result(m_nRows, rhs.m_nCols, T(0));
            for (size_t i = 0; i < m_nRows; ++i)
                for (size_t j = 0; j < rhs.m_nCols; ++j)
                    for (size_t k = 0; k < m_nCols; ++k)
                        result(i, j) += (*this)(i, k) * rhs(k, j);
            *this = std::move(result);
            return *this;
        }

        bool operator==(const CMatrix& rhs) const {
            if (m_nRows != rhs.m_nRows || m_nCols != rhs.m_nCols) return false;
            for (size_t i = 0; i < m_vData.size(); ++i)
                if (std::abs(m_vData[i] - rhs.m_vData[i]) > EPSILON)
                    return false;
            return true;
        }

        // 행렬 전치
        CMatrix transpose() const {
            CMatrix<T> result(m_nCols, m_nRows);
            for (size_t i = 0; i < m_nRows; ++i)
                for (size_t j = 0; j < m_nCols; ++j)
                    result(j, i) = (*this)(i, j);
            return result;
        }

        // 스트림 입력/출력
        friend std::ostream& operator<<(std::ostream& os, const CMatrix& matrix) {
            for (size_t i = 0; i < matrix.m_nRows; ++i) {
                for (size_t j = 0; j < matrix.m_nCols; ++j)
                    os << matrix(i, j) << " ";
                os << "\n";
            }
            return os;
        }
    };
}