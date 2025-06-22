/////** 
////*description   : ���� C++ ���α׷� �ۼ��� ��ݵǴ� Ŭ���� ���� ��� ����  
////* 
////*/
#ifndef _BASICBONE_H_
#define _BASICBONE_H_
#pragma once

//*
// �ٸ� ��� ���� �߰��� �̷� ������ ���� ��
//#ifndef _SMAPLE_H_
//#include "sample.h"
//#endif //_SAMPLE_H_
//*/

// �ַ� �� �� �ִ� C++ �⺻��� ����
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

/////** 
////*description   : ���� C++ ���α׷� �ۼ��� ��ݵǴ� Ŭ����  
////*@parent class : -
////*/
class CBasicBone
{
//// ��� ���� ���� �κ�
public:

protected:

private:

//// ��� �Լ� ���� �κ�

public:

	///**
	//*description   : CBasicBone Ŭ������ ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBasicBone(void){}
		
	///**
	//*description   : CBasicBone Ŭ������ �Ҹ���
	//                 ��� �޴� Ŭ�������� �ݵ�� �Ҹ��ڸ� �����ϵ��� �ϱ� ���� virtual ��������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	virtual ~CBasicBone(void){}

protected:

private: 
    //////////////////////////////////////////////////////////////////
	// ���� ���縦 ���� ��� �ƴϸ�, �Ǽ��ζ� ȣ����� �ʰ� ��ġ��
	// �̵� ������, �̵� ���絵 �������� �ʴ´ٸ�, �Ǽ��ζ� ȣ����� �ʰ� ��ġ��
	// ���� ����� Ŭ������ �ش� Ŭ������ ��ӹ޾Ƽ� ����� �Ǽ��� ȣ��� �����϶� ����� �� ����.
	//////////////////////////////////////////////////////////////////
    
	/////**
	////*description	 : CBasicBone Ŭ������ ���� ������(���� ����� ������ �ʾҴٸ� ȣ�⵵ ���ϰ� ��)
	////*@param input	 : -
	////*@param output	 : -
	////*@return		 : -
	////*/
	CBasicBone(const CBasicBone& rhs);  
	
	/////**
	////*description	 : CBasicBone Ŭ������ �̵� ������(�ʿ��� ��� ��� ���� Ŭ�������� ��������� �������� ��)
	////*@param input	 : -
	////*@param output	 : -
	////*@return		 : -
	////*/
	CBasicBone(CBasicBone&& rhs) noexcept;

	/////**
	////*description	 : CBasicBone Ŭ������ ���� ������ (���� ����� ������ �ʾҴٸ� ȣ�⵵ ���ϰ� ��)
	////*@param input	 : -
	////*@param output	 : -
	////*@return		 : -
	////*/
    CBasicBone& operator=(const CBasicBone& rhs);


	/////**
	////*description	 : CBasicBone Ŭ������ �̵� ���� ������ (�ʿ��� ��� ��� ���� Ŭ�������� ��������� �������� ��)
	////*@param input	 : -
	////*@param output	 : -
	////*@return		 : -
	////*/
	CBasicBone& operator=(CBasicBone&& rhs) noexcept;

