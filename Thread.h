#pragma once

#include <TlHelp32.h>
#include <vector>
// Thread 对话框

class Thread : public CDialogEx
{
	DECLARE_DYNAMIC(Thread)
private:
	CString m_arrMenus[3] = {
		L"线程ID",
		L"线程优先级",
		L"所属进程",
	};
	CString m_szCurThreadID;
	void Refresh();
public:
	Thread(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Thread();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_list;
    virtual BOOL OnInitDialog();
    afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnEndThread();
    afx_msg void OnSuspendThread();
    afx_msg void OnResumeThread();
};
