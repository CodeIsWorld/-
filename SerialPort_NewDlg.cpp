// SerialPort_NewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialPort_New.h"
#include "SerialPort_NewDlg.h"
#include "SerialPort.h"
//#include "DATA_Fomate_Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//rxh2.9.1��̬����������������г�ʼ��
unsigned char CSerialPort_NewDlg::data_bit=8;//rxh2.9.1
unsigned char CSerialPort_NewDlg::stop_bit=1;//ֹͣλ
char CSerialPort_NewDlg::check_bit='N';//��żУ��λ

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialPort_NewDlg dialog

CSerialPort_NewDlg::CSerialPort_NewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialPort_NewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerialPort_NewDlg)
	m_string_receive = _T("");
	m_string_send = _T("");
	m_bool_check_timer_send_period = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}
//DDXָ����Dialog Data Exchange���Ի������ݽ�����
void CSerialPort_NewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerialPort_NewDlg)
	DDX_Control(pDX, IDC_STATIC_THREAD_COUNT_NO_USE, m_static_thread_count_no_use);
	DDX_Control(pDX, IDC_STATIC_RECEIVE_LINE_COUNT, m_static_receive_line_count);
	DDX_Control(pDX, IDC_EDIT_TEMER_PERIOD, m_ctrl_edit_send_period);
	DDX_Control(pDX, IDC_CHECK_TIMER_SEND, m_check_timer_send);
	DDX_Control(pDX, IDC_CHECK_HEX16_SEND, m_ctrlHexSend);
	DDX_Control(pDX, IDC_CHECK_HEX16_DISP, m_check_hex16_disp);
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send_data);
	DDX_Control(pDX, IDC_EDIT_RECEIVE, m_edit_receive_data);
	DDX_Control(pDX, IDC_STATIC_SEND_COUNT, m_static_send_control);
	DDX_Control(pDX, IDC_COMBO_COM_NUM, m_combo_com_num);
	DDX_Control(pDX, IDC_COMBO_BANDRATE, m_Combo_bandRate);
	DDX_Control(pDX, IDC_STATIC_RECEIVE_COUNT, m_static_receive_contr);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_button_send_data);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_open_serial_port);
	DDX_Control(pDX, IDC_BUTTON_CLEAN, m_clean_window);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_string_receive);
	DDX_Text(pDX, IDC_EDIT_SEND, m_string_send);
	DDX_Check(pDX, IDC_CHECK_TIMER_SEND, m_bool_check_timer_send_period);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSerialPort_NewDlg, CDialog)//��Ϣӳ���
	//{{AFX_MSG_MAP(CSerialPort_NewDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, OnButtonClean)
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommReceivedata) //������Ϣ����ֻ�������һ��
	ON_MESSAGE(WM_COMM_CLOSE_PORT, OnComErrorAndClose) //rxh2.8
	ON_CBN_SELENDOK(IDC_COMBO_BANDRATE, OnSelendokCOMBOBaudRate)
	ON_CBN_SELENDOK(IDC_COMBO_COM_NUM, OnSelendokComboComNum)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON__CLEAN_COUNT_, OnButtonCleanCount)
	ON_WM_CHAR()
	ON_WM_SIZE()
	ON_CBN_DROPDOWN(IDC_COMBO_COM_NUM, OnDropdownComboComNum)
	ON_BN_CLICKED(IDC_CHECK_TIMER_SEND, OnCheckTimerSend)
	ON_EN_CHANGE(IDC_EDIT_TEMER_PERIOD, OnChangeEditTemerPeriod)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DATA_FORMAT, OnButtonDataFormat)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON__ABOUT_AUTHOR, OnButtonAboutAuthor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialPort_NewDlg message handlers

