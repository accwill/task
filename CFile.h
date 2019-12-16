#pragma once
#include <vector>


// CFile1 对话框

class CFile1 : public CDialogEx
{
	DECLARE_DYNAMIC(CFile1)

public:
	CFile1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFile1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void EnumFile(PCWSTR szPath);
	std::vector<CString> m_arrColumns = {
		L"文件名称",
		L"文件大小",
		L"创建时间",
		L"修改时间"
	};
	CString m_szCurPath;
	CImageList m_imgList;
	void LoadFile();
	void Refresh();
	void InitList();
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	CTreeCtrl m_tree;
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButton1();
    CString m_path;
};
