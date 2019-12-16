// CWIndows.cpp: 实现文件
//

#include "pch.h"
#include "12.11.tab.h"
#include "CWIndows.h"
#include "afxdialogex.h"

int i = 0;

BOOL CALLBACK WndProcCallback(HWND hWnd, LPARAM l) {
    CWIndows* pWin = (CWIndows*)l;
    TCHAR szPath[MAX_PATH];
    TCHAR szClass[MAX_PATH];
    TCHAR szName[MAX_PATH];
    CString szHandel;
    ZeroMemory(szPath, MAX_PATH);
    ZeroMemory(szClass, MAX_PATH);
    ZeroMemory(szName, MAX_PATH);
    ::GetWindowText(hWnd, szName, MAX_PATH);
    RealGetWindowClass(hWnd, szClass, MAX_PATH);
    GetWindowModuleFileName(hWnd, szPath, MAX_PATH);
    szHandel.Format(L"0x%x", hWnd);

    pWin->m_list.InsertItem(i, szName);
    pWin->m_list.SetItemText(i, 1, szHandel);
    pWin->m_list.SetItemText(i, 2, szClass);
    pWin->m_list.SetItemText(i, 3, szPath);
    i++;
    return TRUE;
}

// CWIndows 对话框

IMPLEMENT_DYNAMIC(CWIndows, CDialogEx)

void CWIndows::Refresh() {
    i = 0;
    m_list.DeleteAllItems();
    EnumWindows();
}

void CWIndows::EnumWindows() {
    //typedef BOOL(CALLBACK* WNDENUMPROC)(HWND, LPARAM);
    ::EnumWindows(WndProcCallback, LPARAM(this));
}

CWIndows::CWIndows(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDOWS, pParent)
{

}

CWIndows::~CWIndows()
{
}

void CWIndows::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CWIndows, CDialogEx)
END_MESSAGE_MAP()


// CWIndows 消息处理程序


BOOL CWIndows::OnInitDialog() {
    CDialogEx::OnInitDialog();

    DWORD dwStyle = m_list.GetExtendedStyle();

    size_t nCount = m_arrColumns.size();

    for (size_t i = 0; i < nCount; i++) {
        m_list.InsertColumn(i, m_arrColumns[i], 0, 120);
    }
    m_list.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT);

    // TODO:  在此添加额外的初始化
    Refresh();

    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}