BOOL CSerialPort_NewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
///////////*************************************************************/////////////////
//�Լ��ĳ�ʼ������
	rxdatacount=0;
	m_bSerialPortOpened=FALSE;
	m_BaudRate=9600;
	data_bit=8;
	stop_bit=1;
	check_bit='N';
	SendDataCount=0;
	timer_send_period=1000;

	tCSerialPort.Hkey2ComboBox(m_combo_com_num);//��������//rxh2.0
	Com_Num=m_nComArray[0];//�ڱ��������д�ע����ж�ȡ�Ĵ��ںŴ洢��m_nComArray[]������
	m_Combo_bandRate.SetCurSel(5);//������Ĭ��9600

	//��ȡ�ؼ���С//rxh2.2
	CRect rect;  
	GetClientRect(&rect);  //
	GetClientRect(&m_rect);  
	oSize.x = rect.right - rect.left;  
	oSize.y = rect.bottom - rect.top;
	//rxh2.6���ý��ձ༭�������С,���������Խ�����ʾ����
	m_editFont.CreatePointFont(90, "������");
	m_edit_receive_data.SetFont(&m_editFont); //����������
	m_edit_receive_data.SetLimitText(-1);//rxh2.7,ȡ���ַ���������
	line_length=0;//rxh2.6
	line_count=0;
	//rxh2.7���ӽ��ջ�����
	receive_buffer=new unsigned char[1024*1024];
	MaxTotalBufNum=1024*1024;//�ܵ��ֽ���
	ctTotalBufNum=0;
	SetTimer(2,55,NULL);//rxh2.7��ʱˢ����ʾ
	receive_data_flag=0;//������ʾ�ͽ���ͬ����ȫ�ֱ���
	m_DlgBackGroundColor.CreateSolidBrush(RGB(154,205,50));//�Զ���һ����ɫ��ˢ
	//rxh2.8�ı䴰�ڵ�͸����
	/*SetWindowLong(this->m_hWnd,GWL_EXSTYLE,GetWindowLong(this->m_hWnd,GWL_EXSTYLE)^0x80000);
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL"));
	if(hInst)
	{
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD);  
		MYFUNC fun = NULL; //ȡ��SetLayeredWindowAttributes����ָ��
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)
		{  
			fun(this->m_hWnd,0,128,2);
		}
		FreeLibrary(hInst);
	}	*/
