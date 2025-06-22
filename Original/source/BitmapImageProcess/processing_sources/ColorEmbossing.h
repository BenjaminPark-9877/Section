/////** 
////*description   : ���� ������ �۾� ���� Ŭ���� ���� ��� ����
////*               
////* 
////*/
#ifndef _COLOREMBOSSING_H_
#define _COLOREMBOSSING_H_
#pragma once

#ifndef _BITMAPACTION_H_
#include "BitmapAction.h"
#endif //_BITMAPACTION_H_

///** 
//*description   : ���� ������ �۾� ���� Ŭ����
//*@parent class : public CBitmapAction  
//*/
class CColorEmbossing : public CBitmapAction
{
//// ��� ���� ���� �κ�
public:

protected:

private:

//// ��� �Լ� ���� �κ�
public:

	//*description   : ���� ������ �۾�
	//*@param input  : CUserBitmap* pCbmpElementsIn
	//*@param input  :   
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	inline void Process(const CUserBitmap& pCbmpElementsIn) { return Process(&pCbmpElementsIn); }

	//*description   : ���� ������ �۾�
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

	//*description   : 
	//*@param input  :  
	//*@param input  :  
	//*@param input  : int				height
	//*@param input  : int				width
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void ColorEmbossing(const unsigned char* InImg, unsigned char* OutImg, int height, int width);

private:

};
#endif //_COLOREMBOSSING_H_

