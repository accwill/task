#pragma once
#include <vector>


// Process 对话框

class Process : public CDialogEx
{
	DECLARE_DYNAMIC(Process)
private:
	std::vector<CString> m_arrColumns = {
		L"进程名称",
		L"进程的ID",
		L"包含的线程数量",
		L"父进程的ID",
		L"路径",
		L"优先级"
	};
	void Refresh();
public:
	Process(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Process();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_list;
	// 选中的进程
	CString m_szCurProcess;
    virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnEndprocess();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
};