//	m_check_timer_send.EnableWindow(FALSE);//rxh2.8ʹ��ʱ���Ͳ�����


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSerialPort_NewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialPort_NewDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSerialPort_NewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//��/�رմ���
void CSerialPort_NewDlg::OnButtonOpen() 
{
	m_bSerialPortOpened=!m_bSerialPortOpened;//ȡ����־λ

//	tCSerialPort.Hkey2ComboBox(m_combo_com_num);//�������ڡ����ڶԻ����ʼ��ִ��
	if(m_bSerialPortOpened)//�򿪴���
	{
		if(tCSerialPort.InitPort(this->m_hWnd, Com_Num,m_BaudRate,check_bit,data_bit,stop_bit,EV_RXFLAG | EV_RXCHAR,512))//��ʼ����������ɹ��ͷ���TRUE�����������ж�
		{
			tCSerialPort.StartMonitoring();///���ô���ͨ�ż���̺߳���
			m_bSerialPortOpened=TRUE;//
//			m_check_timer_send.EnableWindow(TRUE);//rxh2.8ʹ��ʱ���Ϳ���

			m_open_serial_port.SetWindowText("�رմ���");//�ڰ�ť����ʾ�ַ���
		}
		else
		{
			m_bSerialPortOpened=FALSE;//��־λȡ��
			CString str;
			str.Format("COM%d û�з��ֻ������豸ռ��",Com_Num);//�ܰ�~~~~~~~~~~~~~~~~~~~~~~~
			AfxMessageBox(str);
		}
	}
	else//�رմ���
	{
		close_port_all();

	}
}
//�رմ��������
void CSerialPort_NewDlg::close_port_all()
{
	KillTimer(1);
	tCSerialPort.ClosePort();//�رմ���   
	m_bSerialPortOpened=FALSE;		
	m_check_timer_send.SetCheck(FALSE);//rxh2.7//ȡ��ѡ�ж�ʱ����
//	m_check_timer_send.EnableWindow(FALSE);//rxh2.8ʹ��ʱ���Ͳ�����
	m_open_serial_port.SetWindowText("�򿪴���");//�ڰ�ť����ʾ�ַ���
	//m_open_serial_port.SetForeColor(RGB(0,155,0));  //���ڴ򿪺��ı���ɫ����
	
}
//���ڽ��յ�����
//ch->���յ����ַ����ݣ�port->���ں�##########################################
LONG CSerialPort_NewDlg::OnCommReceivedata(WPARAM ch, LPARAM port)
{	
	rxdatacount++;  //�ñ������ڽ����ַ�����
	receive_buffer[ctTotalBufNum]=ch;//���뻺����
	ctTotalBufNum++;//rxh2.7������ָ��+1
	receive_data_flag=1;//���յ�����һ
	//�������ch���Ǵ��������ַ������ݣ�����ʹ�õ�����*******************#########


	return 0;
}
//��������
void CSerialPort_NewDlg::OnButtonSend() 
{
	if(!m_bSerialPortOpened) 
	{
		CString str;
		str.Format("COM%d û�д�",Com_Num);//�ܰ�~~~~~~~~~~~~~~~~~~~~~~~
			AfxMessageBox(str);
		return; //��鴮���Ƿ��
	}

	char buf[100];
	memset(buf, 0, sizeof(buf));//��buf�������0�����г�ʼ��

	//���¼��г����ǻ�ñ༭����ı�
	//GetDlgItemText(IDC_EDIT_SEND, buf, sizeof(buf));//�ӱ༭���ȡҪ���͵�����
	//GetDlgItem(IDC_EDIT_SEND)->GetWindowText(buf, sizeof(buf));//����һ��ͬ������������
	m_edit_send_data.GetWindowText(buf, sizeof(buf));//ֱ���÷��Ϳ�Ŀ��Ʊ�����ȡ�ı�
	//SendDlgItemMessage(IDC_EDIT_SEND,WM_GETTEXT,sizeof(buf),(LPARAM)buf);//�Է�����Ϣ���༭��ؼ���ȡ�ı�

	if (strcmp("NOT FOUND", buf) == 0)//�Ƚ��ַ������������ַ�������򷵻�0����str1>str2������������֮���ظ���
		return;
	m_string_send=buf;
	//����Ƿ�16���Ʒ���
	if(m_ctrlHexSend.GetCheck())//ʮ�����Ʒ���//rxh2.1
	{
		char data[512];
		int len=Str2Hex(m_string_send,data);//ʮ������ת��
		tCSerialPort.WriteToPort(data,len); //��������
		SendDataCount+=(long)((m_string_send.GetLength()+1)/3);//���͸�������
	}
	else //�ַ�����
	{
		tCSerialPort.WriteToPort(buf);       //��������
		//tCSerialPort.WriteToPort((LPCTSTR)m_string_send);	//��������

		SendDataCount+=m_string_send.GetLength();//��ȡ�༭���ַ�������(���͸���)
	}
	//��ʾ���ͼ���
	CString strTemp;
	strTemp.Format("����:%d",SendDataCount);
	m_static_send_control.SetWindowText(strTemp);
}
//16����ת������//rxh2.1
char CSerialPort_NewDlg::HexChar(char c)
{
	if((c>='0')&&(c<='9'))
		return c-0x30;
	else if((c>='A')&&(c<='F'))
		return c-'A'+10;
	else if((c>='a')&&(c<='f'))
		return c-'a'+10;
	else 
		return 0x10;
}
//��һ���ַ�����Ϊʮ�����ƴ�ת��Ϊһ���ֽ����飬�ֽڼ���ÿո�ָ���
//����ת������ֽ����鳤�ȣ�ͬʱ�ֽ����鳤���Զ����á�
int CSerialPort_NewDlg::Str2Hex(CString str, char* data)//rxh2.1
{
	int t,t1;
	int rlen=0,len=str.GetLength();
	//data.SetSize(len/2);
	for(int i=0;i<len;)
	{
		char l,h=str[i];
		if(h==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		l=str[i];
		t=HexChar(h);
		t1=HexChar(l);
		if((t==16)||(t1==16))
			break;
		else 
			t=t*16+t1;
		i++;
		data[rlen]=(char)t;
		rlen++;
	}
	return rlen;
	
}
//��ս�����
void CSerialPort_NewDlg::OnButtonClean() 
{
//	m_string_receive.Empty();
	m_edit_receive_data.SetSel(0,-1);//rxh2.8���¸�����շ�ʽ
	m_edit_receive_data.Clear();
	CString strTemp;
	//��ȡ�༭��������
	line_count=m_edit_receive_data.GetLineCount();
	//����
	line_length=m_edit_receive_data.LineLength(1);//��ȡ��һ�г���
	
	//��ʾ������
	strTemp.Format("��:%ld��:%ld ",line_count,line_length);
	//	strTemp="����:"+strTemp;
		m_static_receive_line_count.SetWindowText(strTemp);  //��ʾ��������
	
}
//�������//rxh2.2
void CSerialPort_NewDlg::OnButtonCleanCount() 
{
	rxdatacount=0;
	CString strTemp;
	strTemp.Format("%ld",rxdatacount);
	strTemp="����:"+strTemp;
	m_static_receive_contr.SetWindowText(strTemp);
	SendDataCount=0;
	strTemp.Format("%ld",SendDataCount);
	strTemp="����:"+strTemp;
	m_static_send_control.SetWindowText(strTemp);
	//��ȡ�༭��������
	line_count=m_edit_receive_data.GetLineCount();
	//����
	line_length=m_edit_receive_data.LineLength(1);//��ȡ��һ�г���
	
	//��ʾ������
	strTemp.Format("��:%ld��:%ld ",line_count,line_length);
	//	strTemp="����:"+strTemp;
	m_static_receive_line_count.SetWindowText(strTemp);  //��ʾ��������
	
}

//��������Ͽ�
void CSerialPort_NewDlg::OnSelendokCOMBOBaudRate() 
{
	CString temp;
	int i=m_Combo_bandRate.GetCurSel();//����Ͽ�ѡ�е��ֵ��i
	switch(i)
	{
	case 0:
		i=300;
		break;
	case 1:
		i=600;
		break;
	case 2:
		i=1200;
		break;
	case 3:
		i=2400;
		break;
	case 4:
		i=4800;
		break;
	case 5:
		i=9600;
		break;
	case 6:
		i=19200;
		break;
	case 7:
		i=38400;
		break;
	case 8:
		i=43000;
		break;
	case 9:
		i=56000;
		break;
	case 10:
		i=57600;
		break;
	case 11:
		i=115200;
		break;
	default:
		break;
		
	}
	m_BaudRate=i;//��i��ֵ��ֵ��������
	//�رմ��� 
	close_port_all();
}
//�û��������ں�����չ���б��
void CSerialPort_NewDlg::OnDropdownComboComNum() 
{
	//�رմ��� 
	close_port_all();
	
	//����ɨ��������д���
	tCSerialPort.Hkey2ComboBox(m_combo_com_num);//��������//rxh2.0
	m_combo_com_num.SetCurSel(0);
	Com_Num=m_nComArray[0];//�ڱ��������д�ע����ж�ȡ�Ĵ��ںŴ洢��m_nComArray[]������
	
	
}
//ѡ�񴮿ں�
void CSerialPort_NewDlg::OnSelendokComboComNum() 
{
	unsigned char i;
	//Com_Num=m_combo_com_num.GetCurSel()+1;//���г����������������д��ںŰ���С�������У�����ѡ�д��ں�
	i=m_combo_com_num.GetCurSel();
	Com_Num=m_nComArray[i];//�ڱ��������д�ע����ж�ȡ�Ĵ��ںŴ洢��m_nComArray[]������

}

void CSerialPort_NewDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:	if(!m_bSerialPortOpened) //rxh2.4
			{
				KillTimer(1);//rxh2.6//���رն�ʱ����ǰ������֮ǰ
				CString str;
				str.Format("COM%d û�д�",Com_Num);//�ܰ�~~~~~~~~~~~~~~~~~~~~~~~
				AfxMessageBox(str);
			
				return; //��鴮���Ƿ��
			}
			OnButtonSend();
			//m_edit_receive_data.PostMessage(WM_VSCROLL, SB_BOTTOM,0);//m_edit_receive_data�Ǹ�CRichEdit�����Ŀؼ��ͱ���
		break;
	case 2:display_function();break;//������ʾ��
	}
	CDialog::OnTimer(nIDEvent);
}

