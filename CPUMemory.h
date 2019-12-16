#pragma once


// CPUMemory 对话框

class CPUMemory : public CDialogEx
{
	DECLARE_DYNAMIC(CPUMemory)
private:
	void InitMemory();
	void InitCPU();
public:
	CPUMemory(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPUMemory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPUMEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_TotalPhys;
	CString m_availPhys;
	CString m_totalPageFIle;
	CString m_availPageFile;
	CString m_totalVirtual;
	CString m_availVirtual;
	CString m_idleTime;
	CString m_kernelTime;
	CString m_userTime;
	CString m_radio;
};
