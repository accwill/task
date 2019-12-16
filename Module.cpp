// Module.cpp: 实现文件
//

#include "pch.h"
#include "12.11.tab.h"
#include "Module.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// Module 对话框

IMPLEMENT_DYNAMIC(Module, CDialogEx)

void Module::InitColumn() {
}

void Module::Refresh() {
    m_list.DeleteAllItems();
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, NULL);
    HANDLE hModule = NULL;
    MODULEENTRY32W md32 = { 0 };
    CString szTemp;
    md32.dwSize = sizeof(MODULEENTRY32W);
    Module32First(hSnap, &md32);
    int i = 0;
    do {
        m_list.InsertItem(i, md32.szModule);
        m_list.SetItemText(i, 1, md32.szExePath);
        szTemp.Format(L"0x%08X", md32.th32ProcessID);
        m_list.SetItemText(i, 2, szTemp);
        szTemp.Format(L"0x%08X", md32.modBaseAddr);
        m_list.SetItemText(i, 3, szTemp);
        szTemp.Format(L"%d", md32.modBaseSize);
        m_list.SetItemText(i, 4, szTemp);
        i++;
    } while (Module32Next(hSnap, &md32));
    CloseHandle(hSnap);
}

Module::Module(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODULE, pParent)
{

}

Module::~Module()
{
}

void Module::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(Module, CDialogEx)
END_MESSAGE_MAP()


// Module 消息处理程序


BOOL Module::OnInitDialog() {
    CDialogEx::OnInitDialog();
    DWORD dwStyle = m_list.GetExtendedStyle();
    m_list.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT);
    for (int i = 0; i < 5; i++) {
        m_list.InsertColumn(i, m_arrMenus[i], LVCFMT_CENTER, 120);
    }
    Refresh();
    // TODO:  在此添加额外的初始化
    return TRUE;  
}
