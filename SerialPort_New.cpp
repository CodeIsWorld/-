++// SerialPort_New.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SerialPort_New.h"
#include "SerialPort_NewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialPort_NewApp

BEGIN_MESSAGE_MAP(CSerialPort_NewApp, CWinApp)
	//{{AFX_MSG_MAP(CSerialPort_NewApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialPort_NewApp construction

CSerialPort_NewApp::CSerialPort_NewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSerialPort_NewApp object

CSerialPort_NewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSerialPort_NewApp initialization

BOOL CSerialPort_NewApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
//�Ի���������ʼ��ʼ���������//rxh2.8
	CSerialPort_NewDlg dlg;//�����˶Ի�����
	m_pMainWnd = &dlg;//��öԻ�����ĵ�ַ�����Ի�������Ϊ������
	int nResponse = dlg.DoModal();//�����Ի���dlg������DoModal�����ķ���ֵ���˳�ʱ�����ť��ID����ֵ��nResponse   
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
extern 	CSerialPort_NewDlg dlg;//rxh2.8������������ĶԻ�����