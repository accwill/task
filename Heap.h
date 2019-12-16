#pragma once


// Heap 对话框

class Heap : public CDialogEx
{
	DECLARE_DYNAMIC(Heap)
private:
	CString m_arrColumns[4] = {
		L"堆标识符",
		L"进程标识符",
		L"开始的线性地址",
		L"大小(MB)"
	};
	void Refresh();
public:
	Heap(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Heap();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HEAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMenu m_cMenu;
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
    afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
};
