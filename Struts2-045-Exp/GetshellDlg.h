
#pragma once
#include "Exp.h"

// GetshellDlg �Ի���
class GetshellDlg : public CDialogEx
{
// ����
public:
	GetshellDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GETSHELL_DIALOG};

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
	Exp exp;
	CString editTextURL;
	CString editTextShellName;
	CString editTextShellData;
	CString editTextResult;
	CString shellDefaultName; //SHELLĬ����
	CString shellDefaultData; //SHELLĬ������
	CString shellDefaultPwd; //SHELLĬ������
	CString getJspRes(UINT resId); //��ȡJSP��Դ
public:
	afx_msg void OnBnClickedGetshell();
};
