
// 12.11.tabDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "12.11.tab.h"
#include "12.11.tabDlg.h"
#include "afxdialogex.h"
#include "Process.h"
#include "Thread.h"
#include "Module.h"
#include "Heap.h"
#include "CPUMemory.h"
#include "CWIndows.h"
#include "CFile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy1211tabDlg 对话框



CMy1211tabDlg::CMy1211tabDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY1211TAB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1211tabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
}

BEGIN_MESSAGE_MAP(CMy1211tabDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CMy1211tabDlg::OnSelchangeTab)
END_MESSAGE_MAP()


// CMy1211tabDlg 消息处理程序

BOOL CMy1211tabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CDialogEx* pDlg = nullptr;
	pDlg = new Process;
	pDlg->Create(IDD_PROCESS);
	m_tab.AddTab(L"进程", pDlg);
	pDlg = new Thread;
	pDlg->Create(IDD_THREAD);
	m_tab.AddTab(L"线程", pDlg);
	pDlg = new Module;
	pDlg->Create(IDD_MODULE);
	m_tab.AddTab(L"模块", pDlg);
	pDlg = new Heap;
	pDlg->Create(IDD_HEAP);
	m_tab.AddTab(L"堆", pDlg);
	pDlg = new CPUMemory;
	pDlg->Create(IDD_CPUMEM);
	m_tab.AddTab(L"CPU和内存", pDlg);
	pDlg = new CWIndows;
	pDlg->Create(IDD_WINDOWS);
	m_tab.AddTab(L"窗口", pDlg);
	pDlg = new CFile1;
	pDlg->Create(IDD_FILE);
	m_tab.AddTab(L"文件", pDlg);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy1211tabDlg::OnPaint()
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
HCURSOR CMy1211tabDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CMy1211tabDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) {
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}
