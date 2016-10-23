
// 1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1.h"
#include "1Dlg.h"
#include "afxdialogex.h"
#include "function.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool isFinished = false;	//������ɺ��ٴ�����ʱ������ı���

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy1Dlg �Ի���



CMy1Dlg::CMy1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy1Dlg::IDD, pParent)
	, Display(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Display);
}

BEGIN_MESSAGE_MAP(CMy1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON1, IDC_BUTTON0, &CMy1Dlg::DisplayFlash)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON11, IDC_BUTTON19, &CMy1Dlg::DisplayFlash)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON21, IDC_BUTTON21, &CMy1Dlg::DisplayFlash)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON24, IDC_BUTTON25, &CMy1Dlg::DisplayFlash)
	
	ON_BN_CLICKED(IDC_BUTTON10, &CMy1Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON20, &CMy1Dlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON23, &CMy1Dlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON22, &CMy1Dlg::OnBnClickedButton22)
END_MESSAGE_MAP()


// CMy1Dlg ��Ϣ�������

BOOL CMy1Dlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy1Dlg::OnPaint()
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
HCURSOR CMy1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy1Dlg::DisplayFlash(UINT uID)
{
	UpdateData(true);
	if (isFinished)
		Display.Delete(0, Display.GetLength());
	UpdateData(false);

	isFinished = false;

	UpdateData(true);
	CString temp;
	GetDlgItem(uID)->GetWindowTextW(temp);
	Display += temp;
	if (uID >= 1016 && uID <= 1019)
		Display += '(';
	UpdateData(false);
}


void CMy1Dlg::OnBnClickedButton10()	//DEL
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (Display.GetLength() > 0)
	{
		if (Display[Display.GetLength() - 1] == 'n'&&Display[Display.GetLength() - 2] == 'i'&&Display[Display.GetLength() - 3] == 's')
			Display.Delete(Display.GetLength() - 3, 3);
		else if (Display[Display.GetLength() - 1] == 's'&&Display[Display.GetLength() - 2] == 'o'&&Display[Display.GetLength() - 3] == 'c')
			Display.Delete(Display.GetLength() - 3, 3);
		else if (Display[Display.GetLength() - 1] == 'n'&&Display[Display.GetLength() - 2] == 'a'&&Display[Display.GetLength() - 3] == 't')
			Display.Delete(Display.GetLength() - 3, 3);
		else if (Display[Display.GetLength() - 1] == 't'&&Display[Display.GetLength() - 2] == 'r'&&Display[Display.GetLength() - 3] == 'q'&&Display[Display.GetLength() - 4] == 's')
			Display.Delete(Display.GetLength() - 4, 4);
		else
			Display.Delete(Display.GetLength() - 1, 1);		//ɾ����ǰ���һ���ַ�
	}
	UpdateData(false);
}


void CMy1Dlg::OnBnClickedButton20()		//pow
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (isFinished)
		Display.Delete(0, Display.GetLength());
	UpdateData(false);
	isFinished = false;
	UpdateData(true);
	Display += '^';
	UpdateData(false);
}


void CMy1Dlg::OnBnClickedButton23()		//AC
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	Display.Delete(0, Display.GetLength());
	UpdateData(false);
}


void CMy1Dlg::OnBnClickedButton22()		//=
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	Display += '=';
	char* expression = new char[Display.GetLength() + 1];
	for (int i = 0; i < Display.GetLength(); i++)
	{
		expression[i] = Display[i];
	}
	expression[Display.GetLength()] = '\0';
	double result;
	CString temp;
	if (calculate(expression, result))
	{
		temp.Format(_T("%lf"), result);
		 Display += temp;
	}
	else
	{
		MessageBox(_T("����ʽ�Ƿ���"), _T("����"), MB_OK);
	}
	isFinished = true;
	UpdateData(false);
}
