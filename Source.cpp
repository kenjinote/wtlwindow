#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define WIN32_LEAN_AND_MEAN

#include <atlbase.h>
#include <atlapp.h>
CAppModule _Module;
#include <atlwin.h>

#include <atlcrack.h>
#include <atlmisc.h>

class CMyWindow : public CWindowImpl<CMyWindow>, public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_WND_CLASS(TEXT("Hello"));

private:
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_MSG_MAP_EX(CMyWindow)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_DESTROY(OnDestroy)
		END_MSG_MAP()

	void OnPaint(HDC /*hDC*/)
	{
		CPaintDC dc(m_hWnd);
		CRect rect;
		GetClientRect(rect);
		dc.DrawText(_T("Hello, ATL/WTL"), -1, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	LRESULT OnCreate(LPCREATESTRUCT lpcs)
	{
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);
		return 0;
	}

	void OnDestroy()
	{
		PostQuitMessage(0);
	}
};

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpCmdLine, int nCmdShow)
{
	_Module.Init(NULL, hInstance);

	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMyWindow wnd;
	wnd.Create(NULL, CWindow::rcDefault, TEXT("Hello, ATL/WTL"), WS_OVERLAPPEDWINDOW | WS_VISIBLE);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();

	_Module.Term();

	return nRet;
}