//��ʾ����
void CSerialPort_NewDlg::display_function()
{
	CString strTemp;
	//���տ���ʾ����
	if (ctTotalBufNum>0)//�����յ����Ͷ�ʱ��ʱ�䵽����ʾ
	{
		long unsigned int buff_num_temp=ctTotalBufNum;
		if (receive_data_flag==1)//rxh2.8���ڽ���
		{
			if (buff_num_temp>300)///���ÿ�δ�����ʾ300���ֽ�
				buff_num_temp=300;
		}
		else //�������,�����д���ʾ����
		{
			if (buff_num_temp>3000)///���ÿ�δ�����ʾ3000���ֽ�
				buff_num_temp=3000;
		
		}
		for (int i=0;i<buff_num_temp;i++)
		{	
			BYTE bt=*(char*)(receive_buffer+i);
			//ʮ��������ʾ
			if(m_check_hex16_disp.GetCheck())
				strTemp.Format("%02X ",bt);
			else 
				strTemp.Format("%c",bt);//���ַ�������ʱ����strtemp���
			
			//				strTemp.Format("%c",bt);//���ַ�������ʱ����strtemp���
			m_string_receive += strTemp;//�����յ����ַ��ӵ��ַ���
		}
		//�ܻ��崮��
		memmove(receive_buffer,&receive_buffer[i],ctTotalBufNum-i);
		ctTotalBufNum-=i;//�ܻ���ָ�����
		
		m_edit_receive_data.SetSel(-1, -1);//ѡ�б༭���е��ı�
		m_edit_receive_data.ReplaceSel(m_string_receive);//�滻�ı�
		m_string_receive.Empty();//ʹ��������
		//������ʾ��ʣ��û����ʾ������
		if (ctTotalBufNum>0)
		{
			strTemp.Format("%ld",ctTotalBufNum);
			strTemp="�ȴ�:"+strTemp;
			m_static_thread_count_no_use.SetWindowText(strTemp);  //
		}

	}
	else//��Ҫ��ʾ�������Ѿ��������ˣ���ʾһ��������
	{
		//��ȡ�༭��������
		line_count=m_edit_receive_data.GetLineCount();
		
		line_length=m_edit_receive_data.LineLength(1);//��ȡ��һ�г���
		
		//��ʾ������
		strTemp.Format("��:%ld��:%ld ",line_count,line_length);
		//	strTemp="����:"+strTemp;
		m_static_receive_line_count.SetWindowText(strTemp);  //*///��ʾ��������
		//ˢ����ʾ�ȴ����ݸ���
		strTemp.Format("%ld",ctTotalBufNum);
		strTemp="�ȴ�:"+strTemp;
		m_static_thread_count_no_use.SetWindowText(strTemp);  //


	}
	//��ʾ���ռ���	
		
	strTemp.Format("%ld",rxdatacount);
	strTemp="����:"+strTemp;
	m_static_receive_contr.SetWindowText(strTemp);  //��ʾ���ռ���


	receive_data_flag=0;//������ձ�־

}

