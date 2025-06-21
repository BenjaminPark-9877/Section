/////** 
////*description   : sobel �۾� ���� Ŭ���� ���� ��� ����
////*               
////* 
////*/
#ifndef _SOBELIMAGE_H_
#define _SOBELIMAGE_H_
#pragma once

#ifndef _DOUBLEMASKIMAGE_H_
#include "DoubleMaskImage.h"
#endif //_DOUBLEMASKIMAGE_H_

///** 
//*description   : sobel �۾� ���� Ŭ����
//*@parent class : public CDoubleMaskImage  
//*/
class CSobelImage :  public CDoubleMaskImage
{
//// ��� ���� ���� �κ�
public:

protected:

private:

//// ��� �Լ� ���� �κ�
public:

protected:

	//*description   : 
	//*@param input  :  
	//*@param output : 
	//*@return		 :  
	//*/
	bool InitializeMask_1St(std::vector<float>& mask, const size_t& winsize);

	//*description   : 
	//*@param input  :  
	//*@param output : 
	//*@return		 :  
	//*/
	bool InitializeMask_2nd(std::vector<float>& mask, const size_t& winsize);

private:

};
#endif //_SOBELIMAGE_H_
