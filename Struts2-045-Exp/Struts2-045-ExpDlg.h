
// Struts2-045-ExpDlg.h : ͷ�ļ�
//

#pragma once


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
	CString editTextURL;
	CString editTextCommand;
	CString editTextResult;
public:
	afx_msg void OnExecuteBtnClicked();
};
