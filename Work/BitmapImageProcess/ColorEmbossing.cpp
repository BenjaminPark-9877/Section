/////** 
////*description   : ���� ������ �۾� ���� Ŭ���� ���� �ҽ� ����
////*               
////* 
////*/
#include "pch.h"
#include "ColorEmbossing.h"
#include "BlobColoring.h"
#include "ColorConv.h"

//*description   : ���� ������ �۾�
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

    // �̹��� ���� (���������� ��Ʈ�� ������ ����)
    if (!Set(*pCbmpElementsIn))
    {
        return;
    }

    // ������ ó�� �Լ� ȣ��
    ColorEmbossing(pCbmpElementsIn->GetImage().data(), m_pCbmpElements->GetImage().data(),
        (int)m_pCbmpElements->GetMaximumHeight(), (int)m_pCbmpElements->GetMaximumWidth());

    // ó���� �̹��� Ŭ������ ����
    CopyClipboard(m_pCbmpElements->GetImage().data(), (int)m_pCbmpElements->GetMaximumHeight(),
        (int)m_pCbmpElements->GetMaximumWidth(), 24);

    // UI ���� (��: �� ���� ���� �޽���)
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//*description   : ���� ������ ó�� (3x3 convolution)
//*@param input  : const unsigned char* InImg   - �Է� RGB ��Ʈ�� ������
//*@param input  : unsigned char* OutImg         - ��� RGB ��Ʈ�� ������ (ó�� ��� ����)
//*@param input  : int height                     - �̹��� ����
//*@param input  : int width                      - �̹��� �ʺ�
//*@return		 : ����
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

    // �����̿� ������� ����ũ ���� (�밢�� ����/���)
    Mask[0] = -1.0f;
    Mask[8] = 1.0f;

    int n = (winsize - 1) >> 1;  // ������ ���� ũ��

    // ������ ���� ����
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

            // �߰��� ���� �� Ŭ�� (0~255)
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
