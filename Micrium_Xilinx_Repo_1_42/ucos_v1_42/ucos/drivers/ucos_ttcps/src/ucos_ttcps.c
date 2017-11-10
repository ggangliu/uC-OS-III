
#include <xparameters.h>
#include <ucos_ttcps.h>


extern UCOS_TTCPS_Config UCOS_TTCPS_ConfigTable[];

static UCOS_TTCPS UCOS_TTCPS_Table[XPAR_UCOS_TTCPS_NUM_INSTANCES];


typedef struct ttcps {
    CPU_REG32  ClkCtrl;
    CPU_REG32  RESERVED0[2];
    CPU_REG32  CtrCtrl;
    CPU_REG32  RESERVED1[2];
    CPU_REG32  CtrVal;
    CPU_REG32  RESERVED2[2];
    CPU_REG32  IntervalCtrVal;
    CPU_REG32  RESERVED3[2];
    CPU_REG32  Match1CtrVal;
    CPU_REG32  RESERVED4[2];
    CPU_REG32  Match2CtrVal;
    CPU_REG32  RESERVED5[2];
    CPU_REG32  Match3CtrVal;
    CPU_REG32  RESERVED6[2];
    CPU_REG32  IntStat;
    CPU_REG32  RESERVED7[2];
    CPU_REG32  IntEn;
    CPU_REG32  RESERVED8[2];
    CPU_REG32  EventCtrl;
    CPU_REG32  RESERVED9[2];
    CPU_REG32  EventReg;
    CPU_REG32  RESERVED10[2];
} TTCPS, *TTCPS_PTR;

#define TTCPS_BIT_CTRCTRL_DIS   DEF_BIT_00
#define TTCPS_BIT_CTRCTRL_INT   DEF_BIT_01
#define TTCPS_BIT_CTRCTRL_DEC   DEF_BIT_02
#define TTCPS_BIT_CTRCTRL_MATCH DEF_BIT_03
#define TTCPS_BIT_CTRCTRL_RST   DEF_BIT_04
#define TTCPS_BIT_CTRCTRL_WAVE  DEF_BIT_05
#define TTCPS_BIT_CTRCTRL_POL   DEF_BIT_06

UCOS_TTCPS_HANDLE UCOS_TTCPSInit (CPU_INT32U DeviceId)
{
    UCOS_TTCPS_HANDLE Handle;
    TTCPS_PTR Tmr;
    CPU_SR_ALLOC();
    
    
    if (DeviceId > XPAR_UCOS_TTCPS_NUM_INSTANCES) {
        return DEF_NULL;
    }
    
    Handle = &UCOS_TTCPS_Table[DeviceId];
    
    Handle->DeviceId = UCOS_TTCPS_ConfigTable[DeviceId].DeviceId;
    Tmr = (TTCPS_PTR)UCOS_TTCPS_ConfigTable[DeviceId].BaseAddress;
    Handle->Timer = Tmr;
    
    CPU_CRITICAL_ENTER(); /* Reset the timer. */
    Tmr->CtrCtrl = 0x21;
    Tmr->ClkCtrl = 0;
    Tmr->IntervalCtrVal = 0;
    Tmr->Match1CtrVal = 0;
    Tmr->Match2CtrVal = 0;
    Tmr->Match1CtrVal = 0;
    Tmr->IntEn = 0;
    Tmr->EventCtrl = 0;
    Tmr->IntStat;
    CPU_CRITICAL_EXIT();
    
    return (Handle);
}


CPU_BOOLEAN UCOS_TTCPSStart (UCOS_TTCPS_HANDLE Handle)
{
    TTCPS_PTR Tmr;
    CPU_SR_ALLOC();
    
    
    Tmr = Handle->Timer;
    
    CPU_CRITICAL_ENTER();
    Tmr->CtrCtrl &= ~TTCPS_BIT_CTRCTRL_DIS;
    CPU_CRITICAL_EXIT();
    
    return (DEF_OK);
}


CPU_BOOLEAN UCOS_TTCPSStop (UCOS_TTCPS_HANDLE Handle)
{
    TTCPS_PTR Tmr;
    CPU_SR_ALLOC();
    
    
    Tmr = Handle->Timer;
    
    CPU_CRITICAL_ENTER();
    Tmr->CtrCtrl |= TTCPS_BIT_CTRCTRL_DIS;
    CPU_CRITICAL_EXIT();
    
    return (DEF_OK);
}


CPU_BOOLEAN UCOS_TTCPSIntSet (UCOS_TTCPS_HANDLE Handle, CPU_INT32U Int)
{
    TTCPS_PTR Tmr;
    CPU_SR_ALLOC();
    
    
    Tmr = Handle->Timer;
    
    CPU_CRITICAL_ENTER();
    Tmr->IntEn |= Int & UCOS_TTCPS_IXR_MASK;
    CPU_CRITICAL_EXIT();
    
    return (DEF_OK);
}


CPU_BOOLEAN UCOS_TTCPSIntClr (UCOS_TTCPS_HANDLE Handle, CPU_INT32U Int)
{
    TTCPS_PTR Tmr;
    CPU_SR_ALLOC();
    
    
    Tmr = Handle->Timer;
    
    CPU_CRITICAL_ENTER();
    Tmr->IntEn &= ~(Int & UCOS_TTCPS_IXR_MASK);
    CPU_CRITICAL_EXIT();
    
    return (DEF_OK);
}


CPU_INT32U UCOS_TTCPSIntStatGet (UCOS_TTCPS_HANDLE Handle)
{
    TTCPS_PTR Tmr;

    Tmr = Handle->Timer;

    return (Tmr->IntStat);
}
