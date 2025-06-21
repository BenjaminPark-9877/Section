#include "pch.h"
#include "BitmapIO.h"

///**
//*description   : ���Ϸκ��� ��Ʈ�� �о��
//*@param input  : LPCTSTR lpszPathName					���� ��θ�
//*@param input  :  
//*@param output :  
//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
//*/
bool CBitmapIO::Open(LPCTSTR lpszPathName, CUserBitmap& bmpNode, RGBQUAD* palRGB /*= NULL*/)
{
	BITMAPINFOHEADER DibHi;
	BITMAPFILEHEADER DibHf;
	memset(&DibHi, 0, sizeof(BITMAPINFOHEADER));
	memset(&DibHf, 0, sizeof(BITMAPFILEHEADER));

	if (lpszPathName == NULL)
	{
		return false;
	}

	if (_tcslen(lpszPathName) <= 0)
	{
		return false;
	}

	CFile hFile;

	if (!hFile.Open(lpszPathName, CFile::modeRead | CFile::typeBinary))
	{
		return false;
	}

	hFile.Read(&DibHf, sizeof(BITMAPFILEHEADER)); // ���� ��带 ���� 

	//�� ������ BMP�������� �˻�. 0x4d42=='BM'
	if (DibHf.bfType != 0x4D42)
	{
		return false;
	}

	hFile.Read(&DibHi, sizeof(BITMAPINFOHEADER)); //"���������� Header"�� �д´�.  

	if (DibHi.biBitCount != 8 && DibHi.biBitCount != 24)
	{
		return false;
	}

	if (DibHi.biBitCount == 8 && palRGB != NULL)
	{
		hFile.Read(palRGB, sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE);
	}

	// �޸� �Ҵ� (�ٲ� �κ�)
	int ImgSize = 0;

	if (DibHi.biBitCount == 8 && palRGB != NULL)
	{
		ImgSize = (int)hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - MAXIMUM_PIXEL_VALUE * sizeof(RGBQUAD);
	}
	else if (DibHi.biBitCount == 24)
	{
		ImgSize = (int)hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
	}

	std::vector<unsigned char> pUcBmpImage;
	pUcBmpImage.resize(ImgSize);
	std::fill(pUcBmpImage.begin(), pUcBmpImage.end(), 0);

	hFile.Read(pUcBmpImage.data(), ImgSize);

	hFile.Close();

	if (DibHi.biBitCount == 24)
	{
		// return true;
	}
	else
	{
		if (palRGB != NULL)
		{
			// �������� ���� 
			unsigned int i, j, index;
			int rwsize = WIDTHBYTES(DibHi.biBitCount * DibHi.biWidth);

			for (i = 0; i < (size_t)DibHi.biHeight; i++)
			{
				index = i * rwsize;

				for (j = 0; j < (size_t)DibHi.biWidth; j++)
				{
					// ���� ���� �ʿ��� �κ�(�����÷ο� �߻� ���ɼ� �ִٰ� ����)
					pUcBmpImage[index + j] = (unsigned char)(palRGB[(int)pUcBmpImage[index + j]].rgbBlue);
				}
			}
		}
	}

	bmpNode.SetImage(pUcBmpImage.data(), &DibHi, &DibHf);

	return true;

}

///**
//*description   : Ȯ���� �ٿ���
//*@param input  : CString lpszPathName	���� ��θ�
//*@param input  : 
//*@param input  : 
//*@param output : -
//*@return		 : ��θ�
//*/
CString CBitmapIO::AddExtendString(CString lpszPathName)
{
	CString cStrPathName = CString(lpszPathName).Trim();

	CString cStrExt = cStrPathName.Right(4);

	if (cStrExt.CompareNoCase(STR_DEFAULT_EXTEND_NAME))
	{
		cStrPathName = cStrPathName + STR_DEFAULT_EXTEND_NAME;
	}
	
	return cStrPathName;
}

///**
//*description   : ��Ʈ���� ���Ϸ� ����
//*@param input  : LPCTSTR lpszPathName	���� ��θ�
//*@param input  : SmallUserBitmap& smallUserBitmap
//*@param input  : RGBQUAD*	palRGB
//*@param output : -
//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
//*/
bool CBitmapIO::Save(LPCTSTR lpszPathName, CUserBitmap& bmpNode, RGBQUAD* palRGB /*= NULL*/)
{
	try
	{
		if (lpszPathName == NULL)
		{
			return false;
		}

		if (_tcslen(lpszPathName) <= 0)
		{
			return false;
		}

		CString cStrPathName = AddExtendString(lpszPathName);

		CFile hFile;

		if (!hFile.Open(cStrPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
		{
			return false;
		}

		hFile.Write(bmpNode.GetBimapFileHeader(), sizeof(BITMAPFILEHEADER));

		hFile.Write(bmpNode.GetBimapInfoHeader(), sizeof(BITMAPINFOHEADER));

		if (bmpNode.GetBimapInfoHeader()->biBitCount == 8 && palRGB != NULL)
		{
			hFile.Write(palRGB, sizeof(RGBQUAD) * 256);
		}

		hFile.Write(bmpNode.c_arr_const(), bmpNode.GetBimapInfoHeader()->biSizeImage);

		hFile.Close();

		return true;
	}
	catch (...)
	{
		return false;
	}
}
