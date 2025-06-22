#ifndef _USERBITMAP_H_
#define _USERBITMAP_H_

#pragma once

#include "BasicBone.h"
#include "UserMachro.h"
#include "BitmapInfo.h"
#include "BitmapFileHeader.h"

#include <vector>
#include <cstddef>
#include <stdexcept>
#include <optional>
#include <algorithm>  // std::copy
#include <mutex>      // 잠재적 스레드 안전성 대비

class CUserBitmap : private CBasicBone
{
public:
    CUserBitmap() noexcept;
    ~CUserBitmap();

    // 복사 생성자 및 복사 대입 연산자
    CUserBitmap(const CUserBitmap& rhs);
    CUserBitmap& operator=(const CUserBitmap& rhs);

    // 이동 생성자 및 이동 대입 연산자 (noexcept 보장)
    CUserBitmap(CUserBitmap&& rhs) noexcept;
    CUserBitmap& operator=(CUserBitmap&& rhs) noexcept;

    // 리소스 초기화 해제
    void Clear() noexcept;

    // 이미지 및 헤더 정보 접근자 (상수형 포함)
    const BITMAPINFO* GetBitmapInfo() const noexcept;
    const BITMAPINFOHEADER* GetBitmapInfoHeader() const noexcept;
    bool GetBitmapInfoHeader(BITMAPINFOHEADER& out) const noexcept;
    bool GetBitmapInfoHeader(BITMAPINFOHEADER* out) const noexcept;

    const BITMAPFILEHEADER* GetBitmapFileHeader() const noexcept;
    bool GetBitmapFileHeader(BITMAPFILEHEADER& out) const noexcept;
    bool GetBitmapFileHeader(BITMAPFILEHEADER* out) const noexcept;

    unsigned long GetMaximumWidth() const noexcept;
    unsigned long GetMaximumHeight() const noexcept;
    unsigned long GetRwSize() const noexcept;
    int GetBitCount() const noexcept;
    unsigned long GetTotalSize() const noexcept;

    // 1차원 이미지 데이터 접근자 (범위 검사 릴리즈 시 제거 가능)
    unsigned char& operator[](size_t pos);
    const unsigned char operator[](size_t pos) const;

    // 2차원 이미지 접근자 (디버그 모드에서만 범위 검사)
#ifdef _DEBUG
    unsigned char& operator()(size_t row, size_t col);
    const unsigned char operator()(size_t row, size_t col) const;
#else
    unsigned char& operator()(size_t row, size_t col) noexcept;
    const unsigned char operator()(size_t row, size_t col) const noexcept;
#endif

    // 비-const 버전 (출력용)
    std::vector<unsigned char>& GetImage();

    // 이미지 데이터(벡터) 직접 접근 (읽기 전용 권장)
    const std::vector<unsigned char>& GetImage() const;

    // 원시 데이터 포인터 접근 (읽기 전용 권장)
    const unsigned char* Data() const noexcept;

    // 이미지 설정 함수들 (복사 및 헤더 동기화)
    bool SetImage(const unsigned char* src, const BITMAPINFO* info);
    bool SetImage(const unsigned char* src, const BITMAPINFOHEADER* hdr, const BITMAPFILEHEADER* fhdr);
    bool SetImage(const CUserBitmap& rhs);

    // 이미지와 헤더 복사 함수
    bool GetImage(unsigned char* dest, BITMAPINFO* info) const;
    bool GetImage(unsigned char* dest, BITMAPINFOHEADER* hdr, BITMAPFILEHEADER* fhdr) const;

protected:
    // 내부 헤더 설정용 함수들
    bool SetBitmapInfo(const BITMAPINFO& info);
    bool SetBitmapInfo(const BITMAPINFO* info);
    bool SetBitmapInfoHeader(const BITMAPINFOHEADER& hdr);
    bool SetBitmapFileHeader(const BITMAPFILEHEADER& fhdr);

    // 내부 이미지 데이터 복사 (예외 안전하게 std::copy 사용)
    void PushBitmapImageVector(const unsigned char* src, size_t size);

private:
    // 이미지 정보 헤더 객체
    CBitmapInfo m_BmpInfo;
    CBitmapFileHeader m_DibHf;

    // 이미지 데이터 저장 (초기화 상태는 optional로 관리)
    std::optional<std::vector<unsigned char>> m_optVecBmpImage;

    // (추후 멀티스레드 환경 대비) 뮤텍스 잠금 멤버
    mutable std::mutex m_mutex;
};

#endif //_USERBITMAP_H_
