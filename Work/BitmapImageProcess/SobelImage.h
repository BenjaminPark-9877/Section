/////** 
////*description   : Sobel �۾� ���� Ŭ���� ���� ��� ����
////*/
#ifndef _SOBELIMAGE_H_
#define _SOBELIMAGE_H_
#pragma once

#ifndef _DOUBLEMASKIMAGE_H_
#include "DoubleMaskImage.h"
#endif //_DOUBLEMASKIMAGE_H_

///** 
//*description   : Sobel �۾� ���� Ŭ����
//*@parent class : public CDoubleMaskImage  
//*/
class CSobelImage : public CDoubleMaskImage
{
	//// ��� �Լ� ���� �κ�
public:
	//*description   : Sobel ���� �ʱ�ȭ (1�� ����ũ)
	//*@param input  : ���� ����ũ
	//*@param output : ������ ũ��
	//*@return		 : �ʱ�ȭ ���� ����
	//*/
	bool InitializeMask_1st(std::vector<float>& mask, const size_t& winsize);

	//*description   : Sobel ���� �ʱ�ȭ (2�� ����ũ)
	//*@param input  : ���� ����ũ
	//*@param output : ������ ũ��
	//*@return		 : �ʱ�ȭ ���� ����
	//*/
	bool InitializeMask_2nd(std::vector<float>& mask, const size_t& winsize);

protected:
private:

};
#endif //_SOBELIMAGE_H_