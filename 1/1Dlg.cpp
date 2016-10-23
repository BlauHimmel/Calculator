
// 1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1.h"
#include "1Dlg.h"
#include "afxdialogex.h"
#include "function.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool isFinished = false;	//计算完成后再次输入时会清空文本框

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMy1Dlg 对话框



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


// CMy1Dlg 消息处理程序

BOOL CMy1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO:  在此添加控件通知处理程序代码
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
			Display.Delete(Display.GetLength() - 1, 1);		//删掉当前最后一个字符
	}
	UpdateData(false);
}


void CMy1Dlg::OnBnClickedButton20()		//pow
{
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	Display.Delete(0, Display.GetLength());
	UpdateData(false);
}


void CMy1Dlg::OnBnClickedButton22()		//=
{
	// TODO:  在此添加控件通知处理程序代码
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
		MessageBox(_T("计算式非法！"), _T("错误"), MB_OK);
	}
	isFinished = true;
	UpdateData(false);
}