void CSerialPort_NewDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}
//�Զ������Ի���ؼ��Ĵ�С//rxh2.2
void CSerialPort_NewDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
///////////////////////////////////////////////
//���ϰ汾0���ı����̬�ı�������пؼ���С
/*    if (nType==SIZE_RESTORED || nType==SIZE_MAXIMIZED)  //�����ڽ�������Ϣ�Ǵ��ڴ�С�����������
    {  
		
		float   ratio[2];  
		POINT   newDialogSize;  
		CRect   newRect;  
		
		//��ȡ�µĿͻ����Ĵ�С,Ҳ�������µĶԻ����С
		GetClientRect(&newRect);  
		newDialogSize.x = newRect.right - newRect.left;  //�õ�����ˮƽ��С
		newDialogSize.y = newRect.bottom - newRect.top;  //�õ����ڴ�ֱ�߶�
		
		//�����ڵĶԻ����������Ի���Ĵ�С����  
		ratio[0]    = (float)newDialogSize.x / oSize.x;  //ˮƽ����
		ratio[1]    = (float)newDialogSize.y / oSize.y;  //��ֱ����
		
		CRect Rect;  
		int woc;  
		
		//�������½ǵ�����  
		CPoint OldTLPoint, NewTLPint;  
		CPoint OldBRPoint, NewBRPint;  
		
		//�г����пؼ�  
		HWND  hwndChild = ::GetWindow(m_hWnd,GW_CHILD);  
		
		while(hwndChild)  
		{  
			//ȡ��ID  
			woc  = ::GetDlgCtrlID(hwndChild);  
			GetDlgItem(woc)->GetWindowRect(Rect);  
			ScreenToClient(Rect);  
			
			OldTLPoint = Rect.TopLeft();  
			NewTLPint.x  = long(OldTLPoint.x*ratio[0]);  
			NewTLPint.y  = long(OldTLPoint.y*ratio[1]);  
			
			OldBRPoint   = Rect.BottomRight();  
			NewBRPint.x  = long(OldBRPoint.x*ratio[0]);  
			NewBRPint.y  = long(OldBRPoint.y*ratio[1]);  
			
			Rect.SetRect(NewTLPint,NewBRPint);  
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);  
		}  
		
		//��ȡ��Ƶ���ڸ����ڵĴ�С  
		::GetClientRect(this->m_hWnd, Rect);  
		
		oSize   = newDialogSize;      
		
    }  //*/
