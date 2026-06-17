#ifndef __DSP_GS32_DEVICE_H__
#define __DSP_GS32_DEVICE_H__

#include "device.h"

#define  StartCpuTimer1() 	CPUTimer_startTimer(CPUTIMER1_BASE)
#define  GetTime()          CPUTimer_getTimerCount(CPUTIMER1_BASE)

#endif /* __DSP_GS32_DEVICE_H__ */
