// CPUMemory.cpp: 实现文件
//

#include "pch.h"
#include "12.11.tab.h"
#include "CPUMemory.h"
#include "afxdialogex.h"


// CPUMemory 对话框

IMPLEMENT_DYNAMIC(CPUMemory, CDialogEx)

void CPUMemory::InitMemory() {
    CString szTemp;
    MEMORYSTATUSEX memstatus;
    memstatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memstatus);
    szTemp.Format(L"%lld GB", memstatus.ullTotalPhys / 1024 / 1024 / 1024);
    m_TotalPhys = szTemp;
    szTemp.Format(L"%lld GB", memstatus.ullAvailPhys / 1024 / 1024 / 1024);
    szTemp.Format(L"%d", memstatus.dwMemoryLoad);
    m_availPhys = szTemp;
    szTemp.Format(L"%lld GB", memstatus.ullTotalPageFile / 1024 / 1024 / 1024);
    m_totalPageFIle = szTemp;
    szTemp.Format(L"%lld GB", memstatus.ullAvailPageFile / 1024 / 1024 / 1024);
    m_availPageFile = szTemp;
    szTemp.Format(L"%lld GB", memstatus.ullTotalVirtual / 1024 / 1024 / 1024);
    m_totalVirtual = szTemp;
    szTemp.Format(L"%lld GB", memstatus.ullAvailVirtual / 1024 / 1024 / 1024);
    m_availVirtual = szTemp;
    UpdateData(false);
}

void CPUMemory::InitCPU() {
    auto FILETIME2DOUBLE = [](const _FILETIME& fileTime) -> double {
        return double(fileTime.dwHighDateTime * 4.294967296e9) + double(fileTime.dwLowDateTime);
    };
    auto ToTime = [](FILETIME* lpFileTime) -> CString {
        CString szTemp;
        SYSTEMTIME systime;
        FileTimeToSystemTime(lpFileTime, &systime);
        szTemp.Format(L"%d:%d:%d",
            //systime.wYear, systime.wMonth, systime.wDay,
            systime.wHour, systime.wMinute, systime.wSecond
        );
        return szTemp;
    };
    CString szTemp;
    //       空闲时间    内核时间    用户事件
    _FILETIME idleTime, kernelTime, userTime;
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    HANDLE hEvent = CreateEvent(NULL, false, false, NULL);
    WaitForSingleObject(hEvent, 1000);
    _FILETIME newIdleTime, newKernelTime, newUserTime;
    GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);

    double dIdleTime = FILETIME2DOUBLE(idleTime);
    double dNewIdleTime = FILETIME2DOUBLE(newIdleTime);
    double dKernelTime = FILETIME2DOUBLE(kernelTime);
    double dNewKernelTime = FILETIME2DOUBLE(newKernelTime);
    double dUserTime = FILETIME2DOUBLE(userTime);
    double dNewUserTime = FILETIME2DOUBLE(newUserTime);

    int radio = int(100.0 - (dNewIdleTime - dIdleTime) / (dNewKernelTime - dKernelTime + dNewUserTime - dUserTime) * 100.0);
    
    //szTemp.Format(L"%lf", dIdleTime);
    //m_idleTime = szTemp;
    //szTemp.Format(L"%lf", dKernelTime);
    //m_kernelTime = szTemp;
    //szTemp.Format(L"%lf", dUserTime);
    //m_userTime = szTemp;
    //szTemp.Format(L"%d", radio);
    //m_radio = szTemp;
    m_idleTime = ToTime(&idleTime);
    m_kernelTime = ToTime(&kernelTime);
    m_userTime = ToTime(&userTime);
    szTemp.Format(L"%d", radio);
    m_radio = szTemp;
    UpdateData(false);
}

CPUMemory::CPUMemory(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CPUMEM, pParent)
    , m_TotalPhys(_T("")), m_availPhys(_T("")), m_totalPageFIle(_T("")), m_availPageFile(_T("")), m_totalVirtual(_T("")), m_availVirtual(_T("")), m_idleTime(_T("")), m_kernelTime(_T("")), m_userTime(_T("")), m_radio(_T("")) {

}

CPUMemory::~CPUMemory()
{
}

void CPUMemory::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TOTALSIZE, m_TotalPhys);
    DDX_Text(pDX, IDC_MEMLOAD, m_availPhys);
    DDX_Text(pDX, IDC_TOTALPAGEFILE, m_totalPageFIle);
    DDX_Text(pDX, IDC_AVAILPAGEFILE, m_availPageFile);
    DDX_Text(pDX, IDC_TOTALVIRTUAL, m_totalVirtual);
    DDX_Text(pDX, IDC_AVAILVIRTUAL, m_availVirtual);
    DDX_Text(pDX, IDC_IDLETIME, m_idleTime);
    DDX_Text(pDX, IDC_KERNELTIME, m_kernelTime);
    DDX_Text(pDX, IDC_USERTIME, m_userTime);
    DDX_Text(pDX, IDC_RADIO, m_radio);
}


BEGIN_MESSAGE_MAP(CPUMemory, CDialogEx)
END_MESSAGE_MAP()


// CPUMemory 消息处理程序


BOOL CPUMemory::OnInitDialog() {
    CDialogEx::OnInitDialog();
    // TODO:  在此添加额外的初始化
    InitMemory();
    InitCPU();
    return TRUE;
}
