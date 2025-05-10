#pragma once

// CclientSocket 명령 대상
#define WM_CLIENT_RECV WM_USER+1
class CclientSocket : public CSocket
{
public:
	CclientSocket();
	virtual ~CclientSocket();
	void SetWnd(HWND hWnd);
	HWND m_hWnd;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

};


