
// Struts2-045-ExpDlg.h : ͷ�ļ�
//

#pragma once
#include "Exp.h"

// CommandDlg �Ի���
class CommandDlg : public CDialogEx
{
// ����
public:
	CommandDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMMAND_DIALOG};

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
	CString editTextURL;
	CString editTextCommand;
	CString editTextResult;
	Exp exp;
public:
	afx_msg void OnExecuteBtnClicked();
};
