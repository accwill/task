#pragma once
//#include <Windows.h>
#include "pch.h"
#include <pdh.h>

//每个磁盘的状态
typedef struct tagDISKSTATUS {
	DWORD	_FreeAvalidToCaller;	//用于容纳调用者可用的字节数量 BYTE
	DWORD	_TotalNummber;			//用于容纳磁盘上的总字节数	BYTE
	DWORD	_TotalNummberOfFree;	//用于容纳磁盘上可用的字节数	BYTE
}DISKSTATUS, * LPDISKSTATUS;
//所有磁盘的状态
typedef struct tagAllDISKSTATUS {
	UINT	_DiskCount;				//磁盘数量
	DWORD	_Total;					//所有磁盘总容量MB
	DWORD	_OfFree;				//所有磁盘剩余容量MB
}AllDISKSTATUS, * LPAllDISKSTATUS;


class CPUMemDiskStatus {
public:
	CPUMemDiskStatus();
	~CPUMemDiskStatus();
public:
	void GetSystemDiskStatus(ULONGLONG& AllDiskTotal, ULONGLONG& AllDiskFree);
	void GetSystemCurrentDiskStatus(ULONGLONG& TatolMB, ULONGLONG& FreeCaller);
	double GetSystemCurrentDiskUsage();
	void SystemCpuInit();
	void SystemCpuUnInit();
	double GetSystemCpuCUrrentUsage();  // 检测CPU的使用率
	BOOL GetPhysicalMemoryState(ULONGLONG& totalPhyMem, ULONGLONG& phyMemUsed);
	double GetTotalPhysicalMemory();
	double GetTotalPhysicalMemoryUsed();
	double GetPhysicalMemoryUsage();
	float TransPercentToFloatValue(const double dValue);
private:
	PDH_HQUERY m_CpuQuery;
	PDH_HCOUNTER m_CpuTotal;
};

