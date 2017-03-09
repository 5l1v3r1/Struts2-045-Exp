
// Struts2-045-ExpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Struts2-045-Exp.h"
#include "UploadFileDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���


// UploadFileDlg �Ի���



UploadFileDlg::UploadFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(UploadFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void UploadFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WRITEURL, editTextURL);
	DDX_Text(pDX, IDC_WRITERESULT, editTextResult);
	DDX_Text(pDX, IDC_WRITEDATA, editTextWriteData);
	DDX_Text(pDX, IDC_WRITEPATH, editTextWritePath);
}

BEGIN_MESSAGE_MAP(UploadFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETROOTPATH, &UploadFileDlg::OnBnClickedGetrootpath)
	ON_BN_CLICKED(IDC_WRITEBTN, &UploadFileDlg::OnBnClickedWritebtn)
END_MESSAGE_MAP()


// UploadFileDlg ��Ϣ�������

BOOL UploadFileDlg::OnInitDialog()
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void UploadFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void UploadFileDlg::OnPaint()
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
HCURSOR UploadFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void UploadFileDlg::OnBnClickedGetrootpath() //��ȡ��Ŀ¼��ť�¼�
{
	UpdateData(true);
	if(editTextURL.IsEmpty()) // URL����Ϊ��
	{
		MessageBox("������URL","����");
		return;
	}
	DWORD statusCode;
	CString url = editTextURL;
	url.Replace("\r",""); //ɾ���س��������޷���ȷ����
	url.Replace("\n",""); //ɾ�����У������޷���ȷ����
	CString getRootPathResult = exp.getRootPath(url,statusCode);
	if(statusCode == 200) //��ȡ�ɹ�
	{
		editTextWritePath = getRootPathResult;
		editTextResult = "��ȡ��վ��Ŀ¼�ɹ�";
	}
	else
		editTextResult = getRootPathResult;
	editTextResult.Replace("\n","\r\n"); //���з� �滻������CEDIT�ؼ����ܻ�����ʾ
	UpdateData(false);
}


void UploadFileDlg::OnBnClickedWritebtn() //д�밴ť�¼�
{
	UpdateData(true);
	CString url = editTextURL;
	url.Replace("\r",""); //ɾ���س��������޷���ȷ����
	url.Replace("\n",""); //ɾ�����У������޷���ȷ����
	CString writePath = editTextWritePath;
	writePath.Replace("\\","/"); //�ָ���ͳһ���� /������Struts2�޷���ȷд�ļ�
	writePath.Replace("\r",""); //ɾ���س�������Struts2�޷���ȷд�ļ�
	writePath.Replace("\n",""); //ɾ�����У�����Struts2�޷���ȷд�ļ�
	if(url.IsEmpty()) // URL����Ϊ��
	{
		MessageBox("������URL","����");
		return;
	}
	if(writePath.IsEmpty()) //д��·��Ϊ��
	{
		MessageBox("������д��·��","����");
		return;
	}
	char lastChar = writePath.GetAt(writePath.GetLength()-1); //��ȡд��·�����һ���ַ�
	if(lastChar == '/' || lastChar == '\\' || lastChar == '.') //·������ȷ
	{
		MessageBox("������д��·�����ļ���","����");
		return;
	}
	
	editTextResult = exp.writeFile(url,writePath,editTextWriteData);//д�ļ�
	editTextResult.Replace("\n","\r\n"); //���з� �滻������CEDIT�ؼ����ܻ�����ʾ
	UpdateData(false);
}
