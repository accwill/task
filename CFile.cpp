// CFile1.cpp: 实现文件
//

#include "pch.h"
#include "12.11.tab.h"
#include "CFile.h"
#include "afxdialogex.h"


#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib") //如果没有这行，会出现link错误
// CFile1 对话框

IMPLEMENT_DYNAMIC(CFile1, CDialogEx)

CFile1::CFile1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILE, pParent)
    , m_path(_T("")) {

}

CFile1::~CFile1()
{
}

void CFile1::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list);
    DDX_Control(pDX, IDC_TREE1, m_tree);
    DDX_Text(pDX, IDC_EDIT1, m_path);
}

void CFile1::EnumFile(PCWSTR szPath) {
    WIN32_FIND_DATA findData = { 0 };
    HANDLE hFind = INVALID_HANDLE_VALUE;
    CString temp;
    temp.Format(L"%s\\*", szPath);
    hFind = FindFirstFile(temp, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }
    static CString str[] = {
        L".obj",
        L".tlog",
        L".lastbuildstate",
        L".idb", L".pdb", L".pch", L".res", L".ilk", L".exe", L".sdf", L".ipch", L".log" };
    CString szTemp;
    do {
        szTemp = findData.cFileName;
        CString szFullPath;
        szFullPath.Format(L"%s\\%s", szPath, szTemp);
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (lstrcmp(findData.cFileName, L".") != 0 && lstrcmp(findData.cFileName, L"..") != 0) {
                EnumFile(szFullPath);
            }
        } else {
            for (int i = 0; i < 12; i++) {
                if (szTemp.Find(str[i]) != -1) {
                    if (PathFileExists(szFullPath)) {
                        DeleteFile(szFullPath);
                    }
                    break;
                }
            }
        }
    } while (FindNextFile(hFind, &findData));
}


BEGIN_MESSAGE_MAP(CFile1, CDialogEx)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CFile1::OnSelchangedTree1)
    ON_NOTIFY(NM_CLICK, IDC_TREE1, &CFile1::OnClickTree1)
    ON_BN_CLICKED(IDC_BUTTON1, &CFile1::OnBnClickedButton1)
END_MESSAGE_MAP()


// CFile1 消息处理程序


void CFile1::LoadFile() {
    WIN32_FIND_DATAW FindData;
    HANDLE hFindFile = INVALID_HANDLE_VALUE;
    // 根据坐标获取当前的选中项
    CPoint pos;
    GetCursorPos(&pos);
    m_tree.ScreenToClient(&pos);
    HTREEITEM hItem = m_tree.HitTest(pos);
    if (hItem == NULL) {
        return;
    }
    m_list.DeleteAllItems();
    TCHAR* pData = (TCHAR*)m_tree.GetItemData(hItem);
    CString szPath;
    szPath.Format(L"%s\\*", pData);
    // 遍历
    hFindFile = FindFirstFile(szPath, &FindData);
    if (hFindFile == INVALID_HANDLE_VALUE) {
        return;
    }
    // 先删除
    while (true) {
        HTREEITEM hChildItem = m_tree.GetChildItem(hItem);
        if (hChildItem == NULL) {
            break;
        }
        TCHAR* p = (TCHAR*)m_tree.GetItemData(hChildItem);
        if (p) {
            free(p);
        }
        m_tree.DeleteItem(hChildItem);
    }
    // 计算文件大小为MB
    auto GetFileSize = [](DWORD dwHigh, DWORD dwLow)->CString {
        ULONGLONG liFileSize;
        liFileSize = dwHigh;
        liFileSize += dwLow;
        CString szTemp;
        szTemp.Format(L"%d KB", liFileSize / 1024);
        return szTemp;
    };
    // 转换时间为 yy-mm-dd hh:mm:ss 
    auto ToTime = [](FILETIME* time) -> CString {
        FILETIME ftLocal;
        SYSTEMTIME st;
        CString szTime;
        FileTimeToLocalFileTime(time, &ftLocal);
        FileTimeToSystemTime(&ftLocal, &st);
        szTime.Format(L"%d-%d-%d %d:%d:%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
        return szTime;
    };
    size_t i = 0;
    CString szTemp;
    do {
        // 插入tree
        TCHAR szPathNew[MAX_PATH] = { 0 };
        CString szParentPath = pData;

        // TODO: 图标
        if (szParentPath.Find(L"\\", szParentPath.GetLength() - 1) == -1) {
            _stprintf_s(szPathNew, L"%s\\%s", pData, FindData.cFileName);
        } else {
            _stprintf_s(szPathNew, L"%s%s", pData, FindData.cFileName);
        }

        TCHAR* pszPath = _wcsdup(szPathNew);
        HTREEITEM hInserteItem = m_tree.InsertItem(FindData.cFileName, hItem, TVI_SORT);
        m_tree.SetItemData(hInserteItem, (DWORD_PTR)pszPath);
        // 插入List
        //SHFILEINFO sz = { 0 };
        //SHGetFileInfo(pszPath, FILE_ATTRIBUTE_NORMAL, &sz, sizeof(sz), SHGFI_ICON);
        m_list.InsertItem(i, FindData.cFileName/*, m_imgList.Add(sz.hIcon)*/);
        m_list.SetItemText(i, 1, GetFileSize(FindData.nFileSizeHigh, FindData.nFileSizeLow));
        m_list.SetItemText(i, 2, ToTime(&FindData.ftCreationTime));
        m_list.SetItemText(i, 3, ToTime(&FindData.ftLastWriteTime));
        i++;
    } while (FindNextFile(hFindFile, &FindData));
}

void CFile1::Refresh() {
    TCHAR szDrives[MAX_PATH];
    TCHAR* szDrive;
    GetLogicalDriveStrings(MAX_PATH, szDrives);
    szDrive = szDrives;
    do {
        HTREEITEM hItem = m_tree.InsertItem(szDrive, NULL);
        TCHAR szAbsPath[MAX_PATH] = { 0 };
        _stprintf_s(szAbsPath, L"%s", szDrive);
        TCHAR* pszAbsPath = _wcsdup(szAbsPath);
        m_tree.SetItemData(hItem, (DWORD_PTR)pszAbsPath);
        szDrive += (lstrlen(szDrive) + 1);
    } while (lstrcmp(szDrive, L"\0"));


}

void CFile1::InitList() {
    for (int i = 0; i < m_arrColumns.size(); i++) {
        m_list.InsertColumn(i, m_arrColumns[i], 0, 120);
    }
    DWORD dwStyle = m_list.GetExtendedStyle();
    m_list.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT);
    m_imgList.Create(32, 32, ILC_COLOR32, 4, 1);
    m_list.SetImageList(&m_imgList, LVS_SMALLICON);
    //m_list.SetCallbackMask(LVIS_SELECTED)

}

BOOL CFile1::OnInitDialog() {
    CDialogEx::OnInitDialog();
    Refresh();
    // TODO:  在此添加额外的初始化
    InitList();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void CFile1::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}


void CFile1::OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult) {
    // TODO: 在此添加控件通知处理程序代码
    LoadFile();
    *pResult = 0;
}


void CFile1::OnBnClickedButton1() {
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(true);
    EnumFile(m_path);
}