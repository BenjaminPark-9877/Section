/////** 
////*description   : 색상 엠보싱 작업 수행 클래스 정의 소스 파일
////*               
////* 
////*/
#include "pch.h"
#include "ColorEmbossing.h"
#include "BlobColoring.h"
#include "ColorConv.h"

//*description   : 색상 엠보싱 작업
//*@param input  : CUserBitmap* pCbmpElementsIn
//*@param input  :   
//*@param input  :  
//*@param input  :  
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CColorEmbossing::Process(const CUserBitmap* pCbmpElementsIn)
{
    if (!pCbmpElementsIn || !pCbmpElementsIn->GetImage().data())
    {
        return;
    }

    if (pCbmpElementsIn->GetBitmapInfo() == NULL)
    {
        return;
    }

    if (pCbmpElementsIn->GetBitCount() != 24)
    {
        return;
    }

    // 이미지 설정 (내부적으로 비트맵 데이터 복사)
    if (!Set(*pCbmpElementsIn))
    {
        return;
    }

    // 엠보싱 처리 함수 호출
    ColorEmbossing(pCbmpElementsIn->GetImage().data(), m_pCbmpElements->GetImage().data(),
        (int)m_pCbmpElements->GetMaximumHeight(), (int)m_pCbmpElements->GetMaximumWidth());

    // 처리된 이미지 클립보드 복사
    CopyClipboard(m_pCbmpElements->GetImage().data(), (int)m_pCbmpElements->GetMaximumHeight(),
        (int)m_pCbmpElements->GetMaximumWidth(), 24);

    // UI 갱신 (예: 새 파일 생성 메시지)
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//*description   : 색상 엠보싱 처리 (3x3 convolution)
//*@param input  : const unsigned char* InImg   - 입력 RGB 비트맵 데이터
//*@param input  : unsigned char* OutImg         - 출력 RGB 비트맵 데이터 (처리 결과 저장)
//*@param input  : int height                     - 이미지 높이
//*@param input  : int width                      - 이미지 너비
//*@return		 : 없음
//*/
void CColorEmbossing::ColorEmbossing(const unsigned char* InImg, unsigned char* OutImg, int height, int width)
{
    if (!InImg || !OutImg || height <= INVALID_IMAGE_SIZE || width <= INVALID_IMAGE_SIZE)
    {
        return;
    }

    size_t rwsize = WIDTHBYTES(24 * width);

    int winsize = 3;
    std::vector<float> Mask;
    InitializeMask(Mask, winsize);

    // 엠보싱용 컨볼루션 마스크 설정 (대각선 음수/양수)
    Mask[0] = -1.0f;
    Mask[8] = 1.0f;

    int n = (winsize - 1) >> 1;  // 윈도우 절반 크기

    // 엠보싱 필터 적용
    for (int i = n; i < height - n; i++)
    {
        int index1 = i * (int)rwsize;
        for (int j = n; j < width - n; j++)
        {
            double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;

            for (int k = -n; k <= n; k++)
            {
                int index2 = (i + k) * (int)rwsize;
                int index3 = (k + n) * winsize;

                for (int l = -n; l <= n; l++)
                {
                    sum1 += (double)(InImg[index2 + 3 * (j + l)]) * (double)(Mask[index3 + l + n]);
                    sum2 += (double)(InImg[index2 + 3 * (j + l) + 1]) * (double)(Mask[index3 + l + n]);
                    sum3 += (double)(InImg[index2 + 3 * (j + l) + 2]) * (double)(Mask[index3 + l + n]);
                }
            }

            // 중간값 보정 및 클립 (0~255)
            sum1 += 128.0; sum2 += 128.0; sum3 += 128.0;
            CLIP<double>(sum1, 0.0, 255.0);
            CLIP<double>(sum2, 0.0, 255.0);
            CLIP<double>(sum3, 0.0, 255.0);

            OutImg[index1 + 3 * j] = (unsigned char)sum1;
            OutImg[index1 + 3 * j + 1] = (unsigned char)sum2;
            OutImg[index1 + 3 * j + 2] = (unsigned char)sum3;
        }
    }
}