	//////////////////////////////////////////////////////////////////
	//// ���� ���縦 ���� ����� �̷� �ڵ� ������� �ۼ��� ��
	////CBasicBone(const CBasicBone& p)
	////{  
	////	// �Ʒ� ���� ������ ���� �Ҵ��� �޾Ƽ� ����
	////	//name= new char[strlen(p.name)+1];  
	////	//strcpy(name, p.name);  
	////}  
	//////////////////////////////////////////////////////////////////	
	//// ���� �����ڵ� ���� ����, �ڱ� ���� �˻���� �ݿ��� ��
	////CBasicBone& operator=(const CBasicBone& p)  
	////{  
	////	if (this == &rhs)   //  ��ġ�� �˻�, �� ��ü�� ������, �ڱ� �������� �˻��Ѵ�.  
	////		return *this; 
	////
	////	// �Ʒ� �� ���� �ڵ�� �� �� ������ �����ؼ� Ŭ������ ���� �����ϱ�
	////    /* 
	////    // 1. ���� ��ü ���� 
	////	delete []name;  
	////	name= new char[strlen(p.name)+1];   
	////	strcpy(name, p.name);
	////    */
	////    /* 
	////    // 2. ��ü ���� ��ȯ
    ////    CBasicBone temp(rhs);   // rhs�� �����Ϳ� ���� �纻�� �ϳ� �����.  
    ////    swap(temp);         // *this�� �����͸� �� �纻�� �Ͱ� �¹ٲ۴�.  
    ////    delete temp.pb; 
	////    */
	////	reurn *this;  
	////} 
	//////////////////////////////////////////////////////////////////	
	//// �ʿ�� ��(Ȥ�� ���� ��ü)�� �̿��� ���� �����ڵ� ����� ���� ����
	////CBasicBone& operator=(CBasicBone rhs)   
    ////{  
    ////    cout << "CBasicBone& operator=(const CBasicBone& rhs)" << endl;  
    ////  
    ////    swap(rhs);  // *this�� �����͸� �� �纻�� �����Ϳ� �¹ٲ۴�.  
    ////  
    ////    delete rhs.pb;  
    ////    return *this;  
    ////}  
	/////////////////////////////////////////////////////////////////
	////// *this�� ������ �� rhs�� �����͸� �¹ٲ۴�.  
	////void swap(CBasicBone& rhs)  
    ////{  
	////	// ��ü���� �¹ٲٴ� �۾��̹Ƿ� ���� ���� ���� �ʿ�
	////  CBasicBone * pOrig = pb;  
	////  pb = new CBasicBone(*rhs.pb);  
	////  rhs.pb = pOrig;       
	////}
	//////////////////////////////////////////////////////////////////
	//// �̵� �����ڸ� ����ϴ� ����� �̷� �ڵ� ������� �ۼ��� ��
	////CBasicBone(CBasicBone&& p)
	////{  
	////	// �Ʒ� ���� Ŭ���� ���迡 ���� �ٸ����� ���� ������ ���� ���� rhs���� ������ ���� NULL�� ����(C++ ǥ�ؿ� ���� �ٸ����� ����)
	////	// len = rhs.len; 
	////	// strName = rhs.strName;
	////    // rhs.StrName = NULL; 
	////
	////}  
	//////////////////////////////////////////////////////////////////
	//// �̵� ���� �����ڸ� ����ϴ� ����� �̷� �ڵ� ������� �ۼ��� ��
	////CBasicBone& operator=(CBasicBone&& p)
	////{  
	////	// �Ʒ� ���� Ŭ���� ���迡 ���� �ٸ����� ���� ������ ���� ���� rhs���� ������ ���� NULL�� ����(C++ ǥ�ؿ� ���� �ٸ����� ����)
	////	// len = rhs.len; 
	////	// strName = rhs.strName;
	////    // rhs.StrName = NULL; 
	////	// return *this;
	////}  
};

//////////////////////////////////////////////////////////////////
///// �ҽ� ���� �κ�
///// �� ���� �������� ����� ���ø� ��������, �ٸ� Ŭ�������� �ظ��ϸ� cpp�� ���� �и��صξ� �ۼ��ϱ�
//////////////////////////////////////////////////////////////////
/////** 
////*description   : ���� C++ ���α׷� �ۼ��� ��ݵǴ� Ŭ���� ���� �ҽ� ���� 
////*               
////* 
////*/
//#include "pch.h"
//#include "BasicBone.h"
//
/////**
////*description   : CBasicBone Ŭ������ ������
////*@param input  : -
////*@param output : -
////*@return		 : -
////*/
//CBasicBone::CBasicBone(void)
//{
//}
//
/////**
////*description   : CBasicBone Ŭ������ �Ҹ���
////                 ��� �޴� Ŭ�������� �ݵ�� �Ҹ��ڸ� �����ϵ��� �ϱ� ���� virtual ��������
////*@param input  : -
////*@param output : -
////*@return		 : -
////*/
//CBasicBone::~CBasicBone(void)
//{
//}
//////////////////////////////////////////////////////////////////

#endif //_BASICBONE_H_
