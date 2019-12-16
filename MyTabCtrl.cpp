// MyTabCtrl.cpp: 实现文件
//

#include "pch.h"
#include "12.11.tab.h"
#include "MyTabCtrl.h"


// MyTabCtrl

IMPLEMENT_DYNAMIC(MyTabCtrl, CTabCtrl)

MyTabCtrl::MyTabCtrl() {

}

MyTabCtrl::~MyTabCtrl()  {
}

void MyTabCtrl::AddTab(const CString& title, CDialogEx* pDialog) {
    InsertItem(m_subWnds.size(), title);

    m_subWnds.push_back(pDialog);

    SetWindowLong(pDialog->m_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    pDialog->SetParent(this);


    CRect rect;
    // 获取选项卡的大小
    GetClientRect(&rect);
    rect.DeflateRect(2, 25, 2, 2);
    // 将子窗口的窗口位置和大小进行修改
    pDialog->MoveWindow(rect);

    // 设置为第一个展示
    if (m_subWnds.size() == 1) {
        m_subWnds[0]->ShowWindow(SW_SHOW);
        return;
    }
    pDialog->ShowWindow(SW_HIDE);
    // 设置背景色
    //SetClassLong(cdlg->m_hWnd, (-10), (long)CreateSolidBrush(COLOR_BACKGROUND));
}


BEGIN_MESSAGE_MAP(MyTabCtrl, CTabCtrl)
    ON_NOTIFY_REFLECT(TCN_SELCHANGE, &MyTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()


// MyTabCtrl 消息处理程序




void MyTabCtrl::OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult) {
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
    DWORD dwCurSel = GetCurSel();
    m_subWnds[m_nPrevTabIndex]->ShowWindow(SW_HIDE);
    m_subWnds[dwCurSel]->ShowWindow(SW_SHOW);
    m_nPrevTabIndex = dwCurSel;
}
