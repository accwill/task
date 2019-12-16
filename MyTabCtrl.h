#pragma once

#include <vector>
// MyTabCtrl

class MyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(MyTabCtrl)

public:
	MyTabCtrl();
	virtual ~MyTabCtrl();
	void AddTab(const CString& title, CDialogEx* pDialog);
private:
	std::vector<CWnd*> m_subWnds;
	int m_nPrevTabIndex = 0;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
};


