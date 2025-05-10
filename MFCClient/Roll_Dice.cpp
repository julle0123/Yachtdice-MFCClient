// Roll_Dice.cpp: 구현 파일
//

#include "pch.h"
#include "MFCClient.h"
#include "afxdialogex.h"
#include "Roll_Dice.h"


// Roll_Dice 대화 상자

IMPLEMENT_DYNAMIC(Roll_Dice, CDialogEx)

Roll_Dice::Roll_Dice(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
{

}

Roll_Dice::~Roll_Dice()
{
}

void Roll_Dice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Roll_Dice, CDialogEx)
END_MESSAGE_MAP()


// Roll_Dice 메시지 처리기
