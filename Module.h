#pragma once


// Module 对话框

class Module : public CDialogEx
{
	DECLARE_DYNAMIC(Module)

private:
	CString m_arrMenus[5] = {
		L"模块的名称",
		L"执行地址",
		L"进程ID",
		L"基址",
		L"占用字节数"
	};
	void InitColumn();
	void Refresh();

public:
	Module(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Module();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
};
