/////** 
////*description   : ��Ʈ�� ������ �ϳ� �޾Ƽ� Ư���� �� ������ ó���� �ϴ� Ŭ���� ���� ��� ����
////*               
////* 
////*/
#ifndef _BITMAPACTION_H_
#define _BITMAPACTION_H_
#pragma once
#ifndef _BASICBONE_H_
#include "basicbone.h"
#endif //_BASICBONE_H_

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif //_USERMACHRO_H_

#ifndef _USER_RGBQUAD_H_
#include "UserRGBQuad.h"
#endif //_USER_RGBQUAD_H_

#ifndef _USERBITMAP_H_
#include "UserBitmap.h"
#endif //_USERBITMAP_H_ 

#ifndef _COLORCONV_H_
#include "ColorConv.h"
#endif //_COLORCONV_H_

///** 
//*description   : ��Ʈ�� ������ ó���ϴ� ��ü
//*@parent class : private CBasicBone : ���� ������, ���� ������ ȣ�� ������
//*/
class CBitmapAction : private CBasicBone
{
//// ��� ���� ���� �κ�
public:

protected:

	CUserRGBQuad* m_pCuserRGBQuad;

	CUserBitmap* m_pCbmpElements;

private:

//// ��� �Լ� ���� �κ�
public:

	///**
	//*description   : ��Ʈ�� ���� �ϳ��� ���� ��ü �� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapAction();

	///**
	//*description   : ��Ʈ�� ���� �ϳ��� ���� ��ü �� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	virtual ~CBitmapAction();

	///**
	//*description   : ��Ʈ�� ���� �ϳ��� ���� ��ü �� ���� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapAction(const CBitmapAction& rhs);

	///**
	//*description   : ��Ʈ�� ���� �ϳ��� ���� ��ü �� �̵� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapAction(CBitmapAction&& rhs) noexcept;
	
	///**
	//*description   : ��Ʈ�� ���� �ϳ��� ���� ��ü �� ���� ���� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapAction& operator=(const CBitmapAction& rhs);

	///**
	//*description   : ��Ʈ�� ���� �ϳ��� ���� ��ü �� �̵� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/	
	CBitmapAction& operator=(CBitmapAction&& rhs) noexcept;

	///**
	//*description   : ��Ʈ�� ���� �ϳ��� ���� ��ü �����Ҵ� �޸� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void Clear(void);

	//*description   : User Image�� ������ ������ ȭ�� ���
	//*@param input  : CDC* pDC					����� DC ������
	//*@param output : -
	//*@return		 : ������ ���࿩��(true:������,false:������)
	//*/
	bool DrawImage(CDC* pDC);

	//*description   : 
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void GetImageSize(CSize& csSizeImage) const;

	//*description   : Ŭ������� �����ϱ�
	//*@param input  : -
	//*@param output : -
	//*@return		 :  
	//*/
	bool CopyClipboard(void);

protected:

	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline void ClearCUserRGBQuad(void) { if (m_pCuserRGBQuad != NULL) { m_pCuserRGBQuad->Clear();	delete m_pCuserRGBQuad;	m_pCuserRGBQuad = NULL; } }

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline void ClearCUserBitmap(void) { if (m_pCbmpElements != NULL) { m_pCbmpElements->Clear(); delete m_pCbmpElements; m_pCbmpElements = NULL; } }

	///**
	//*description   : ��Ʈ�� ���� �ϳ��� ���� ��ü �����Ҵ� ���� ���� �ʱ�ȭ
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	bool Initialize(void);

	///**
	//*description   :  
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	bool InitializeCuserRGBQuad(void);

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	bool InitializeCUserBitmap(void);

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CUserRGBQuad* GetRGBQuad(int) { return ((m_pCuserRGBQuad != NULL) ? m_pCuserRGBQuad : NULL); }

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CUserBitmap* GetUserBitmap(int) { return ((m_pCbmpElements != NULL) ? m_pCbmpElements : NULL); }

