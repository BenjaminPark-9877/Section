/////** 
////*description   : ��Ʈ�� ������ ó���ϴ� ��ü ���� �ҽ� ����
////*               
////* 
////*/
#include "pch.h"
#include "BitmapProcess.h"


///**
//*description   : ��Ʈ�� ������ ó���ϴ� ��ü�� ������
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapProcess::CBitmapProcess(void)
{
	Initialize();
}

///**
//*description   : ��Ʈ�� ������ ó���ϴ� ��ü�� �Ҹ���
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapProcess::~CBitmapProcess(void)
{
	Clear();
}

///**
//*description   : ��Ʈ�� �̹��� ó�� ��� ��ü ���� �����Ҵ� �޸� ����
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
void CBitmapProcess::Clear(void)
{
	m_cbmpNodeIn.Clear();
}

///**
//*description   : ��Ʈ�� �̹��� ó�� ��� ��ü ���� ���� �ʱ�ȭ
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
void CBitmapProcess::Initialize(void)
{
	m_cuserRGBQuad.Initialize();
}

///**
//*description   : ��Ʈ���� ���Ϸ� ����
//*@param input  : LPCTSTR lpszPathName	���� ��θ�
//*@param input  : SmallUserBitmap& smallUserBitmap
//*@param input  : RGBQUAD*	palRGB
//*@param output : -
//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
//*/
bool CBitmapProcess::SaveImageToFile(LPCTSTR lpszPathName)
{
	if (lpszPathName == NULL)
	{
		return false;
	}

	if (_tcslen(lpszPathName) <= 0)
	{
		return false;
	}

	CBitmapIO bitmapIO;

	if (bitmapIO.Save(lpszPathName, m_cbmpNodeIn, m_cuserRGBQuad.Get()) == false)
	{
		return false;
	}

	return true;
}

///**
//*description   : ���Ϸκ��� ��Ʈ�� �о��
//*@param input  : LPCTSTR lpszPathName					���� ��θ�
//*@param input  :  
//*@param output :  
//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
//*/
bool CBitmapProcess::OpenImageFromFile(LPCTSTR lpszPathName)
{
	if (lpszPathName == NULL)
	{
		return false;
	}

	if (_tcslen(lpszPathName) <= 0)
	{
		return false;
	}

	CBitmapIO bitmapIO;

	if (bitmapIO.Open(lpszPathName, m_cbmpNodeIn, m_cuserRGBQuad.Get()) == false)
	{
		return false;
	}

	return true;
}

//*description   : 
//*@param input  :  
//*@param input  :   
//*@param input  :  
//*@param input  :  
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CBitmapProcess::RGB2HSI(void)
{
	CRGBToHSI rgb2hsi;
	
	rgb2hsi.Process(m_cbmpNodeIn);

	rgb2hsi.Clear(); // �޸� ���� ���� �� Ȯ���� ���ؼ��� �ݵ�� �� �κ��� �߰��� ��
}

//*description   : 
//*@param input  :  
//*@param input  :   
//*@param input  :
//*@param input  : 
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CBitmapProcess::RGB2Gray(void)
{
	CRGBToGray rgb2gray;

	rgb2gray.Process(m_cbmpNodeIn);

	rgb2gray.Clear(); // �޸� ���� ���� �� Ȯ���� ���ؼ��� �ݵ�� �� �κ��� �߰��� ��		 
}

//*description   : 
//*@param input  :  
//*@param input  :  
//*@param input  :  
//*@param input  :  
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CBitmapProcess::ColorEmbossing(void)
{
	CColorEmbossing colorEmbossing;

	colorEmbossing.Process(m_cbmpNodeIn);

	colorEmbossing.Clear();// �޸� ���� ���� �� Ȯ���� ���ؼ��� �ݵ�� �� �κ��� �߰��� ��		 
}

//*description   : 
//*@param input  :  
//*@param input  :  
//*@param input  : 
//*@param input  :
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CBitmapProcess::RGBShapening(void)
{
	CRGBSharpening rgbSharpening;
	
	rgbSharpening.Process(m_cbmpNodeIn);

	rgbSharpening.Clear();

}

//*description   :  
//*@param input  : -
//*@param output : -
//*@return		 :  
//*/
void CBitmapProcess::OnRgbSobel(void)
{
	CSobelImage sobelImage;

	sobelImage.Process(m_cbmpNodeIn);

	sobelImage.Clear();
}


