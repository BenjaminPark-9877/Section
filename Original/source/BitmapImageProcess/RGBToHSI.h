/////** 
////*description   : ��Ʈ�� ���� �޾Ƽ� RGB To HSI �۾� ���� Ŭ���� ���� ��� ����
////*               
////* 
////*/
#ifndef _RGBTOHSI_H_
#define _RGBTOHSI_H_
#pragma once

#ifndef _BITMAPACTION_H_
#include "BitmapAction.h"
#endif //_BITMAPACTION_H_

///** 
//*description   : ��Ʈ�� ���� �޾Ƽ� RGB To HSI �۾� ���� Ŭ����
//*@parent class : private CBitmapAction  
//*/
class CRGBToHSI :  public CBitmapAction
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
	//*@param input  : int				height
	//*@param input  : int				width
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void RGB2HSI(const unsigned char* InImg, unsigned char* OutImg, int height, int width);

	//*description   : 
	//*@param input  :  
	//*@param input  :   
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	bool SpiltOneColorImage(const CUserBitmap& bitmapNode, int nType = THREE_COLOR_TYPE );

private:

};
#endif //_RGBTOHSI_H_

