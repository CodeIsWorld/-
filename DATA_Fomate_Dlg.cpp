// DATA_Fomate_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialPort_New.h"
#include "DATA_Fomate_Dlg.h"
#include "SerialPort_NewDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DATA_Fomate_Dlg dialog


DATA_Fomate_Dlg::DATA_Fomate_Dlg(CWnd* pParent /*=NULL*/)
: CDialog(DATA_Fomate_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DATA_Fomate_Dlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DATA_Fomate_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DATA_Fomate_Dlg)
	DDX_Control(pDX, IDC_COMBO_STOP_BIT, m_combo_stop_bit);
	DDX_Control(pDX, IDC_COMBO_CHECK_BIT, m_combo_check_bit);
	DDX_Control(pDX, IDC_COMBO_DATA_BIT, m_combo_data_bit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DATA_Fomate_Dlg, CDialog)
//{{AFX_MSG_MAP(DATA_Fomate_Dlg)
ON_CBN_SELENDOK(IDC_COMBO_DATA_BIT, OnSelendokComboDataBit)
	ON_CBN_SELENDOK(IDC_COMBO_STOP_BIT, OnSelendokComboStopBit)
	ON_CBN_SELENDOK(IDC_COMBO_CHECK_BIT, OnSelendokComboCheckBit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL DATA_Fomate_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//	data_bit=8;
	switch (CSerialPort_NewDlg::data_bit)//rxh2.9
	{
	case 5:m_combo_data_bit.SetCurSel(0);break;//����λĬ��Ϊ5λ	
	case 6:m_combo_data_bit.SetCurSel(1);break;//����λĬ��Ϊ6λ	
	case 7:m_combo_data_bit.SetCurSel(2);break;//����λĬ��Ϊ7λ	
	case 8:m_combo_data_bit.SetCurSel(3);break;//����λĬ��Ϊ8λ	

	}
	switch (CSerialPort_NewDlg::stop_bit)
	{
	case 1:m_combo_stop_bit.SetCurSel(0);break;//ֹͣλ1λ	
	case 2:m_combo_stop_bit.SetCurSel(1);break;//ֹͣλ2λ		
		
	}
	switch (CSerialPort_NewDlg::check_bit)//rxh2.9
	{
	case 'N':m_combo_check_bit.SetCurSel(0);break;//Ĭ����У��
	case 'O':m_combo_check_bit.SetCurSel(1);break;//��У��	
	case 'E':m_combo_check_bit.SetCurSel(2);break;//żУ��		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// DATA_Fomate_Dlg message handlers
//����λѡ���ѡ��
void DATA_Fomate_Dlg::OnSelendokComboDataBit() 
{
	unsigned char i;
	//Com_Num=m_combo_com_num.GetCurSel()+1;//���г����������������д��ںŰ���С�������У�����ѡ�д��ں�
	i=m_combo_data_bit.GetCurSel();
	switch (i)
	{
	case 0:i=5;break;
	case 1:i=6;break;
	case 2:i=7;break;
	case 3:i=8;break;
	}
	CSerialPort_NewDlg::data_bit=i;//����λ��ֵ��ȫ�ֱ���
	
}

void DATA_Fomate_Dlg::OnSelendokComboStopBit() 
{
	unsigned char i=1;
	i=m_combo_stop_bit.GetCurSel();
	switch (i)
	{
	case 0:i=1;break;
	case 1:i=2;break;
	}
	CSerialPort_NewDlg::stop_bit=i;//����λ��ֵ��ȫ�ֱ���	
}
//��żУ��λ
void DATA_Fomate_Dlg::OnSelendokComboCheckBit() 
{
	char temp;
	int i=m_combo_check_bit.GetCurSel();
	switch(i)
	{
	case 0:
		temp='N';//��У��
		break;
	case 1:
		temp='O';//��У��
		break;
	case 2:
		temp='E';//żУ��
		break;
	}
	CSerialPort_NewDlg::check_bit=temp;	
}