//*description   : 
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CBitmapProcess::ChannelsplitRgb(void)
{
	CChannelsplitRgb channelsplitRgb;

	channelsplitRgb.Process(m_cbmpNodeIn);

	channelsplitRgb.Clear();
}

//*description   : 
//*@param input  :  
//*@param input  :  
//*@param input  : 
//*@param input  :
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CBitmapProcess::Blobcoloring(CClientDC* pDc)
{
	if (pDc == NULL)
	{
		return;
	}
	
	CActBlobcoloring actBlobcoloring;

	actBlobcoloring.Process(m_cbmpNodeIn, pDc);

	actBlobcoloring.Clear();
}

//*description   : 
//*@param input  :  
//*@param input  :  
//*@param input  : 
//*@param input  :
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
bool CBitmapProcess::OnImgDynbinSet(CDLG_DYNBIN* pDlg)
{
	if (pDlg == NULL)
	{
		return false;
	}

	if (m_cbmpNodeIn.GetBitmapInfo() == NULL)
	{
		return false;
	}

	if (m_cbmpNodeIn.c_arr_const() == NULL)
	{
		return false;
	}

	pDlg->Set(m_cbmpNodeIn);

	return true;
}

//*description   : 
//*@param input  :  
//*@param input  :  
//*@param input  : 
//*@param input  :
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
bool CBitmapProcess::OnImgDynbinGet(CDLG_DYNBIN* pDlg)
{
	if (pDlg == NULL)
	{
		return false;
	}

	if (m_cbmpNodeIn.GetBitmapInfo() == NULL)
	{
		return false;
	}

	if (m_cbmpNodeIn.c_arr_const() == NULL)
	{
		return false;
	}
	pDlg->Get(m_cbmpNodeIn);

	return true;
}


///**
//*description   : ���ο� User Image ������
//*@param input  : -
//*@param output : -
//*@return		 : ������ ���࿩��(true:������,false:������)
//*/
bool CBitmapProcess::NewDocument(void)
{
	CBitmapClipBoard bitmapClipBoard;

	if (bitmapClipBoard.NewDocument(m_cbmpNodeIn, m_cuserRGBQuad) == false)
	{
		return false;
	}

	return true;
}

//*description   : 
//*@param input  : int nFlag
//*@param output : -
//*@return		 : 
//*/
const size_t CBitmapProcess::GetImageWidth(void) const
{
	return m_cbmpNodeIn.GetMaximumWidth();
}

//*description   : 
//*@param input  : int nFlag
//*@param output : -
//*@return		 :  
//*/
const size_t CBitmapProcess::GetImageHeight(void) const
{
	return m_cbmpNodeIn.GetMaximumHeight();
}

//*description   : 
//*@param input  : int nFlag
//*@param output : -
//*@return		 :  
//*/
const int CBitmapProcess::GetImageBitCount(void) const
{
	return m_cbmpNodeIn.GetBitCount();
}

//*description   : 
//*@param input  : int nFlag
//*@param output : -
//*@return		 :  
//*/
const int CBitmapProcess::GetImageRwSize(void) const
{
	return m_cbmpNodeIn.GetRwSize();
}


//*description   : User Image�� ������ ������ ȭ�� ���
//*@param input  : CDC* pDC					����� DC ������
//*@param output : -
//*@return		 : ������ ���࿩��(true:������,false:������)
//*/
bool CBitmapProcess::DrawImage(CDC* pDC)
{
	if (pDC == NULL)
	{
		return false;
	}

	if (m_cbmpNodeIn.c_arr_const() == NULL)
	{
		return false;
	}

	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0,
		m_cbmpNodeIn.GetMaximumWidth(), m_cbmpNodeIn.GetMaximumHeight(),
		0, 0, 0, m_cbmpNodeIn.GetMaximumHeight(),
		m_cbmpNodeIn.c_arr_const(), m_cbmpNodeIn.GetBitmapInfo(), DIB_RGB_COLORS);

	return true;

}

//*description   : 
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CBitmapProcess::GetImageSize(CSize& csSizeImage) const
{
		csSizeImage.cx = GetImageWidth();
		csSizeImage.cy = GetImageHeight();
}

//*description   : Ŭ������� �����ϱ�
//*@param input  : -
//*@param output : -
//*@return		 :  
//*/
void  CBitmapProcess::CopyClipboard(void)
{
	CBitmapClipBoard bitmapClipBoard;

	bitmapClipBoard.CopyClipboard(m_cbmpNodeIn, m_cuserRGBQuad);

}