#pragma once
//#include <Windows.h>
#include "pch.h"
#include <pdh.h>

//ÿ�����̵�״̬
typedef struct tagDISKSTATUS {
	DWORD	_FreeAvalidToCaller;	//�������ɵ����߿��õ��ֽ����� BYTE
	DWORD	_TotalNummber;			//�������ɴ����ϵ����ֽ���	BYTE
	DWORD	_TotalNummberOfFree;	//�������ɴ����Ͽ��õ��ֽ���	BYTE
}DISKSTATUS, * LPDISKSTATUS;
//���д��̵�״̬
typedef struct tagAllDISKSTATUS {
	UINT	_DiskCount;				//��������
	DWORD	_Total;					//���д���������MB
	DWORD	_OfFree;				//���д���ʣ������MB
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
	double GetSystemCpuCUrrentUsage();  // ���CPU��ʹ����
	BOOL GetPhysicalMemoryState(ULONGLONG& totalPhyMem, ULONGLONG& phyMemUsed);
	double GetTotalPhysicalMemory();
	double GetTotalPhysicalMemoryUsed();
	double GetPhysicalMemoryUsage();
	float TransPercentToFloatValue(const double dValue);
private:
	PDH_HQUERY m_CpuQuery;
	PDH_HCOUNTER m_CpuTotal;
};

