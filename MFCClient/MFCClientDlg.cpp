
// MFCClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
#include "afxdialogex.h"

#define delaypoint 50
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define IP_ADD "127.0.0.1"//리턴백 주소
#define PORT 9999
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

//다이스 굴리는 횟수 제한
int Dicerollnumber = 3;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCClientDlg 대화 상자



CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
	//, m_edit_send(_T(""))
	
	, player2_name(_T("Player2"))
	, player1_name(_T("Player1"))
	, dice_lockbox1(FALSE)
	, dice_lockbox2(FALSE)
	, dice_lockbox3(FALSE)
	, dice_lockbox4(FALSE)
	, dice_lockbox5(FALSE)
	, s_Turn(_T("1/12"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send);		//IDC_EDIT_SEND 컨트롤 변수 추가
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);		//IDC_LIST_MSG 컨트롤 변수 추가
													//  DDX_Text(pDX, IDC_EDIT_SEND, m_edit_send);
													//0 ACE, 1 DEUCES, 2 THREES, 3 FOURS, 4 FIVES, 5 SIXS, 6 BONUS(SUBTOTAL), 7 CHOICE,8 4OF A KIND, 9 FULL HOUSE, 10 S.STRAIGHT, 11 L.STRAIGHT,12 YACHT, 13 TOTAL
													//ACE, DEUCES, THREES, FOURS, FIVES, SIXS, BONUS(SUBTOTAL), CHOICE, 4OF A KIND, FULL HOUSE, S.STRAIGHT, L.STRAIGHT,YACHT, TOTAL
	InvalidTextUpdate(IDC_YACHT_PLAYER2);
	DDX_Text(pDX, IDC_YACHT_PLAYER2, score[1][12]);
	InvalidTextUpdate(IDC_YACHT_PLAYER1);
	DDX_Text(pDX, IDC_YACHT_PLAYER1, score[0][12]);
	InvalidTextUpdate(IDC_TOTAL_PLAYER1);
	DDX_Text(pDX, IDC_TOTAL_PLAYER1, score[0][13]);
	InvalidTextUpdate(IDC_TOTAL_PLAYER2);
	DDX_Text(pDX, IDC_TOTAL_PLAYER2, score[1][13]);
	InvalidTextUpdate(IDC_THREES_PLAYER2);
	DDX_Text(pDX, IDC_THREES_PLAYER2, score[1][2]);
	InvalidTextUpdate(IDC_THREES_PLAYER1);
	DDX_Text(pDX, IDC_THREES_PLAYER1, score[0][2]);
	InvalidTextUpdate(IDC_SUBTOTAL_PLAYER2);
	DDX_Text(pDX, IDC_SUBTOTAL_PLAYER2, score[1][6]);
	InvalidTextUpdate(IDC_SUBTOTAL_PLAYER1);
	DDX_Text(pDX, IDC_SUBTOTAL_PLAYER1, score[0][6]);
	if (score[0][6] > 63 || score[1][6] > 63) {
		int subtotal[4] = { score[0][6] - 35 ,score[1][6] - 35 ,35,35 };
		InvalidTextUpdate(IDC_SUBTOTAL_PLAYER2);
		DDX_Text(pDX, IDC_SUBTOTAL_PLAYER2, subtotal[1]);
		InvalidTextUpdate(IDC_SUBTOTAL_PLAYER1);
		DDX_Text(pDX, IDC_SUBTOTAL_PLAYER1, subtotal[0]);
		InvalidTextUpdate(IDC_BONUS_PLAYER2);
		DDX_Text(pDX, IDC_BONUS_PLAYER2, subtotal[3]);
		InvalidTextUpdate(IDC_BONUS_PLAYER1);
		DDX_Text(pDX, IDC_BONUS_PLAYER1, subtotal[2]);
	}
	InvalidTextUpdate(IDC_SSTRAIGHT_PLAYER2);
	DDX_Text(pDX, IDC_SSTRAIGHT_PLAYER2, score[1][10]);
	InvalidTextUpdate(IDC_SSTRAIGHT_PLAYER1);
	DDX_Text(pDX, IDC_SSTRAIGHT_PLAYER1, score[0][10]);
	InvalidTextUpdate(IDC_SIXES_PLAYER2);
	DDX_Text(pDX, IDC_SIXES_PLAYER2, score[1][5]);
	InvalidTextUpdate(IDC_SIXES_PLAYER1);
	DDX_Text(pDX, IDC_SIXES_PLAYER1, score[0][5]);
	DDX_Text(pDX, IDC_NAME_PLAYER2, player2_name);
	DDX_Text(pDX, IDC_NAME_PLAYER1, player1_name);
	InvalidTextUpdate(IDC_LSTRAIGHT_PLAYER2);
	DDX_Text(pDX, IDC_LSTRAIGHT_PLAYER2, score[1][11]);
	InvalidTextUpdate(IDC_LSTRAIGHT_PLAYER1);
	DDX_Text(pDX, IDC_LSTRAIGHT_PLAYER1, score[0][11]);
	InvalidTextUpdate(IDC_FULLHOUSE_PLAYER2);
	DDX_Text(pDX, IDC_FULLHOUSE_PLAYER2, score[1][9]);
	InvalidTextUpdate(IDC_FULLHOUSE_PLAYER1);
	DDX_Text(pDX, IDC_FULLHOUSE_PLAYER1, score[0][9]);
	InvalidTextUpdate(IDC_FOURS_PLAYER2);
	DDX_Text(pDX, IDC_FOURS_PLAYER2, score[1][3]);
	InvalidTextUpdate(IDC_FOURS_PLAYER1);
	DDX_Text(pDX, IDC_FOURS_PLAYER1, score[0][3]);
	InvalidTextUpdate(IDC_FIVES_PLAYER2);
	DDX_Text(pDX, IDC_FIVES_PLAYER2, score[1][4]);
	InvalidTextUpdate(IDC_FIVES_PLAYER1);
	DDX_Text(pDX, IDC_FIVES_PLAYER1, score[0][4]);
	InvalidTextUpdate(IDC_DEUCES_PLAYER2);
	DDX_Text(pDX, IDC_DEUCES_PLAYER2, score[1][1]);
	InvalidTextUpdate(IDC_DEUCES_PLAYER1);
	DDX_Text(pDX, IDC_DEUCES_PLAYER1, score[0][1]);
	InvalidTextUpdate(IDC_CHOICE_PLAYER2);
	DDX_Text(pDX, IDC_CHOICE_PLAYER2, score[1][7]);
	InvalidTextUpdate(IDC_CHOICE_PLAYER1);
	DDX_Text(pDX, IDC_CHOICE_PLAYER1, score[0][7]);

	InvalidTextUpdate(IDC_ACES_PLAYER2);
	DDX_Text(pDX, IDC_ACES_PLAYER2, score[1][0]);
	InvalidTextUpdate(IDC_4KIND_PLAYER2);
	DDX_Text(pDX, IDC_4KIND_PLAYER2, score[1][8]);
	InvalidTextUpdate(IDC_4KIND_PLAYER1);
	DDX_Text(pDX, IDC_4KIND_PLAYER1, score[0][8]);
	InvalidTextUpdate(IDC_ACES_PLAYER1);
	DDX_Text(pDX, IDC_ACES_PLAYER1, score[0][0]);
	DDX_Control(pDX, IDC_GAME_TIMECOUNT, m_progress_time);
	DDX_Check(pDX, IDC_DICE_LOCKBOX1, dice_lockbox1);
	DDX_Check(pDX, IDC_DICE_LOCKBOX2, dice_lockbox2);
	DDX_Check(pDX, IDC_DICE_LOCKBOX3, dice_lockbox3);
	DDX_Check(pDX, IDC_DICE_LOCKBOX4, dice_lockbox4);
	DDX_Check(pDX, IDC_DICE_LOCKBOX5, dice_lockbox5);
	InvalidTextUpdate(IDC_TURN);
	DDX_Text(pDX, IDC_TURN, s_Turn);

}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_CLIENT_RECV, &CMFCClientDlg::OnClientRecv)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCClientDlg::OnClickedButtonSend)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	//ON_STN_CLICKED(IDC_TURN, &CMFCClientDlg::OnStnClickedTurn)
	ON_BN_CLICKED(IDC_ROLL_DICE, &CMFCClientDlg::OnBnClickedRollDice)
	ON_BN_CLICKED(IDC_ACES_INSERT_BT, &CMFCClientDlg::OnBnClickedAcesInsertBt)
	ON_BN_CLICKED(IDC_DEUCES_INSERT_BT, &CMFCClientDlg::OnBnClickedDeucesInsertBt)
	ON_BN_CLICKED(IDC_THREES_INSERT_BT, &CMFCClientDlg::OnBnClickedThreesInsertBt)
	ON_BN_CLICKED(IDC_FOURS_INSERT_BT, &CMFCClientDlg::OnBnClickedFoursInsertBt)
	ON_BN_CLICKED(IDC_FIVES_INSERT_BT, &CMFCClientDlg::OnBnClickedFivesInsertBt)
	ON_BN_CLICKED(IDC_SIXES_INSERT_BT, &CMFCClientDlg::OnBnClickedSixesInsertBt)
	ON_BN_CLICKED(IDC_CHOICE_INSERT_BT, &CMFCClientDlg::OnBnClickedChoiceInsertBt)
	ON_BN_CLICKED(IDC_4KIND_INSERT_BT, &CMFCClientDlg::OnBnClicked4kindInsertBt)
	ON_BN_CLICKED(IDC_FULLHOUSE_INSERT_BT, &CMFCClientDlg::OnBnClickedFullhouseInsertBt)
	ON_BN_CLICKED(IDC_SSTRAIGHT_INSERT_BT, &CMFCClientDlg::OnBnClickedSstraightInsertBt)
	ON_BN_CLICKED(IDC_LSTRAIGHT_INSERT_BT, &CMFCClientDlg::OnBnClickedLstraightInsertBt)
	ON_BN_CLICKED(IDC_YACHT_INSERT_BT, &CMFCClientDlg::OnBnClickedYachtInsertBt)
