
// Struts2-045-ExpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Struts2-045-Exp.h"
#include "CommandDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���


// CommandDlg �Ի���



CommandDlg::CommandDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CommandDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, editTextURL);
	DDX_Text(pDX, IDC_EDIT2, editTextCommand);
	DDX_Text(pDX, IDC_EDIT3, editTextResult);
}

BEGIN_MESSAGE_MAP(CommandDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CommandDlg::OnExecuteBtnClicked)
END_MESSAGE_MAP()


// CommandDlg ��Ϣ�������

BOOL CommandDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	editTextCommand = "whoami"; //Ĭ������
	UpdateData(false);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CommandDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CommandDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CommandDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CommandDlg::OnExecuteBtnClicked() //ִ�� ��ť ����¼�
{
	UpdateData(true); //ͬ����������ֵ
	CString url = editTextURL;
	url.Replace("\r",""); //ɾ���س��������޷���ȷ����
	url.Replace("\n",""); //ɾ�����У������޷���ȷ����
	CString command = editTextCommand;
	command.Replace("\r",""); //ɾ���س��������޷���ȷ����
	command.Replace("\n",""); //ɾ�����У������޷���ȷ����
	if(url.IsEmpty()) //���URL�����Ϊ��
	{
		MessageBox("������URL","����");
		return;
	}
	if(command.IsEmpty()) //������������Ϊ��
	{
		MessageBox("������ִ������","����");
		return;
	}
	
	editTextResult = exp.executeCommand(url,command);
	editTextResult.Replace("\n","\r\n"); //���з� �滻������CEDIT�ؼ����ܻ�����ʾ
	UpdateData(false); //ͬ����������ֵ
}
