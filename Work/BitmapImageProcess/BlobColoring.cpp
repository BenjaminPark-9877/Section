#include "pch.h"
#include "BlobColoring.h"
#include <cmath>
#include <algorithm>

#undef min
#undef max

#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)

CBlobColoring::CBlobColoring(const unsigned char* InImg, int height, int width)
    : width(width),
    height(height),
    distanceBound(0),
    m_MaxStack(static_cast<size_t>(height)* width),
    rwsize(WIDTHBYTES(24 * width)),
    nBlob(0)
{
    m_InImg.assign(InImg, InImg + rwsize * height);
    passImg.resize(height * width, 0);
    m_Coloring.resize(height * width, 0);
    blobData.reserve(height * width / 2); // 예상 blob 수의 여유 공간 확보
}

CBlobColoring::~CBlobColoring()
{
    passImg.clear();
    m_Coloring.clear();
    blobData.clear();
    while (!m_stack.empty()) m_stack.pop();
}

bool CBlobColoring::push(int vx, int vy)
{
    if (m_stack.size() >= m_MaxStack)
        return false;
    m_stack.emplace(vx, vy);
    return true;
}

bool CBlobColoring::pop(int& vx, int& vy)
{
    if (m_stack.empty())
        return false;
    auto p = m_stack.top();
    m_stack.pop();
    vx = p.first;
    vy = p.second;
    return true;
}

bool CBlobColoring::BoundDist(int rColor, int gColor, int bColor, int rVal, int gVal, int bVal) const
{
    return (std::abs(rColor - rVal) <= distanceBound) &&
        (std::abs(gColor - gVal) <= distanceBound) &&
        (std::abs(bColor - bVal) <= distanceBound);
}

void CBlobColoring::fnBlobColoring(int distBound)
{
    distanceBound = distBound;
    nBlob = 0;
    blobData.clear();

    const int maxPossibleBlobs = height * width / 4;  // 임의의 예산
    blobData.reserve(maxPossibleBlobs);

    for (int i = 0; i < height * width; ++i)
    {
        passImg[i] = 0;
        m_Coloring[i] = 0;
    }

    for (int i = 0; i < height; ++i)
    {
        int indexScanline = (height - i - 1) * static_cast<int>(rwsize);
        int indexImg = i * width;

        for (int j = 0; j < width; ++j)
        {
            if (passImg[indexImg + j] == 0)
            {
                ++nBlob;
                if (nBlob >= (int)blobData.size())
                    blobData.emplace_back();

                auto& blob = blobData[nBlob - 1];

                blob.ltx = blob.lty = std::max(height, width);
                blob.rbx = blob.rby = 0;
                blob.cx = blob.cy = 0.0f;
                blob.r = blob.g = blob.b = 0.0f;
                blob.n = 0;

                int rColor = m_InImg[indexScanline + 3 * j + 2];
                int gColor = m_InImg[indexScanline + 3 * j + 1];
                int bColor = m_InImg[indexScanline + 3 * j];

                push(i, j);
                passImg[indexImg + j] = 1;
                m_Coloring[indexImg + j] = nBlob;

                while (!m_stack.empty())
                {
                    int r, c;
                    pop(r, c);
                    int indexCur = r * width + c;

                    // 색상 픽셀 업데이트
                    int idxColor = (height - r - 1) * static_cast<int>(rwsize) + 3 * c;
                    int curR = m_InImg[idxColor + 2];
                    int curG = m_InImg[idxColor + 1];
                    int curB = m_InImg[idxColor];

                    blob.cx += r;
                    blob.cy += c;
                    blob.r += curR;
                    blob.g += curG;
                    blob.b += curB;

                    blob.ltx = std::min(blob.ltx, static_cast<short>(r));
                    blob.lty = std::min(blob.lty, static_cast<short>(c));
                    blob.rbx = std::max(blob.rbx, static_cast<short>(r));
                    blob.rby = std::max(blob.rby, static_cast<short>(c));
                    ++blob.n;

                    // 주변 8방향 검사
                    for (int m = r - 1; m <= r + 1; ++m)
                    {
                        for (int n = c - 1; n <= c + 1; ++n)
                        {
                            if (m < 0 || m >= height || n < 0 || n >= width)
                                continue;

                            int idxNeighbor = m * width + n;
                            if (passImg[idxNeighbor] != 0)
                                continue;

                            int idxNeighborColor = (height - m - 1) * static_cast<int>(rwsize) + 3 * n;
                            int nr = m_InImg[idxNeighborColor + 2];
                            int ng = m_InImg[idxNeighborColor + 1];
                            int nb = m_InImg[idxNeighborColor];

                            if (BoundDist(rColor, gColor, bColor, nr, ng, nb))
                            {
                                push(m, n);
                                passImg[idxNeighbor] = 1;
                                m_Coloring[idxNeighbor] = nBlob;
                            }
                        }
                    }
                }

                // 중심점 및 평균 색상 계산
                blob.cx /= blob.n;
                blob.cy /= blob.n;
                blob.r /= blob.n;
                blob.g /= blob.n;
                blob.b /= blob.n;
            }
        }
    }

    m_FindBoundary();
}

