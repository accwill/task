// Thread.cpp: 实现文件
//

#include "pch.h"
#include "12.11.tab.h"
#include "Thread.h"
#include "afxdialogex.h"


// Thread 对话框

IMPLEMENT_DYNAMIC(Thread, CDialogEx)

void Thread::Refresh() {
    m_list.DeleteAllItems();
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
    HANDLE hThread = NULL;
    THREADENTRY32 th32 = { 0 };
    CString szTemp;
    th32.dwSize = sizeof(THREADENTRY32);
    Thread32First(hSnap, &th32);
    int i = 0;
    do {
        szTemp.Format(L"%d", th32.th32ThreadID);
        m_list.InsertItem(i, szTemp);
        szTemp.Format(L"%d", th32.th32OwnerProcessID);
        m_list.SetItemText(i, 1, szTemp);
        szTemp.Format(L"%d", th32.tpBasePri);
        m_list.SetItemText(i, 2, szTemp);
        i++;
    } while (Thread32Next(hSnap, &th32));
    CloseHandle(hSnap);
}

Thread::Thread(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THREAD, pParent)
{

}

Thread::~Thread()
{
}

void Thread::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(Thread, CDialogEx)
    ON_NOTIFY(NM_RCLICK, IDC_LIST1, &Thread::OnRclickList1)
    ON_COMMAND(32772, &Thread::OnEndThread)
    ON_COMMAND(32773, &Thread::OnSuspendThread)
    ON_COMMAND(32774, &Thread::OnResumeThread)
END_MESSAGE_MAP()


// Thread 消息处理程序


BOOL Thread::OnInitDialog() {
    CDialogEx::OnInitDialog();
    for (int i = 0; i < 3; i++) {
        m_list.InsertColumn(i, m_arrMenus[i], LVCFMT_CENTER, 120);
    }
    DWORD dwStyle = m_list.GetExtendedStyle();
    m_list.SetExtendedStyle(dwStyle | TVS_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT);
    Refresh();
    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void Thread::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    CMenu cMenu;
    cMenu.LoadMenu(IDR_MENU2);
    CMenu* pMenu = cMenu.GetSubMenu(0);
    CPoint cPoint;
    GetCursorPos(&cPoint);
    TrackPopupMenu(pMenu->m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON, cPoint.x, cPoint.y, 0, this->m_hWnd, NULL);
    TCHAR szThreadID[MAX_PATH];

    ListView_GetItemText(m_list.m_hWnd, pNMItemActivate->iItem, 0, szThreadID, MAX_PATH);
    m_szCurThreadID = szThreadID;
    *pResult = 0;
}


void Thread::OnEndThread() {
    // TODO: 在此添加命令处理程序代码
    DWORD dwthreadID;
    _stscanf_s(m_szCurThreadID, L"%d", &dwthreadID);

    HANDLE hThread = OpenThread(NULL, FALSE, dwthreadID);
    if (hThread == NULL) {
        MessageBox(L"操作失败");
        return;
    }
    TerminateThread(hThread, 0);
    Refresh();
}


void Thread::OnSuspendThread() {
    // TODO: 在此添加命令处理程序代码
    DWORD dwthreadID;
    _stscanf_s(m_szCurThreadID, L"%d", &dwthreadID);

    HANDLE hThread = OpenThread(NULL, FALSE, dwthreadID);
    if (hThread == NULL) {
        MessageBox(L"操作失败");
        return;
    }
    SuspendThread(hThread);
}


void Thread::OnResumeThread() {
    // TODO: 在此添加命令处理程序代码
    DWORD dwthreadID;
    _stscanf_s(m_szCurThreadID, L"%d", &dwthreadID);

    HANDLE hThread = OpenThread(NULL, FALSE, dwthreadID);
    if (hThread == NULL) {
        MessageBox(L"操作失败");
        return;
    }
    ResumeThread(hThread);
}