#ifndef _USERMACHRO_H_
#define _USERMACHRO_H_
#pragma once

////////////////////////////////////////////////////////////////////////////
// ���� ���α׷������� ���� �и�������, �켱�� �� ���α׷����� �������� ���� ����� ���� ������
////////////////////////////////////////////////////////////////////////////
#include <wingdi.h>
#include <vcruntime_string.h>
#include <winnt.h>
#include <windef.h>
#include <tchar.h>
#include <afx.h>
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
// ����� ���� ��ũ�� �Լ��� ������(����� �ζ��� �Լ��� ��ü����)
////////////////////////////////////////////////////////////////////////////
//////* 
////#define WIDTHBYTES(bits)    (((bits)+31)/32*4)  //4����Ʈ�� �������  
////#define CLIP(val, low, high) {if(val<low) val=low; if(val>high) val=high;}
////*/

///**
//*description   : 4����Ʈ�� ��� ó�� �Լ�
//*@param input  : const size_t& bits
//*@param output : -
//*@return		 : size_t ��
//*/
inline size_t WIDTHBYTES(const size_t& bits) { return  (((bits)+31) / 32 * 4); } 

///**
//*description   : ���� �� �������� �߶�
//*@param input  : const myType& low
//*@param input  : const myType& high
//*@param output : myType& val
//*@return		 : -
//*/
template <typename myType>
inline void CLIP(myType& val,const myType& low, const myType& high) { if(val < low) val=low; if(val > high) val=high; }
////////////////////////////////////////////////////////////////////////////
 

////////////////////////////////////////////////////////////////////////////
// ����� ���� ��� �� ������
////////////////////////////////////////////////////////////////////////////
// �� �ȼ��� �� �� �ִ� �ִ� ��� ��谪 
#define MAXIMUM_PIXEL_VALUE 256

// �⺻ ��Ʈ�� ��� ���� ũ��
#define DEFALUT_BITMAPINFO_HEADERSIZE ( sizeof(BITMAPINFO)+MAXIMUM_PIXEL_VALUE*sizeof(RGBQUAD) )

// ũ�Ⱑ �������� ������ ��¡�ϴ� ��� ��
#define INVALID_IMAGE_SIZE 0

// ��ȿ�� ���� ��Ʈ���� ��Ÿ���� ���
#define INVALID_BIT_COUNT  0

// �ܻ� ü�踦 ������� ��Ÿ���� ��� ��
#define	 MONO_COLOR_TYPE 1

// 3�� ü�踦 ������� ��Ÿ���� ��� ��
#define	 THREE_COLOR_TYPE 3

// 4�� ü�踦 ������� ��Ÿ���� ��� ��
#define	 FOUR_COLOR_TYPE 4

// �⺻ �̹��� Ȯ���� ��
#define STR_DEFAULT_EXTEND_NAME _T(".bmp")
////////////////////////////////////////////////////////////////////////////

#endif //_USERMACHRO_H_