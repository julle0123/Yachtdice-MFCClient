#pragma once
#include "afxdialogex.h"


// Roll_Dice 대화 상자

class Roll_Dice : public CDialogEx
{
	DECLARE_DYNAMIC(Roll_Dice)

public:
	Roll_Dice(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Roll_Dice();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
