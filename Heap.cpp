// Heap.cpp: 实现文件
//

#include "pch.h"
#include "12.11.tab.h"
#include "Heap.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

// Heap 对话框

IMPLEMENT_DYNAMIC(Heap, CDialogEx)

void Heap::Refresh() {
    m_list.DeleteAllItems();
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, NULL);
    HEAPLIST32 hp32 = { 0 };
    hp32.dwSize = sizeof(HEAPLIST32);
    Heap32ListFirst(hSnap, &hp32);
    CString szTemp;

    do {

        szTemp.Format(L"%u", hp32.th32HeapID);
        m_list.InsertItem(0, szTemp);
        szTemp.Format(L"%d", hp32.th32ProcessID);
        m_list.SetItemText(0, 1, szTemp);

        HEAPENTRY32 he;
        ZeroMemory(&he, sizeof(HEAPENTRY32));
        he.dwSize = sizeof(HEAPENTRY32);
        //if (Heap32First(&he, GetCurrentProcessId(), he.th32HeapID)) {
        //    szTemp.Format(L"0x%08X", he.dwAddress);
        //    m_list.SetItemText(0, 2, szTemp);
        //    szTemp.Format(L"%lf", he.dwBlockSize / 1024 / 1024);
        //    m_list.SetItemText(0, 3, szTemp);
        //}

        hp32.dwSize = sizeof(HEAPLIST32);
    } while (Heap32ListNext(hSnap, &hp32));
    CloseHandle(hSnap);
}

Heap::Heap(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HEAP, pParent)
{

}

Heap::~Heap()
{
}

void Heap::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(Heap, CDialogEx)
    ON_NOTIFY(NM_RCLICK, IDC_LIST1, &Heap::OnRclickList1)
END_MESSAGE_MAP()


// Heap 消息处理程序


BOOL Heap::OnInitDialog() {
    CDialogEx::OnInitDialog();

    DWORD dwStyle = m_list.GetExtendedStyle();
    m_list.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT);
    for (int i = 0; i < 2; i++) {
        m_list.InsertColumn(i, m_arrColumns[i], LVCFMT_CENTER, 120);
    }
    Refresh();


    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void Heap::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}