END_MESSAGE_MAP()


// CMFCClientDlg 메시지 처리기

BOOL CMFCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_progress_time.SetRange(0, 180);
	m_progress_time.SetPos(180);




	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	GetDlgItem(IDC_GAME_BOARD)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);
	GetDlgItem(IDC_DICE_IMAGE1)->GetWindowRect(dice1_rect);
	ScreenToClient(dice1_rect);
	GetDlgItem(IDC_DICE_IMAGE2)->GetWindowRect(dice2_rect);
	ScreenToClient(dice2_rect);
	GetDlgItem(IDC_DICE_IMAGE3)->GetWindowRect(dice3_rect);
	ScreenToClient(dice3_rect);
	GetDlgItem(IDC_DICE_IMAGE4)->GetWindowRect(dice4_rect);
	ScreenToClient(dice4_rect);
	GetDlgItem(IDC_DICE_IMAGE5)->GetWindowRect(dice5_rect);
	ScreenToClient(dice5_rect);
	m_image.Load(L"yachtdicescore.png");
	m_image_dice1.Load(L"dice1.bmp");
	m_image_dice2.Load(L"dice2.bmp");
	m_image_dice3.Load(L"dice3.bmp");
	m_image_dice4.Load(L"dice4.bmp");
	m_image_dice5.Load(L"dice5.bmp");
	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create();
	if (m_ClientSocket.Connect(_T(IP_ADD), PORT) == FALSE) {
		AfxMessageBox(_T("서버와 연결할 수 없습니다."));
		PostQuitMessage(0);
		return FALSE;
	}

	//서버에서 데이터전달시 다른 함수에서 동작예정, 테스트용
	SetTimer(1, 3000, NULL);

	return TRUE; 
}

void CMFCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


//사진띄우는 함수
void CMFCClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		m_image.Draw(dc, m_rect);
		m_image_dice1.Draw(dc, dice1_rect);
		m_image_dice2.Draw(dc, dice2_rect);
		m_image_dice3.Draw(dc, dice3_rect);
		m_image_dice4.Draw(dc, dice4_rect);
		m_image_dice5.Draw(dc, dice5_rect);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCClientDlg::OnClickedButtonSend() //채팅 데이터 전송 버튼
{
	CString str;
	UpdateData(TRUE);
	m_edit_send.GetWindowTextW(str);
	str = _T("C|") + str;
	m_ClientSocket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	m_edit_send.SetWindowTextW(_T(""));
	UpdateData(FALSE);
}

afx_msg LRESULT CMFCClientDlg::OnClientRecv(WPARAM wParam, LPARAM lParam) //데이터 수신
{
	CString lpszStr = (LPCTSTR)lParam;
	if (lpszStr.Find(_T("C|")) + 1) {
		lpszStr.Format(lpszStr.Mid(2));
		m_list_msg.InsertString(-1, lpszStr);
		m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	}
	else if(lpszStr.Find(_T("D|")) + 1){
		lpszStr.Format(lpszStr.Mid(2));
		Diceinsert(lpszStr);
	}
	else if (lpszStr.Find(_T("T|")) + 1) {
		lpszStr.Format(lpszStr.Mid(2));
		Turnchange(lpszStr);
	}
	else if (lpszStr.Find(_T("Player1접속")) + 1) { 
		playername[0] = TRUE;
		m_list_msg.InsertString(-1, lpszStr);
		m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	}
	else if ((lpszStr.Find(_T("Player2접속")) + 1)) {	
		if (!playername[0]) { playername[1] = TRUE; }
		m_list_msg.InsertString(-1, lpszStr);
		m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
		start();
	}
	else if ((lpszStr.Find(_T("reset|")) + 1)) {
		start();
	}
	else if (lpszStr.Find(_T("Player접속종료")) + 1) {
		game_reset();
		m_list_msg.InsertString(-1, lpszStr);
		m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	}
	
	return 0;
}


