
// Struts2-045-ExpDlg.h : ͷ�ļ�
//

#pragma once
#include "CommandDlg.h"
#include "UploadFileDlg.h"
#include "GetshellDlg.h"

// CStruts2045ExpDlg �Ի���
class CStruts2045ExpDlg : public CDialogEx
{
// ����
public:
	CStruts2045ExpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STRUTS2045EXP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CTabCtrl funcTab;
	CommandDlg commandDlg; //����ִ�жԻ���
	UploadFileDlg uploadFileDlg; //�ϴ��ļ��Ի���
	GetshellDlg getshellDlg; //GETSHELL�Ի���
	int currTab; //��ǰTABҳ
	CDialogEx* tabDlgs[3];//TAB���жԻ���
public:
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
};
