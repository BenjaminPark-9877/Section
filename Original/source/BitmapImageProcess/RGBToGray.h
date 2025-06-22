/////** 
////*description   : ��Ʈ�� ���� �޾Ƽ� RGB To Gray �۾� ���� Ŭ���� ���� ��� ����
////*               
////* 
////*/
#ifndef _RGBTOGRAY_H_
#define _RGBTOGRAY_H_
#pragma once

#ifndef _BITMAPACTION_H_
#include "BitmapAction.h"
#endif //_BITMAPACTION_H_

///** 
//*description   : ��Ʈ�� ���� �޾Ƽ� RGB To Gray �۾� ���� Ŭ����
//*@parent class : private CBitmapAction  
//*/
class CRGBToGray :  public CBitmapAction
{

//// ��� ���� ���� �κ�
public:

protected:

private:

//// ��� �Լ� ���� �κ�
public:

	//*description   : RGB -> HSI �������� ��ȯ �� ����
	//*@param input  : CUserBitmap* pCbmpElementsIn
	//*@param input  :   
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	inline void Process(const CUserBitmap& pCbmpElementsIn) { return Process(&pCbmpElementsIn); }

	//*description   : RGB -> HSI �������� ��ȯ �� ����
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
	//*@param input  :
	//*@param input  : 
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void RGB2Gray(const unsigned char* InImg, unsigned char* OutImg, int height, int width);

	//*description   : 
	//*@param input  :  
	//*@param input  :   
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	bool SpiltOneColorImage(const CUserBitmap& bitmapNode, int nType = THREE_COLOR_TYPE);

private:

};
#endif //_RGBTOGRAY_H_