///////////////////////////////////////
//���ϰ汾1���ı�һ���ؼ���С�ĳ���
	
	if(nType!=SIZE_MINIMIZED )  //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
	{
		CWnd *pWnd_RX= GetDlgItem(IDC_EDIT_RECEIVE); //��ȡ���տ�ؼ����
		CWnd *pWnd_TX= GetDlgItem(IDC_EDIT_SEND); //��ȡ���Ϳ�ؼ����
		CWnd *pWnd_staticsend= GetDlgItem(IDC_BUTTON_SEND); //��ȡ���Ͱ�ť���
		CWnd *pWnd_HEXsend= GetDlgItem(IDC_CHECK_HEX16_SEND); //��ȡHEX���;��
		static unsigned char flag=0;
		static LONG send_high_temp,send_length_temp,sendbox_to_dialog_left;


		if(pWnd_RX)//�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
		{
			CRect receive_rect; //��ȡ���Ϳ�ؼ��仯ǰ��С
			pWnd_RX->GetWindowRect(&receive_rect);
			ScreenToClient(&receive_rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
			CRect send_rect; //��ȡ���Ϳ�ؼ���С
			pWnd_TX->GetWindowRect(&send_rect);
			ScreenToClient(&send_rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
			CRect static_send_rect; //��ȡ���;�̬�ı���ؼ���С
			pWnd_staticsend->GetWindowRect(&static_send_rect);
			ScreenToClient(&static_send_rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
			CRect hex16_send_rect; //��ȡ16���Ʒ��Ϳؼ���С
			pWnd_HEXsend->GetWindowRect(&hex16_send_rect);
			ScreenToClient(&hex16_send_rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������

			if (flag==0)
			{
				send_high_temp=send_rect.bottom-send_rect.top;//��ȡ���Ϳ�ĸ߶�
				send_length_temp=send_rect.right-send_rect.left;//���Ϳ���

				sendbox_to_dialog_left=send_rect.left-m_rect.left;//��ȡ���Ϳ���Ի�����߽�ľ���
			}
			flag=1;
			
			GetClientRect(&m_rect);//���¶Ի����С


			//���տ����
			receive_rect.left=receive_rect.left;//���տ���߽�///�����ؼ���С
			receive_rect.right=m_rect.right;//���տ��ұ߽�
			receive_rect.top=receive_rect.top;//�ϱ߽�
			receive_rect.bottom=m_rect.bottom-send_high_temp-50;//���տ��±߽�
			//���Ϳ����
			CPoint send_edit_TLpoint,send_edit_BRpoint;//��ȡ���Ϳ�����Ͻ�����
			send_edit_TLpoint.x=m_rect.left+sendbox_to_dialog_left;
			send_edit_TLpoint.y=m_rect.bottom-send_high_temp-10;
			send_edit_BRpoint.x=m_rect.right;
			send_edit_BRpoint.y=m_rect.bottom;
			send_rect.SetRect(send_edit_TLpoint,send_edit_BRpoint);  
			//���Ͱ�ť_����
		//	CPoint send_edit_TLpoint,send_edit_BRpoint;//��ȡ���Ϳ�����Ͻ�����
			send_edit_TLpoint.x=m_rect.left+sendbox_to_dialog_left;
			send_edit_TLpoint.y=m_rect.bottom-send_high_temp-40;
			send_edit_BRpoint.x=m_rect.left+sendbox_to_dialog_left+90;
			send_edit_BRpoint.y=m_rect.bottom-send_high_temp-15;
			static_send_rect.SetRect(send_edit_TLpoint,send_edit_BRpoint); 
			//16���Ʒ��͵���
			send_edit_TLpoint.x=m_rect.left+sendbox_to_dialog_left+120;
			send_edit_TLpoint.y=m_rect.bottom-send_high_temp-37;
			send_edit_BRpoint.x=m_rect.left+sendbox_to_dialog_left+190;
			send_edit_BRpoint.y=m_rect.bottom-send_high_temp-12;
			hex16_send_rect.SetRect(send_edit_TLpoint,send_edit_BRpoint); 


		/*	send_rect.left=send_rect.left;
			send_rect.right=send_rect.right;
			send_rect.top=m_rect.bottom-receive_rect.bottom;
			send_rect.bottom=m_rect.bottom;*/

			pWnd_RX->MoveWindow(receive_rect);//���ÿؼ���С

			pWnd_TX->Invalidate(FALSE);//��ֹ��ť��ʾ���ֺ�����//rxh2.4

			pWnd_TX->MoveWindow(send_rect);

			GetDlgItem(IDC_BUTTON_SEND)->Invalidate(FALSE);//��ֹ��ť��ʾ���ֺ�����
			pWnd_HEXsend->Invalidate(FALSE);//��ֹ��ť��ʾ���ֺ�����

			pWnd_staticsend->MoveWindow(static_send_rect);
			pWnd_HEXsend->MoveWindow(hex16_send_rect);

			line_length=m_edit_receive_data.LineLength(1);//���»�ȡ���տ��һ�г���//rxh2.6
			//��ȡ�༭�����ı�����
			line_count=m_edit_receive_data.GetLineCount();	
			//��ʾ����
			CString strTemp;
			strTemp.Format("��:%ld��:%ld ",line_count,line_length);
			//	strTemp="����:"+strTemp;
			m_static_receive_line_count.SetWindowText(strTemp);  //��ʾ��������
			
			//Invalidate();//rxh2.8ʹ�ͻ�����Ч��ǿ�Ƶ���OnPaintˢ�¿ͻ���
		}
	}//*/
////////////////////////////////////////////////////////////
//���ϰ汾2
/*	if(nType!=SIZE_MINIMIZED )  //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
	{
		ChangeSize(IDC_EDIT_RECEIVE,cx,cy);  /��ÿһ���ؼ�����������
	//	ChangeSize(IDC_EDIT_RECEIVE,cx,cy);
	//	ChangeSize(IDC_EDIT_RECEIVE,cx,cy); 
	//	ChangeSize(IDC_EDIT_RECEIVE,cx,cy); 
		GetClientRect(&m_rect);   //���Ҫ���¶Ի���Ĵ�С��������һ�α仯�ľ����ꣻ
     }//*/
////////////////////////////////////////////////////////////////
	
}
//�ı�ؼ���С�ĺ�������OnSize��������
void CSerialPort_NewDlg::ChangeSize(UINT nID, int x, int y)  //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{
	CWnd *pWnd;
	pWnd=GetDlgItem(nID); 
	if(pWnd!=NULL)     //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
	{
		CRect rec; 
		pWnd->GetWindowRect(&rec);  //��ȡ�ؼ��仯ǰ�Ĵ�С
		ScreenToClient(&rec);   //���ؼ���Сװ��λ�ڶԻ����е���������
		rec.left=rec.left*x/m_rect.Width();  //���ձ��������ռ����λ��
		rec.top=rec.top*y/m_rect.Height();
		rec.bottom=rec.bottom*y/m_rect.Height();
		rec.right=rec.right*x/m_rect.Width();
		pWnd->MoveWindow(rec);   //�����ؼ�
	}
}


//��ʱ����
void CSerialPort_NewDlg::OnCheckTimerSend() //rxh2.4,��ʱ���͹���
{
	if(m_check_timer_send.GetCheck())//��ѡ��ʱ����
	{
		if(m_bSerialPortOpened)//�����Ѿ���
		{
			CString strText;
			m_ctrl_edit_send_period.GetWindowText(strText);//��ȡ�༭���ڵ��ַ���
			timer_send_period=atoi(strText);
			if (timer_send_period<1)
				KillTimer(1);
			else
			SetTimer(1,timer_send_period,NULL);
		}
		else
		{
			m_check_timer_send.SetCheck(FALSE);//rxh2.7//ȡ��ѡ�ж�ʱ����
			CString str;
			str.Format("COM%d û�д�",Com_Num);//�ܰ�~~~~~~~~~~~~~~~~~~~~~~~
			AfxMessageBox(str);

		//	m_check_timer_send.();
			return; //��鴮���Ƿ��
		}

	}
	else
		KillTimer(1);


	
}
//�Ѿ��ı䶨ʱ����
void CSerialPort_NewDlg::OnChangeEditTemerPeriod() //rxh2.4
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString strText;
	m_ctrl_edit_send_period.GetWindowText(strText);
	timer_send_period=atoi(strText);

	if(m_check_timer_send.GetCheck()&&m_bSerialPortOpened)//rxh2.6//��ѡ��ʱ���Ͳ��Ҵ����Ѿ���
	{
		if (timer_send_period<1)
			KillTimer(1);
		else
			SetTimer(1,timer_send_period,NULL);
	}	
}
//�Ի���ر�
void CSerialPort_NewDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(receive_buffer != NULL)//rxh2.8ɾ���Կ��ٵ��ڴ�
    {
        delete [] receive_buffer;
        receive_buffer = NULL;//��ֵ��ָ�룬��ֹ��ɾ�ռ�
    }	
}
//���ڱ�ͻȻ�γ����߷�����ȡ����ȣ��ɼ��߳̽���Ի����ʹ�����Ϣ��������Ӧ����//rxh2.8
void CSerialPort_NewDlg::OnComErrorAndClose()
{	//�رմ���
	close_port_all();
	//����ɨ��������д���
	tCSerialPort.Hkey2ComboBox(m_combo_com_num);//��������//rxh2.0
	m_combo_com_num.SetCurSel(0);
	Com_Num=m_nComArray[0];//�ڱ��������д�ע����ж�ȡ�Ĵ��ںŴ洢��m_nComArray[]������
}
//�ı䱳��ɫ
/*HBRUSH CSerialPort_NewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);//rxh2.8��ʹ��Ĭ�ϵĻ�ˢ
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}*/
//����ͨ�����ݸ�ʽ��ť//rxh2.9
void CSerialPort_NewDlg::OnButtonDataFormat() 
{
	// TODO: Add your control notification handler code here
	//�رմ��� 
	close_port_all();
	
	tDATA_Fomate_Dlg.DoModal();
	
}

