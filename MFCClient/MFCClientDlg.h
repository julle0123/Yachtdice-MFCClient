
// MFCClientDlg.h: 헤더 파일
//

#pragma once

#include "CclientSocket.h"
// CMFCClientDlg 대화 상자
class CMFCClientDlg : public CDialogEx
{
private:
	CImage m_image;
	CRect m_rect;

	// 생성입니다.
public:
	CMFCClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	CclientSocket m_ClientSocket;
	
	// 구현입니다.
public:
	CListBox m_list_msg;
	CEdit m_edit_send;
	//afx_msg void OnBnClickedBtnSend();
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);  //사용자 메시지 함수 추가

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonSend();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnStnClickedTurn();
	CString player2_name;
	CString player1_name;
	int player2_Yacht_point;
	int player1_Yacht_point;
	int player1_total_point;
	int player2_total_point;
	int player2_threes_point;
	int player1_threes_point;
	int player2_subtotal_point;
	int player1_subtotal_point;
	int player2_sstraight_point;
	int player1_sstraight_point;
	int player2_sixes_point;
	int player1_sixes_point;
	int player2_lstraight_point;
	int player1_lstraight_point;
	int player2_fullhouse_point;
	int player1_fullhouse_point;
	int player2_fours_point;
	int player1_fours_point;
	int player2_fives_point;
	int player1_fives_point;
	int player2_deuces_point;
	int player1_deuces_point;
	int player2_choice_point;
	int player1_choice_point;
	int player2_bonus_point;
	int player1_bonus_point;
	int player2_4kind_point;
	int player1_4kind_point;
	int player2_aces_point;
	int player1_aces_point;
private:
	CProgressCtrl m_progress_time;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL dice_lockbox1;
	BOOL dice_lockbox2;
	BOOL dice_lockbox3;
	BOOL dice_lockbox4;
	BOOL dice_lockbox5;
	CString s_Turn;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedRollDice();
	void Insert_Point(CString insert_Pos);
	afx_msg void OnBnClickedAcesInsertBt();
	afx_msg void OnBnClickedDeucesInsertBt();
	afx_msg void OnBnClickedThreesInsertBt();
	afx_msg void OnBnClickedFoursInsertBt();
	afx_msg void OnBnClickedFivesInsertBt();
	afx_msg void OnBnClickedSixesInsertBt();
	afx_msg void OnBnClickedChoiceInsertBt();
	afx_msg void OnBnClicked4kindInsertBt();
	afx_msg void OnBnClickedFullhouseInsertBt();
	afx_msg void OnBnClickedSstraightInsertBt();
	afx_msg void OnBnClickedLstraightInsertBt();
	afx_msg void OnBnClickedYachtInsertBt();
	void Diceinsert(CString dice);
	bool playername[2] = {FALSE,FALSE};
	void Turnchange(CString recvdata);
	void InvalidTextUpdate(UINT Id);
	void start();
	bool gstart[2] = { FALSE ,FALSE};
	void turnend();
	int score[2][14] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,} };
	CStatic dice_picture1;
	CImage m_image_dice1;
	CRect dice1_rect;
	CStatic dice_picture2;
	CImage m_image_dice2;
	CRect dice2_rect;
	CStatic dice_picture3;
	CImage m_image_dice3;
	CRect dice3_rect;
	CStatic dice_picture4;
	CImage m_image_dice4;
	CRect dice4_rect;
	CStatic dice_picture5;
	CImage m_image_dice5;
	CRect dice5_rect;
	void game_reset();
	
};