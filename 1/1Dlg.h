
// 1Dlg.h : ͷ�ļ�
//

#pragma once


// CMy1Dlg �Ի���
class CMy1Dlg : public CDialogEx
{
// ����
public:
	CMy1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY1_DIALOG };

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
	afx_msg void DisplayFlash(UINT uID);
	DECLARE_MESSAGE_MAP()
public:
	//��ʾ��ʽ
	CString Display;
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton22();
};