//��������
void CSerialPort_NewDlg::OnButtonAboutAuthor() 
{

	m_string_receive="\r\n###############################################################\r\n\r\n\
���������������߻�������Ϣʱ�俪����һ����ٴ���\r\n\r\n\
���д��ں��Զ�ɨ�衢�ನ���ʡ�����λ��У��λ��ֹͣλѡ��\r\n\r\n\
���ڰγ������������ʱ���͡�ʮ�����Ʒ��͡����ա����м����ȹ���\r\n\r\n\
���տ���ա������٣�����鿴��ʷ���ݣ��Զ��洰�����ţ��Զ����С�\r\n\r\n\
���������Ľ��������Ⱥ����\r\n\r\n\
���������������Ⱥ��476174311\r\n\r\n\
���ߵĸ��ٶ�ͨ������ʾ�������ڿ������������ߣ�\r\n\r\n\
��������������Ѵ������ָ����Ŀ���������������\r\n\r\n\
�����������     ֧����:861063204@qq.com\r\n\r\n\
����֧�����Ҽ�����������ǿ������\r\n\
###############################################################\r\n";

	m_edit_receive_data.SetSel(-1, -1);//ѡ�б༭���е��ı�
	m_edit_receive_data.ReplaceSel(m_string_receive);//�滻�ı�
	m_string_receive.Empty();//ʹ��������	
}
