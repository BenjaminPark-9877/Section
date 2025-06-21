#ifndef _BLOBCOLORING_H_
#define _BLOBCOLORING_H_

#pragma once

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif //_USERMACHRO_H_

#ifndef _BASICBONE_H_
#include "BasicBone.h"
#endif //_BASICBONE_H_

#include <stack>
#include <vector>
#include <utility>  // std::pair

class CBlobColoring : private CBasicBone
{
public:
    CBlobColoring(const unsigned char* InImg, int height, int width);
    virtual ~CBlobColoring();

    void fnBlobColoring(int distanceBound);

    struct BLOBDATA
    {
        short ltx, lty, rbx, rby;  // bounding box
        int n;                     // pixel count
        int pc;                    // boundary pixel count
        float cx, cy;              // centroid
        float r, g, b;             // average color
        float u02, u20, u11;       // moments
        float m, v;                // boundary mean radius and variance
    };

    int getBlobCount() const { return nBlob; }
    const std::vector<BLOBDATA>& getBlobData() const { return blobData; }
    const std::vector<int>& getColoringMap() const { return m_Coloring; }
    
    // Ư�� ��� �����͸� ��ȯ�ϴ� �Լ�
    BLOBDATA getBlobDataAt(int index) const
    {
        if (index >= 0 && index < nBlob)
            return blobData[index];
        else
            throw std::out_of_range("Index out of range");
    }

private:
    bool push(int vx, int vy);
    bool pop(int& vx, int& vy);

    void m_FindBoundary();
    void m_FindMoment();
    bool BoundDist(int rColor, int gColor, int bColor, int rVal, int gVal, int bVal) const;

    // ����� ����� ���� ���� ������ �� ���� ������
    CBlobColoring(const CBlobColoring&) = delete;  // ���� ������ ����
    CBlobColoring& operator=(const CBlobColoring&) = delete;  // ���� ���� ������ ����
    CBlobColoring(CBlobColoring&&) = delete;  // �̵� ������ ����
    CBlobColoring& operator=(CBlobColoring&&) = delete;  // �̵� ���� ������ ����

private:
    int width;
    int height;
    int distanceBound;
    size_t m_MaxStack;
    size_t rwsize;

    int nBlob;

    std::vector<int> m_Coloring;         // blob index per pixel
    std::vector<char> passImg;           // visited flag per pixel
    std::vector<unsigned char> m_InImg;  // input image buffer (BGR)
    std::vector<BLOBDATA> blobData;

    std::stack<std::pair<int, int>> m_stack; // stack for BFS
};

#endif //_BLOBCOLORING_H_