HBRUSH CMFCClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	int nret = pWnd->GetDlgCtrlID();
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	return hbr;
}


//엔터를 눌러 채팅을 전송하는 함수
BOOL CMFCClientDlg::PreTranslateMessage(MSG* pMsg)
{
	CEdit* editSendMsg;
	editSendMsg = (CEdit*)GetDlgItem(IDC_EDIT_SEND);
	if (pMsg->message == WM_KEYDOWN) //키가 눌렸을 경우
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			if (editSendMsg == GetFocus())
				OnClickedButtonSend();
		case VK_ESCAPE:
			return TRUE;

		default:
			break;
		}
	}
	//엔터키 적용
	return CDialogEx::PreTranslateMessage(pMsg);
}

afx_msg void CMFCClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (1 == nIDEvent) {
		KillTimer(1);
		Invalidate();
	}
	else if (2 == nIDEvent)
	{
		int position = m_progress_time.GetPos();
		CString str;
		if (position > 10) {
			position--;
			m_progress_time.SetPos(position);
		}
		else if (position > 0) {
			position--;
			m_progress_time.SetPos(position);
			
			str.Format(_T("C|%d 초 남았습니다."), position+1);
			m_list_msg.InsertString(-1, str);
			m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
		}
		else {
			str.Format(_T("시간이 초과되었습니다."));
			m_list_msg.InsertString(-1, str);
			m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);

			str.Format(_T("T|timeout"));
			m_ClientSocket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);

			KillTimer(2);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

//굴리기 버튼동작
void CMFCClientDlg::OnBnClickedRollDice()
{
	if (gstart[0] || gstart[1]) {
		if (Dicerollnumber != 0) {
			UpdateData(TRUE);
			CString str;
			str.Format(_T("R|%d%d%d%d%d\n"), dice_lockbox1, dice_lockbox2, dice_lockbox3, dice_lockbox4, dice_lockbox5);
			m_ClientSocket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
			Dicerollnumber--;


			Sleep(delaypoint);
			str.Format(_T("C| %d회 남았습니다"), Dicerollnumber);
			m_ClientSocket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
		}
	}
}