void CBlobColoring::m_FindMoment()
{
    for (int i = 0; i < nBlob; ++i)
    {
        blobData[i].u02 = blobData[i].u20 = blobData[i].u11 = 0.0f;
    }

    for (int i = 0; i < height; ++i)
    {
        int idxRow = i * width;
        for (int j = 0; j < width; ++j)
        {
            int blobIdx = m_Coloring[idxRow + j] - 1;
            if (blobIdx < 0 || blobIdx >= nBlob) continue;

            float dx = i - blobData[blobIdx].cx;
            float dy = j - blobData[blobIdx].cy;

            blobData[blobIdx].u11 += dx * dy;
            blobData[blobIdx].u02 += dx * dx;
            blobData[blobIdx].u20 += dy * dy;
        }
    }
}

void CBlobColoring::m_FindBoundary()
{
    for (int i = 0; i < nBlob; ++i)
    {
        blobData[i].m = 0.0f;
        blobData[i].v = 0.0f;
        blobData[i].pc = 0;
    }

    constexpr std::pair<int, int> directions[4] = { {-1,0}, {0,1}, {1,0}, {0,-1} };

    for (int i = 1; i < height - 1; ++i)
    {
        int idxRow = i * width;
        for (int j = 1; j < width - 1; ++j)
        {
            int blobIdx = m_Coloring[idxRow + j] - 1;
            if (blobIdx < 0 || blobIdx >= nBlob) continue;

            for (auto& d : directions)
            {
                int ni = i + d.first;
                int nj = j + d.second;
                int nBlobIdx = m_Coloring[ni * width + nj] - 1;

                if (blobIdx == nBlobIdx)
                    continue;

                float dist = std::sqrt((ni - blobData[blobIdx].cx) * (ni - blobData[blobIdx].cx) +
                    (nj - blobData[blobIdx].cy) * (nj - blobData[blobIdx].cy));

                blobData[blobIdx].m += dist;
                blobData[blobIdx].pc++;
            }
        }
    }

    for (int i = 0; i < nBlob; ++i)
    {
        if (blobData[i].pc > 0)
            blobData[i].m /= blobData[i].pc;
    }

    for (int i = 1; i < height - 1; ++i)
    {
        int idxRow = i * width;
        for (int j = 1; j < width - 1; ++j)
        {
            int blobIdx = m_Coloring[idxRow + j] - 1;
            if (blobIdx < 0 || blobIdx >= nBlob) continue;

            for (auto& d : directions)
            {
                int ni = i + d.first;
                int nj = j + d.second;
                int nBlobIdx = m_Coloring[ni * width + nj] - 1;

                if (blobIdx == nBlobIdx)
                    continue;

                float dist = std::sqrt((ni - blobData[blobIdx].cx) * (ni - blobData[blobIdx].cx) +
                    (nj - blobData[blobIdx].cy) * (nj - blobData[blobIdx].cy));
                float diff = dist - blobData[blobIdx].m;
                blobData[blobIdx].v += diff * diff;
            }
        }
    }

    for (int i = 0; i < nBlob; ++i)
    {
        if (blobData[i].pc > 1)
            blobData[i].v /= (blobData[i].pc - 1);
    }
}
