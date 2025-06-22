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
#include <mutex>      // ������ ������ ������ ���

class CUserBitmap : private CBasicBone
{
public:
    CUserBitmap() noexcept;
    ~CUserBitmap();

    // ���� ������ �� ���� ���� ������
    CUserBitmap(const CUserBitmap& rhs);
    CUserBitmap& operator=(const CUserBitmap& rhs);

    // �̵� ������ �� �̵� ���� ������ (noexcept ����)
    CUserBitmap(CUserBitmap&& rhs) noexcept;
    CUserBitmap& operator=(CUserBitmap&& rhs) noexcept;

    // ���ҽ� �ʱ�ȭ ����
    void Clear() noexcept;

    // �̹��� �� ��� ���� ������ (����� ����)
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

    // 1���� �̹��� ������ ������ (���� �˻� ������ �� ���� ����)
    unsigned char& operator[](size_t pos);
    const unsigned char operator[](size_t pos) const;

    // 2���� �̹��� ������ (����� ��忡���� ���� �˻�)
#ifdef _DEBUG
    unsigned char& operator()(size_t row, size_t col);
    const unsigned char operator()(size_t row, size_t col) const;
#else
    unsigned char& operator()(size_t row, size_t col) noexcept;
    const unsigned char operator()(size_t row, size_t col) const noexcept;
#endif

    // ��-const ���� (��¿�)
    std::vector<unsigned char>& GetImage();

    // �̹��� ������(����) ���� ���� (�б� ���� ����)
    const std::vector<unsigned char>& GetImage() const;

    // ���� ������ ������ ���� (�б� ���� ����)
    const unsigned char* Data() const noexcept;

    // �̹��� ���� �Լ��� (���� �� ��� ����ȭ)
    bool SetImage(const unsigned char* src, const BITMAPINFO* info);
    bool SetImage(const unsigned char* src, const BITMAPINFOHEADER* hdr, const BITMAPFILEHEADER* fhdr);
    bool SetImage(const CUserBitmap& rhs);

    // �̹����� ��� ���� �Լ�
    bool GetImage(unsigned char* dest, BITMAPINFO* info) const;
    bool GetImage(unsigned char* dest, BITMAPINFOHEADER* hdr, BITMAPFILEHEADER* fhdr) const;

protected:
    // ���� ��� ������ �Լ���
    bool SetBitmapInfo(const BITMAPINFO& info);
    bool SetBitmapInfo(const BITMAPINFO* info);
    bool SetBitmapInfoHeader(const BITMAPINFOHEADER& hdr);
    bool SetBitmapFileHeader(const BITMAPFILEHEADER& fhdr);

    // ���� �̹��� ������ ���� (���� �����ϰ� std::copy ���)
    void PushBitmapImageVector(const unsigned char* src, size_t size);

private:
    // �̹��� ���� ��� ��ü
    CBitmapInfo m_BmpInfo;
    CBitmapFileHeader m_DibHf;

    // �̹��� ������ ���� (�ʱ�ȭ ���´� optional�� ����)
    std::optional<std::vector<unsigned char>> m_optVecBmpImage;

    // (���� ��Ƽ������ ȯ�� ���) ���ؽ� ��� ���
    mutable std::mutex m_mutex;
};

#endif //_USERBITMAP_H_
