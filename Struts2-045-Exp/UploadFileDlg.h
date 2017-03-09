
#pragma once
#include "Exp.h"

// UploadFileDlg �Ի���
class UploadFileDlg : public CDialogEx
{
// ����
public:
	UploadFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPLOADFILE_DIALOG};

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
	CString editTextResult;
	CString editTextWriteData;
	Exp exp;

public:
	afx_msg void OnBnClickedGetrootpath();
	afx_msg void OnBnClickedWritebtn();
private:
	CString editTextWritePath;
};
