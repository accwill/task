#pragma once
#include <vector>


// CWIndows 对话框

class CWIndows : public CDialogEx
{
	DECLARE_DYNAMIC(CWIndows)
private:
	std::vector<CString> m_arrColumns = {
		L"窗口名称",
		L"窗口句柄",
		L"窗口类",
		L"句柄路径"
	};
	void Refresh();
	void EnumWindows();
public:
	CWIndows(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CWIndows();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOWS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
};
