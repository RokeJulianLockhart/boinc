// The contents of this file are subject to the Mozilla Public License
// Version 1.0 (the "License"); you may not use this file except in
// compliance with the License. You may obtain a copy of the License at
// http://www.mozilla.org/MPL/ 
// 
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
// License for the specific language governing rights and limitations
// under the License. 
// 
// The Original Code is the Berkeley Open Infrastructure for Network Computing. 
// 
// The Initial Developer of the Original Code is the SETI@home project.
// Portions created by the SETI@home project are Copyright (C) 2002
// University of California at Berkeley. All Rights Reserved. 
// 
// Contributor(s):
//

#ifndef __WIN_MAINWINDOW_H_
#define __WIN_MAINWINDOW_H_

// includes

#include "wingui.h"
#include "wingui_listctrl.h"
#include "wingui_piectrl.h"
#include "wingui_dialog.h"
#include "wingui_sswindow.h"
#include "gui_titles.h"

// constants

#define WND_TITLE			"BOINC"		// window's title

#define ICON_OFF			0			// remove icon
#define ICON_NORMAL			1			// normal icon
#define ICON_HIGHLIGHT		2			// highlighted icon

#define DEF_COL_WIDTH		80			// default width of list columns

#define TOP_BUFFER			5			// buffer pixels around edge of client
#define EDGE_BUFFER			2			// buffer pixels around edge of client

#define GUI_TIMER			104			// gui refresh
#define APP_TIMER			105			// app check
#define GUI_WAIT			1000		// timeout sleep time (in milliseconds)
#define APP_WAIT			100			// timeout sleep time (in milliseconds)

#define STATUS_ICON_ID		(WM_USER + 1)	// id for notifications from status icon

#define STATUS_MENU			0			// submenus for context menus
#define PROJECT_MENU		1
#define RESULT_MENU			2
#define XFER_MENU			3

#define PROJECT_ID			0			// child control ids
#define RESULT_ID			1
#define XFER_ID				2
#define MESSAGE_ID			3
#define USAGE_ID			4
#define TAB_ID				5

#define PROJECT_COLS		5			// number of columns for each control
#define RESULT_COLS			7
#define XFER_COLS			7
#define MESSAGE_COLS		3

//////////
// class:		CMyApp
// parent:		CWinApp
// description:	subclasses CWinApp to create main window.
class CMyApp : public CWinApp 
{
public:
    virtual BOOL			InitInstance();
    virtual int				ExitInstance();
};

//////////
// class:		CMainWindow
// parent:		CWnd
// description:	the main window, organizes child control windows and client
//				state, handles timer updates, some display features.
class CMainWindow : public CWnd
{
public:
							CMainWindow ();
	void					UpdateGUI(CLIENT_STATE*);
	void					MessageUser(char*,char*,int);
    BOOL					IsSuspended();
    BOOL					RequestNetConnect();
	UINT					m_nNetActivityMsg;		// ID of net activity message

protected:
	CMenu					m_MainMenu;				// window's main menu
	CMenu					m_ContextMenu;			// context menu for status icon and lists
	CProgressListCtrl		m_ProjectListCtrl;		// list control
	CProgressListCtrl		m_XferListCtrl;			// list control
	CProgressListCtrl		m_ResultListCtrl;		// list control
	CProgressListCtrl		m_MessageListCtrl;		// list control for messages to user
	CPieChartCtrl			m_UsagePieCtrl;			// pie chart control
	CFont					m_Font;					// window's font
	CTabCtrl				m_TabCtrl;				// tab control for choosing display
	CImageList				m_TabIL;				// image list for tab control
	CBitmap					m_TabBMP[MAX_TABS];		// bitmaps for tab image list
	HINSTANCE				m_hIdleDll;				// handle to dll for user idle
	int						m_nIconState;			// state of the status icon
	BOOL					m_bMessage;				// does the user have a new message?
	BOOL					m_bRequest;				// does the user have a net connection request?
	int						m_nContextItem;			// item selected for context menu
	UINT					m_nGuiTimerID;			// ID of current GUI timer	
	UINT					m_nAppTimerID;			// ID of current GUI timer	
	CSSWindow*				m_pSSWnd;				// default graphics window
	UINT					m_nScreenSaverMsg;		// ID of screensaver message
	UINT					m_nShowMsg;				// ID of show window request message
	UINT					m_nSetMsg;
	UINT					m_nGetMsg;

	DWORD					m_dwAppId;
	CRect					m_AppRect;
	int						m_AppMode;

	COLORREF				GetPieColor(int);
    void					ShowTab(int);
    void					SetStatusIcon(DWORD);
    void					SaveListControls();
    void					LoadListControls();
    void					SaveUserSettings();
    void					LoadUserSettings();
	void					LoadLanguage();
	DWORD					GetUserIdleTime();
	void					Syncronize(CProgressListCtrl*, vector<void*>*);
	void					CheckAppWnd();
    virtual void			PostNcDestroy();
	LRESULT					DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

    afx_msg void			OnClose();
	afx_msg void			OnCommandSettingsQuit();
	afx_msg void			OnCommandSettingsLogin();
	afx_msg void			OnCommandSettingsProxyServer();
	afx_msg void			OnCommandHelpAbout();
	afx_msg void			OnCommandProjectRelogin();
	afx_msg void			OnCommandProjectQuit();
	afx_msg void			OnCommandFileShowGraphics();
	afx_msg void			OnCommandFileClearInactive();
	afx_msg void			OnCommandFileClearMessages();
	afx_msg void			OnCommandConnectionConnectNow();
	afx_msg void			OnCommandConnectionHangupIfDialed();
	afx_msg void			OnCommandConnectionConfirmBeforeConnecting();
	afx_msg void			OnCommandHide();
	afx_msg void			OnCommandSuspend();
	afx_msg void			OnCommandResume();
	afx_msg void			OnCommandExit();
    afx_msg int				OnCreate(LPCREATESTRUCT);
	afx_msg BOOL			OnNotify(WPARAM, LPARAM, LRESULT*);
	afx_msg void			OnRButtonDown(UINT, CPoint);
    afx_msg void			OnSetFocus(CWnd*);
    afx_msg void			OnSize(UINT, int, int);
	afx_msg LRESULT			OnStatusIcon(WPARAM, LPARAM);
	afx_msg void			OnTimer(UINT); 

    DECLARE_MESSAGE_MAP()
};

// globals

extern CMyApp g_myApp;
extern CMainWindow* g_myWnd;

#endif