//삽입 버튼 눌렀을 떄에 대한 버튼 분류 및 버튼 데이터 전송
void CMFCClientDlg::Insert_Point(CString insert_Pos)
{
	UpdateData(TRUE);
	CString str;
	str = _T("T|") + insert_Pos;
	m_ClientSocket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	

	KillTimer(2);
}

//'삽입' 버튼 동작
void CMFCClientDlg::OnBnClickedAcesInsertBt()
{
	if(gstart[0]||gstart[1]) {
		Insert_Point(_T("Ace"));
		GetDlgItem(IDC_ACES_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::OnBnClickedDeucesInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Deuces"));
		GetDlgItem(IDC_DEUCES_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::OnBnClickedThreesInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Threes"));
		GetDlgItem(IDC_THREES_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::OnBnClickedFoursInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Fours"));
		GetDlgItem(IDC_FOURS_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::OnBnClickedFivesInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Fives"));
		GetDlgItem(IDC_FIVES_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::OnBnClickedSixesInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Sixes"));
		GetDlgItem(IDC_SIXES_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::OnBnClickedChoiceInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Choice"));
		GetDlgItem(IDC_CHOICE_INSERT_BT)->EnableWindow(FALSE);
	}

}

void CMFCClientDlg::OnBnClicked4kindInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("4kind"));
		GetDlgItem(IDC_4KIND_INSERT_BT)->EnableWindow(FALSE);
	}

}

void CMFCClientDlg::OnBnClickedFullhouseInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Fullhouse"));
		GetDlgItem(IDC_FULLHOUSE_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::OnBnClickedSstraightInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Sstraight"));
		GetDlgItem(IDC_SSTRAIGHT_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::OnBnClickedLstraightInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Lstraight"));
		GetDlgItem(IDC_LSTRAIGHT_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::OnBnClickedYachtInsertBt()
{
	if (gstart[0] || gstart[1]) {
		Insert_Point(_T("Yacht"));
		GetDlgItem(IDC_YACHT_INSERT_BT)->EnableWindow(FALSE);
	}
	
}

void CMFCClientDlg::Diceinsert(CString dice)
{
	CString dicedata[5];
	//CString bmpdata[5];
	
	for (int i = 0; i < 5; i++) {
		AfxExtractSubString(dicedata[i], dice, i, '/');
		// 이미지 파일 경로 생성
		CString imagePath;
		imagePath.Format(_T("dice%s.bmp"), dicedata[i]);

		// 이미지 파일 존재 여부 확인
		if (PathFileExists(imagePath)) {
			// 이미지 로드
			switch (i) {
			case 0:
				// `m_image_dice1` 변수에 연결된 이미지 해제
				m_image_dice1.Destroy();
				m_image_dice1.Load(imagePath);
				InvalidateRect(&dice1_rect);
				UpdateWindow();
				break;
			case 1:
				// `m_image_dice2` 변수에 연결된 이미지 해제
				m_image_dice2.Destroy();
				m_image_dice2.Load(imagePath);
				InvalidateRect(&dice2_rect);
				UpdateWindow();
				break;
			case 2:
				// `m_image_dice3` 변수에 연결된 이미지 해제
				m_image_dice3.Destroy();
				m_image_dice3.Load(imagePath);
				InvalidateRect(&dice3_rect);
				UpdateWindow();
				break;
			case 3:
				// `m_image_dice4` 변수에 연결된 이미지 해제
				m_image_dice4.Destroy();
				m_image_dice4.Load(imagePath);
				InvalidateRect(&dice4_rect);
				UpdateWindow();
				break;
			case 4:
				// `m_image_dice5` 변수에 연결된 이미지 해제
				m_image_dice5.Destroy();
				m_image_dice5.Load(imagePath);
				InvalidateRect(&dice5_rect);
				UpdateWindow();
				break;
			}
		}
		else {
			CString start = L"이미지로드실패";
			m_list_msg.InsertString(-1, start);
			m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
		}
	
	}

}

void CMFCClientDlg::Turnchange(CString recvdata) {
	CString turndata[6];//첫번째는 1~12 턴정보 두번째는 선택한족보가 어떤거인지 세번째는 선택한 점수 네번째는 서브토탈 다섯번째는 토탈 여섯번째는 어떤 플레이어 정보인지 
	UpdateData(TRUE);
	m_progress_time.SetPos(180);
	SetTimer(2, 1000, NULL);
	if (recvdata.Find(L"timeout")) {
		for (int i = 0; i < 6; i++)
		{
			AfxExtractSubString(turndata[i], recvdata, i, '/');
		}
		
		
		s_Turn.Format(_T("%d/12"), _ttoi(turndata[0]));
		if (turndata[5].Find(L"1") + 1) {
			gstart[0] = TRUE;
			gstart[1] = FALSE;
			if (playername[1]) { gstart[0] = FALSE; }
			m_list_msg.InsertString(-1, L"PLAYER1의 턴입니다.");
		}
		if (turndata[5].Find(L"0") + 1) {
			gstart[1] = TRUE;
			gstart[0] = FALSE;
			if (playername[0]) { gstart[1] = FALSE; }
			m_list_msg.InsertString(-1, L"PLAYER2의 턴입니다.");
		}
		Dicerollnumber = 3;
		score[_ttoi(turndata[5])][_ttoi(turndata[1])] = _ttoi(turndata[2]);
		score[_ttoi(turndata[5])][6] = _ttoi(turndata[3]);
		score[_ttoi(turndata[5])][13] = _ttoi(turndata[4]);
	}
	else if (recvdata.Find(L"timeout") + 1) {
		for (int i = 0; i < 3; i++)
		{
			AfxExtractSubString(turndata[i], recvdata, i, '/');
		}
		s_Turn.Format(_T("%d/12"), _ttoi(turndata[1]));
		if (turndata[2].Find(L"1") + 1) {
			gstart[0] = TRUE;
			gstart[1] = FALSE;
			if (playername[1]) { gstart[0] = FALSE; }
			m_list_msg.InsertString(-1, L"PLAYER1의 턴입니다.");
		}
		if (turndata[2].Find(L"0") + 1) {
			gstart[1] = TRUE;
			gstart[0] = FALSE;
			if (playername[0]) { gstart[1] = FALSE; }
			m_list_msg.InsertString(-1, L"PLAYER2의 턴입니다.");
		}
		Dicerollnumber = 3;
	}
	//m_list_msg.InsertString(-1,L"PLAYER1의 턴입니다.");
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	UpdateData(FALSE);

}

//전에 있던 글자 Invalid해주는 함수
void CMFCClientDlg::InvalidTextUpdate(UINT Id) {
	CRect useRect;
	GetDlgItem(Id)->GetWindowRect(useRect);
	ScreenToClient(&useRect);
	InvalidateRect(useRect);
}
void CMFCClientDlg::start() {
	CString start = L"게임을 시작합니다";
	game_reset();
	if (playername[0]) {
		gstart[0] = TRUE;	
	}
	gstart[1] = FALSE;
	SetTimer(2, 1000, NULL);
	
	m_list_msg.InsertString(-1, start);
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
}
void CMFCClientDlg::game_reset() {
	UpdateData(TRUE);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			score[i][j] = 0;
		}
	}
	s_Turn=_T("1/12");
	GetDlgItem(IDC_ACES_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEUCES_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_THREES_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_FOURS_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIVES_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIXES_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHOICE_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_4KIND_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_FULLHOUSE_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_YACHT_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SSTRAIGHT_INSERT_BT)->EnableWindow(TRUE);
	GetDlgItem(IDC_LSTRAIGHT_INSERT_BT)->EnableWindow(TRUE);
	UpdateData(FALSE);
}