/////** 
////*description   : ���� �߽� ���ϱ� �۾� ���� Ŭ���� ���� ��� ����
////*               
////* 
////*/
#ifndef _ACTBLOBCOLORING_H_
#define _ACTBLOBCOLORING_H_
#pragma once

#ifndef _BITMAPACTION_H_
#include "BitmapAction.h"
#endif //_BITMAPACTION_H_

///** 
//*description   : ���� �߽� ���ϱ� �۾� ���� Ŭ����
//*@parent class : public CBitmapAction  
//*/
class CActBlobcoloring : public CBitmapAction
{
	//// ��� ���� ���� �κ�
public:

protected:

private:

	//// ��� �Լ� ���� �κ�
public:

	//*description   :  
	//*@param input  : CUserBitmap* pCbmpElementsIn
	//*@param input  :   
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	inline void Process(const CUserBitmap& pCbmpElementsIn, CClientDC* pDc) { return Process(&pCbmpElementsIn, pDc); }

	//*description   :  
	//*@param input  : CUserBitmap* pCbmpElementsIn
	//*@param input  :   
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void Process(const CUserBitmap* pCbmpElementsIn, CClientDC* pDc);

protected:

private:

};
#endif // _ACTBLOBCOLORING_H_
