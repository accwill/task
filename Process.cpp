// Process.cpp: 实现文件
//

#include "pch.h"
#include "12.11.tab.h"
#include "Process.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// Process 对话框

IMPLEMENT_DYNAMIC(Process, CDialogEx)

void Process::Refresh() {
    m_list.DeleteAllItems();
    PROCESSENTRY32W oPro32 = { 0 };
    oPro32.dwSize = sizeof(PROCESSENTRY32W);

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    HANDLE hProcess = NULL;
    DWORD dwPriority;
    CString szTemp;
    BOOL isSuccess = Process32First(hSnap, &oPro32);
    if (!isSuccess) {
        return;
    }
    int i = 0;
    TCHAR szPath[MAX_PATH];
    DWORD dwSize = MAX_PATH;
    ZeroMemory(szPath, MAX_PATH);
    do {
        //m_list.
        m_list.InsertItem(i, oPro32.szExeFile, LVM_SORTITEMS);
        szTemp.Format(L"%d", oPro32.th32ProcessID);
        m_list.SetItemText(i, 1, szTemp);
        szTemp.Format(L"%d", oPro32.cntThreads);
        m_list.SetItemText(i, 2, szTemp);
        szTemp.Format(L"%d", oPro32.th32ParentProcessID);
        m_list.SetItemText(i, 3, szTemp);

        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, oPro32.th32ProcessID);
        if (hProcess != NULL) {
            dwPriority = GetPriorityClass(hProcess);
            QueryFullProcessImageName(hProcess, 0, szPath, &dwSize);
        } else {
            dwPriority = INFINITE;
            ZeroMemory(szPath, MAX_PATH);
        }
        szTemp.Format(L"%d", dwPriority);

        m_list.SetItemText(i, 4, szPath);
        m_list.SetItemText(i, 5, szTemp);
        i++;
    } while (Process32Next(hSnap, &oPro32));
    CloseHandle(hSnap);
}

Process::Process(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROCESS, pParent)
{

}

Process::~Process()
{
}

void Process::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(Process, CDialogEx)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Process::OnLvnItemchangedList1)
    ON_COMMAND(ID_ENDPROCESS, &Process::OnEndprocess)
    ON_WM_RBUTTONDOWN()
    ON_NOTIFY(NM_RCLICK, IDC_LIST1, &Process::OnRclickList1)
END_MESSAGE_MAP()


// Process 消息处理程序


BOOL Process::OnInitDialog() {
    CDialogEx::OnInitDialog();
    DWORD dwStyle = m_list.GetExtendedStyle();

    size_t nCount = m_arrColumns.size();

    for (size_t i = 0; i < nCount; i++) {
        m_list.InsertColumn(i, m_arrColumns[i], 0, 120);
    }
    m_list.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT);

    // TODO:  在此添加额外的初始化
    Refresh();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void Process::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}


void Process::OnEndprocess() {
    // TODO: 在此添加命令处理程序代码
    DWORD dwProcessID;
    _stscanf_s(m_szCurProcess, L"%d", &dwProcessID);
    HANDLE hProcess = INVALID_HANDLE_VALUE;
    hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);
    if (hProcess == NULL) {
        MessageBox(L"结束进程失败");
        return;
    }
    ::TerminateProcess(hProcess, 0);
    Refresh();
}


void Process::OnRButtonDown(UINT nFlags, CPoint point) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CDialogEx::OnRButtonDown(nFlags, point);
}


void Process::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    NMITEMACTIVATE* ItemActivate = (NMITEMACTIVATE*)pNMHDR;
    TCHAR szText[MAX_PATH] = { 0 };
    ListView_GetItemText(m_list.m_hWnd, ItemActivate-> iItem, 1, szText, MAX_PATH);
    m_szCurProcess = szText;
    CMenu cMenu;
    cMenu.LoadMenu(IDR_MENU1);
    CMenu* pSubMenu = cMenu.GetSubMenu(0);
    CPoint cPoint;
    ::GetCursorPos(&cPoint);
    TrackPopupMenu(pSubMenu->m_hMenu, TPM_LEFTALIGN, cPoint.x, cPoint.y, NULL, this->m_hWnd, NULL);
    *pResult = 0;
}
