/////** 
////*description   : ���� ������ R/G/B �������� �и� �۾� ���� Ŭ���� ���� ��� ����
////*               
////* 
////*/
#ifndef _CHANNELSPLITRGB_H_
#define _CHANNELSPLITRGB_H_
#pragma once

#ifndef _BITMAPACTION_H_
#include "BitmapAction.h"
#endif //_BITMAPACTION_H_

///** 
//*description   : ���� ������ R/G/B �������� �и� �۾� ���� Ŭ����
//*@parent class : public CBitmapAction  
//*/
class CChannelsplitRgb : public CBitmapAction
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
	inline void Process(const CUserBitmap& pCbmpElementsIn) { return Process(&pCbmpElementsIn); }

	//*description   :  
	//*@param input  : CUserBitmap* pCbmpElementsIn
	//*@param input  :   
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void Process(const CUserBitmap* pCbmpElementsIn);

protected:

private:

};
#endif //_CHANNELSPLITRGB_H_
