/////** 
////*description   :  �۾� ���� Ŭ���� �ҽ� ����
////*               
////* 
////*/
#include "pch.h"
#include "ChannelsplitRgb.h"

#include "BlobColoring.h"
#include "ColorConv.h"

//*description   :  
//*@param input  : CUserBitmap* pCbmpElementsIn
//*@param input  :   
//*@param input  :  
//*@param input  :  
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CChannelsplitRgb::Process(const CUserBitmap* pCbmpElementsIn)
{
	if (pCbmpElementsIn->c_arr_const() == NULL)
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

	// ���̹����� �ʱ�ȭ �Ͽ��� �ϳ� ���� Ȯ�� �� ������ set �ϴ� �� ���� ���� �̷��� ó����
	if (Set(pCbmpElementsIn) == false)
	{
		return;
	}

	int index = 0;
	unsigned long i = 0;
	unsigned long j = 0;

	for (int k = 2; k >= 0; k--)
	{
		for (i = 0; i < pCbmpElementsIn->GetMaximumHeight() * pCbmpElementsIn->GetRwSize(); i++)
		{
			m_pCbmpElements->LocateAt(i) = 0;
		}

		for (i = 0; i < m_pCbmpElements->GetMaximumHeight(); i++)
		{
			index = (pCbmpElementsIn->GetMaximumHeight() - i - 1) * pCbmpElementsIn->GetRwSize();

			for (j = 0; j < m_pCbmpElements->GetMaximumWidth(); j++)
			{
				m_pCbmpElements->LocateAt(index + 3 * j + k) = pCbmpElementsIn->LocateAt(index + 3 * j + k);
			}
		}

		CopyClipboard(m_pCbmpElements->c_arr_const(), m_pCbmpElements->GetMaximumHeight(), m_pCbmpElements->GetMaximumWidth(), 24);

		AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
	}
}

