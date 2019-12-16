#include "pch.h"
#include "CPUMemDiskStatus.h"

CPUMemDiskStatus::CPUMemDiskStatus() : m_CpuQuery(NULL), m_CpuTotal(NULL) {
}

CPUMemDiskStatus::~CPUMemDiskStatus() {
    if (m_CpuTotal) {
        //PdhRemoveCounter(m_CpuTotal);
        m_CpuTotal = NULL;
    }
    if (m_CpuQuery) {
        //PdhCloseQuery(m_CpuQuery);
        m_CpuQuery = NULL;
    }
    SystemCpuUnInit();
}

void CPUMemDiskStatus::GetSystemDiskStatus(DWORD64& dw64AllDiskTotal, DWORD64& dw64AllDiskFree) {
    int nType = 0;
    int nSi = 0;
    BOOL bResult = FALSE;
    int nDiskCount = 0;
    DWORD64 dw64TempTotal = 0;
    DWORD64 dw64TempFre = 0;

    DWORD64 dw64FreeBytesToCaller;
    DWORD64 dw64TotalBytes;
    DWORD64 dw64FreeBytes;

    DWORD dwDiskInfo = GetLogicalDrives(); // 返回一个可用驱动器的掩码， 通过掩码左移来去驱动器的个数

    // 磁盘个数？？
    while (dwDiskInfo) {
        if (dwDiskInfo & 1) {
            ++nDiskCount;
        }
        dwDiskInfo = dwDiskInfo >> 1;
    }

    int nTest = nDiskCount;
    int nDsLength = GetLogicalDriveStrings(0, NULL);









}

void CPUMemDiskStatus::GetSystemCurrentDiskStatus(DWORD64& dw64TatolMB, DWORD64& dw64FreeCaller) {
}

double CPUMemDiskStatus::GetSystemCurrentDiskUsage() {
    return 0.0;
}

void CPUMemDiskStatus::SystemCpuInit() {
}

void CPUMemDiskStatus::SystemCpuUnInit() {
}

double CPUMemDiskStatus::GetSystemCpuCUrrentUsage() {
    return 0.0;
}

BOOL CPUMemDiskStatus::GetPhysicalMemoryState(DWORD64& dw64TotalPhyMem, DWORD64& dw64PhyMemUsed) {
    return 0;
}

double CPUMemDiskStatus::GetTotalPhysicalMemory() {
    return 0.0;
}

double CPUMemDiskStatus::GetTotalPhysicalMemoryUsed() {
    return 0.0;
}

double CPUMemDiskStatus::GetPhysicalMemoryUsage() {
    return 0.0;
}

float CPUMemDiskStatus::TransPercentToFloatValue(const double dValue) {
    return 0.0f;
}
