/*
 * DSP2803x_CpuTimers.c ¡ú GS32F035P Port (Phase 1)
 *
 * TI CPU Timer API ¡ú GS32 V30 CPUTimer driverlib wrapper.
 * Preserves TI-compatible function signatures for downstream code.
 */

#include "device.h"
#include "driverlib.h"
#include "board_cfg.h"

/* ---- TI-compatible CPU Timer variables ---- */
typedef struct {
    uint32_t base;
    uint32_t interruptCount;
    float    cpuFreqInMHz;
    float    periodInUSec;
} CPUTIMER_VARS;

CPUTIMER_VARS CpuTimer0;
CPUTIMER_VARS CpuTimer1;

/* ---- InitCpuTimers ---- */
void InitCpuTimers(void)
{
    CpuTimer0.base = CPUTIMER0_BASE;
    CpuTimer0.interruptCount = 0;
    CpuTimer0.cpuFreqInMHz = (float)(DEVICE_SYSCLK_FREQ / 1000000U);
    CpuTimer0.periodInUSec = 0.0f;

    CpuTimer1.base = CPUTIMER1_BASE;
    CpuTimer1.interruptCount = 0;
    CpuTimer1.cpuFreqInMHz = (float)(DEVICE_SYSCLK_FREQ / 1000000U);
    CpuTimer1.periodInUSec = 0.0f;
}

/* ---- ConfigCpuTimer ----
 * TI: period = Freq_MHz * Period_uSec (timer clock = SYSCLK)
 * GS32: timer clock = SYSCLK / 4, so period = (SYSCLK/4e6) * Period_uSec
 */
void ConfigCpuTimer(CPUTIMER_VARS *Timer, float Freq_MHz, float Period_uSec)
{
    uint32_t period;

    Timer->cpuFreqInMHz = Freq_MHz;
    Timer->periodInUSec = Period_uSec;
    period = (uint32_t)((float)(DEVICE_SYSCLK_FREQ / 4000000U) * Period_uSec);
    CPUTimer_init(Timer->base, period);
}

void StartCpuTimer0(void) { CPUTimer_startTimer(CPUTIMER0_BASE); }
void StartCpuTimer1(void) { CPUTimer_startTimer(CPUTIMER1_BASE); }
void StopCpuTimer0(void)  { CPUTimer_stopTimer(CPUTIMER0_BASE); }
void StopCpuTimer1(void)  { CPUTimer_stopTimer(CPUTIMER1_BASE); }
void ReloadCpuTimer0(void) { CPUTimer_startTimer(CPUTIMER0_BASE); }
void ReloadCpuTimer1(void) { CPUTimer_startTimer(CPUTIMER1_BASE); }