	//*description   : Ŭ������� �����ϱ�
	//*@param input  : unsigned char	*m_CpyImg
	//*@param input  : int				height
	//*@param input  : int				width
	//*@param input  : int				biBitCount 
	//*@param output : -
	//*@return		 :  
	//*/
	void CopyClipboard(const unsigned char* m_CpyImg, int height, int width, int biBitCount);

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	bool Set(const CBitmapAction& rhs);

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	bool Set(const CUserBitmap* pUserBitmap);

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline bool Set(const CUserBitmap& userBitmap) { return Set(&userBitmap); }

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	bool Set(const CUserBitmap* pUserBitmap, const CUserRGBQuad* pRGBQuad);

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline bool Set(const CUserBitmap& userBitmap, const CUserRGBQuad& rgbQuad) { return Set(&userBitmap, &rgbQuad); }

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	bool Get(CBitmapAction& rhs);

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline bool Get(CUserBitmap& userBitmap) { return Get(&userBitmap); }

	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	bool Get(CUserBitmap* pUserBitmap);

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const CUserRGBQuad* GetRGBQuad(void) const { return ((m_pCuserRGBQuad != NULL) ? m_pCuserRGBQuad : NULL); }

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const CUserBitmap* GetUserBitmap(void) const { return ((m_pCbmpElements != NULL) ? m_pCbmpElements : NULL); }

	//*description   : 
	//*@param input  :  
	//*@param output : -
	//*@return		 : 
	//*/
	const size_t GetImageWidth(void) const;

	//*description   : 
	//*@param input  :  
	//*@param output : -
	//*@return		 :  
	//*/
	const size_t GetImageHeight(void) const;

	//*description   : 
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	const int GetImageBitCount(void) const;

	//*description   : 
	//*@param input  :
	//*@param output : -
	//*@return		 :  
	//*/
	const unsigned long GetImageRwSize(void) const;

	//*description   : 
	//*@param input  :
	//*@param output : -
	//*@return		 :  
	//*/
	const unsigned long GetTotalSize(void) const;

	//*description   : 
	//*@param input  :  
	//*@param input  :  
	//*@param input  : int				height
	//*@param input  : int				width
	//*@param input  : float			*Mask
	//*@param input  : int				winsize
	//*@param output : -
	//*@return		 :  
	//*/
	virtual bool ImgConvolution(std::vector<unsigned char>& InImg, std::vector<unsigned char>& OutImg,
						const size_t& height, const size_t& width, 
						std::vector<float>& Mask, int winsize);

	//*description   : RGB --> HSI���� ��ȯ 
	//*@param input  :  
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param input  : 
	//*@param input  :  
	//*@param output :  
	//*@return		 :  
	//*/
	bool RGBtoHSI(std::vector<unsigned char>& InImg, std::vector<short>& H,
				  std::vector<unsigned char>& S, std::vector<unsigned char>& IV,
				  const size_t& height, const size_t& width);

	//*description   : HSI --> RGB���� ��ȯ 	
	//*@param input  :  
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param input  : 
	//*@param input  :  
	//*@param output :  
	//*@return		 :  
	//*/
	bool HSItoRGB(std::vector<unsigned char>& OutImg, std::vector<short>& H,
		          std::vector<unsigned char>& S, std::vector<unsigned char>& IV,
		          const size_t& height, const size_t& width);

	//*description   : 
	//*@param input  : const size& winsize
	//*@param output : std::vector<float>& mask
	//*@return		 :  
	//*/
	bool InitializeMask(std::vector<float>& mask, const size_t& winsize);


	//*description   : 
	//*@param input  : const size& winsize
	//*@param input  : const std::vector<float>& pattern
	//*@param output : std::vector<float>& mask
	//*@return		 :  
	//*/
	bool FillMaskPattern(std::vector<float>& mask, const std::vector<float>& pattern, const size_t& winsize);

	//*description   : 
	//*@param input  : size& imageSize
	//*@param output : std::vector<float>& ucImage
	//*@return		 :  
	//*/
	bool InitializeBufferImage(std::vector<unsigned char>& ucImage, const size_t& imageSize);

	//*description   : 
	//*@param input  : size& imageSize
	//*@param output : std::vector<float>& ucImage
	//*@return		 :  
	//*/
	bool InitializeBufferImage(std::vector<short>& sImage, const size_t& imageSize);

private:

};

#endif //_BITMAPACTION_H_

