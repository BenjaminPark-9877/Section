/////** 
////*description   : 작업 수행 클래스 소스 파일
////*               
////* 
////*/
#include "pch.h"
#include "ActBlobcoloring.h"
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
void CActBlobcoloring::Process(const CUserBitmap* pCbmpElementsIn, CClientDC* pDc)
{
	if (pDc == NULL)
	{
		return;
	}

	if (pCbmpElementsIn->GetImage().data() == NULL)
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

	// 빈이미지로 초기화 하여야 하나 동작 확인 및 별도로 set 하는 일 막기 위해 이렇게 처리함
	if (Set(*pCbmpElementsIn) == false)
	{
		return;
	}

	int sx, sy, ex, ey;
	int count = 0;
	int height = m_pCbmpElements->GetMaximumHeight();
	int width = m_pCbmpElements->GetMaximumWidth();

	CBlobColoring pBlob(m_pCbmpElements->GetImage().data(), height, width);
	pBlob.fnBlobColoring(50);

	//for (int i = 1; i < pBlob.nBlob; i++)
	for (size_t i = 1; i < pBlob.getBlobCount(); i++)
	{
		if (pBlob.getBlobDataAt(i).n < 50) continue;
		//if (pBlob.blobData[i].n < 50) continue;
		sx = (int)pBlob.getBlobDataAt(i).cx - 5;
		//sx = (int)pBlob.blobData[i].cx - 5;
		ex = (int)pBlob.getBlobDataAt(i).cx + 5;
		//ex = (int)pBlob.blobData[i].cx + 5;
		sy = (int)pBlob.getBlobDataAt(i).cy - 5;
		//sy = (int)pBlob.blobData[i].cy - 5;
		ey = (int)pBlob.getBlobDataAt(i).cy + 5;
		//ey = (int)pBlob.blobData[i].cy + 5;

		sx = sx < 0 ? 0 : sx;
		sy = sy < 0 ? 0 : sy;
		ex = ex >= height ? height - 1 : ex;
		ey = ey >= width ? width - 1 : ey;

		float eccen = (pBlob.getBlobDataAt(i).u02 - pBlob.getBlobDataAt(i).u20) * (pBlob.getBlobDataAt(i).u02 - pBlob.getBlobDataAt(i).u20);
		//float eccen = (pBlob.blobData[i].u02 - pBlob.blobData[i].u20) * (pBlob.blobData[i].u02 - pBlob.blobData[i].u20);
				
		eccen = (eccen + 4 * pBlob.getBlobDataAt(i).u11) / pBlob.getBlobDataAt(i).n;
		//eccen = (eccen + 4 * pBlob.blobData[i].u11) / pBlob.blobData[i].n;

		if (pBlob.getBlobDataAt(i).v > 5) continue;
		//if (pBlob.blobData[i].v > 5) continue;

		pDc->MoveTo((int)pBlob.getBlobDataAt(i).cy, sx);
		//pDc->MoveTo((int)pBlob.blobData[i].cy, sx);

		pDc->LineTo((int)pBlob.getBlobDataAt(i).cy, ex);
		//pDc->LineTo((int)pBlob.blobData[i].cy, ex);
		
		pDc->MoveTo(sy, (int)pBlob.getBlobDataAt(i).cx);
		//pDc->MoveTo(sy, (int)pBlob.blobData[i].cx);
		
		pDc->LineTo(ey, (int)pBlob.getBlobDataAt(i).cx);
		//pDc->LineTo(ey, (int)pBlob.blobData[i].cx);
		count++;
	}
}
