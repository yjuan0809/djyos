//----------------------------------------------------
// Copyright (c) 2014, SHENZHEN PENGRUI SOFT CO LTD. All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
// Copyright (c) 2014 著作权由深圳鹏瑞软件有限公司所有。著作权人保留一切权利。
//
// 这份授权条款，在使用者符合下列条件的情形下，授予使用者使用及再散播本
// 软件包装原始码及二进位可执行形式的权利，无论此包装是否经改作皆然：
//
// 1. 对于本软件源代码的再散播，必须保留上述的版权宣告、本条件列表，以
//    及下述的免责声明。
// 2. 对于本套件二进位可执行形式的再散播，必须连带以文件以及／或者其他附
//    于散播包装中的媒介方式，重制上述之版权宣告、本条件列表，以及下述
//    的免责声明。

// 免责声明：本软件是本软件版权持有人以及贡献者以现状（"as is"）提供，
// 本软件包装不负任何明示或默示之担保责任，包括但不限于就适售性以及特定目
// 的的适用性为默示性担保。版权持有人及本软件之贡献者，无论任何条件、
// 无论成因或任何责任主义、无论此责任为因合约关系、无过失责任主义或因非违
// 约之侵权（包括过失或其他原因等）而起，对于任何因使用本软件包装所产生的
// 任何直接性、间接性、偶发性、特殊性、惩罚性或任何结果的损害（包括但不限
// 于替代商品或劳务之购用、使用损失、资料损失、利益损失、业务中断等等），
// 不负任何责任，即在该种使用已获事前告知可能会造成此类损害的情形下亦然。
//-----------------------------------------------------------------------------
//所属模块: 调度器
//作者：lst
//版本：V1.0.1
//文件描述: 调度器中与CPU直接相关的代码。
//其他说明:
//修订历史:
//2. 日期: 2009-04-24
//   作者: lst
//   新版本号: V1.0.1
//   修改说明: 删除了一些为dlsp版本准备的东西
//1. 日期: 2009-01-04
//   作者: lst
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#include "align.h"
#include "stdint.h"
#include "stdlib.h"
#include "int.h"
#include "hard-exp.h"
#include "string.h"
#include "arch_feature.h"
#include "djyos.h"
#include "cpu.h"
#include "cpu_peri.h"

void __asm_reset_thread(void (*thread_routine)(void),struct ThreadVm *vm);

extern s64  g_s64OsTicks;             //操作系统运行ticks数
u32 g_u32CycleSpeed; //for(i=j;i>0;i--);每循环纳秒数*1.024

//tick选择t64-0的t12

//----创建线程-----------------------------------------------------------------
//功能：为事件类型创建伪虚拟机，初始化上下文环境，安装执行函数，构成完整线程
//参数：evtt_id，待创建的线程所服务的事件类型id
//返回：新创建的线程的虚拟机指针
//注: 移植敏感函数
//-----------------------------------------------------------------------------
struct ThreadVm *__CreateThread(struct EventType *evtt,u32 *stack_size)
{
    struct ThreadVm  *result;
    ptu32_t  len;

    //计算虚拟机栈:线程+最大单个api需求的栈
    len = evtt->stack_size;
    //栈顶需要对齐，malloc函数能保证栈底是对齐的，对齐长度可以使栈顶对齐
    len = align_up_sys(len);
    result=(struct ThreadVm  *)__MallocStack(len);
    *stack_size = len;
    if(result==NULL)
    {
        Djy_SaveLastError(EN_MEM_TRIED);   //内存不足，返回错误
        return result;
    }
    len = M_CheckSize(result);
    memset(result,'d',len);
    result->stack_top = (u32*)((ptu32_t)result+len); //栈顶地址，移植敏感
    result->next = NULL;
    result->stack_size = len - sizeof(struct ThreadVm); //保存栈深度
    result->host_vm = NULL;
    //复位虚拟机并重置线程
    __asm_reset_thread(evtt->thread_routine,result);
    return result;
}

//----静态创建线程-------------------------------------------------------------
//功能：为事件类型创建线程，初始化上下文环境，安装执行函数，构成完整线程
//参数：evtt_id，待创建的线程所服务的事件类型id
//返回：新创建的线程指针
//注: 移植敏感函数
//-----------------------------------------------------------------------------
struct ThreadVm *__CreateStaticThread(struct EventType *evtt,void *Stack,
                                    u32 StackSize)
{
    struct ThreadVm  *result;

    result = (struct ThreadVm  *)align_up_sys(Stack);

    memset(Stack, 'd', StackSize-((ptu32_t)result - (ptu32_t)Stack));

    //看实际分配了多少内存，djyos内存分配使用块相联策略，如果分配的内存量大于
    //申请量，可以保证其实际尺寸是对齐的。之所以注释掉，是因为当len大于申请量时，
    //对齐只是实际结果，而不是内存管理的规定动作，如果不注释掉，就要求内存管理
    //模块必须提供对齐的结果，对模块独立性是不利的。
//    len = M_CheckSize(result);
    result->stack_top = align_down_sys((ptu32_t)Stack+StackSize); //栈顶地址，移植敏感
    result->next = NULL;
    result->stack_size = (ptu32_t)(result->stack_top) - (ptu32_t)result
                            - sizeof(struct ThreadVm);       //保存栈深度
    result->host_vm = NULL;
    //复位线程并重置线程
    __asm_reset_thread(evtt->thread_routine,result);
    return result;
}

//----测量指令指令延时常数-----------------------------------------------------
//功能: 设置指令延时常数,使不管用何种编译器和编译优化选项,djy_delay_us函数准确延时，
//参数：无
//返回: 无
//备注: 本函数移植敏感
//-----------------------------------------------------------------------------
void __DjySetDelay(void)
{
    uint32_t counter,u32_fors=10000,clksum,timer_clk_hz;
    volatile uint32_t u32loops;

    clksum = 0xFFFF;  //此处建议取计数器最大值，S3Cxxxx Timer是16位计数器
    timer_clk_hz =5000000; //硬件定时器时钟为5MHZ.

    Int_CutLine(CN_INT_LINE_TIMER3); //禁止TIMER3中断
    Timer_SetCounter(3,clksum);
    Timer_SetClkSource(3,0);  //pclk预分频数的1/2分频
    Timer_SetPrecale(1,(CN_CFG_PCLK/2/timer_clk_hz));  //设置定时器pre_div
    Timer_SetType(3,0);  //单次定时工作
    Timer_Reload(3);
    Timer_Start(3);

    for(u32loops=u32_fors;u32loops>0;u32loops--);       //循环u32_fors次
    Timer_Stop(3);

    //此处调试阶段需确定，当递减计数器到达0时，说明一个计数周期内无法完成上述循环
    //需减小u32_fors值，或采用systick中断服务函数计算有多少个计数周期
    counter =Timer_Read(3);
    if(counter==0)
    {
        while(1);
    }

    counter = clksum - counter;    //取实际脉冲数。
    g_u32CycleSpeed = ((uint64_t)counter * (u64)10E8)/timer_clk_hz/u32_fors;//防溢出，用64位
    g_u32CycleSpeed = (g_u32CycleSpeed << 10) / 1000;     //扩大1.024倍
}


u32 __DjyIsrTick(ptu32_t line)
{
    Djy_IsrTick(1);
    return 0;
}

//----初始化tick---------------------------------------------------------------
//功能: 初始化定时器,并连接tick中断函数,启动定时器.
//参数: 无
//返回: 无
//备注: 本函数是移植敏感函数.
//-----------------------------------------------------------------------------
void __DjyInitTick(void)
{
    Int_Register(CN_INT_LINE_TIMER3);
    Int_CutLine(CN_INT_LINE_TIMER3);
    //连接timer3作为tick中断
    Int_IsrConnect(CN_INT_LINE_TIMER3,__DjyIsrTick);
    Int_SettoAsynSignal(CN_INT_LINE_TIMER3);          //tick中断被设为异步信号
    //以下设置定时器参数，需与board-config.h中CN_CFG_TICK_US、CN_CFG_TICK_HZ和
    //CN_CFG_FINE_US、CN_CFG_FINE_HZ的定义一致
    Timer_SetClkSource(3,0);          //pclk预分频数的1/2分频
    Timer_SetPrecale(1,CN_CFG_TIMER_CLK/CN_CFG_FINE_HZ/2 -1);
    //以上把定时器输入时钟的频率设为CN_CFG_FINE_HZ
    //Timer_SetCounter(3,(uint16_t)((u32)CN_CFG_TICK_US*1000/CN_CFG_FINE_US));
    Timer_SetCounter(3, CN_CFG_FINE_HZ/CN_CFG_TICK_HZ);
    Timer_SetType(3,1);                //设置tick定时器连续工作
    Timer_Reload(3);                    //重载定时值
    Timer_Start(3);                     //启动定时器
    Int_RestoreAsynLine(CN_INT_LINE_TIMER3);//启动tick中断S
}

//----读取当前时间(uS)---------------------------------------------------------
//功能：读取当前时间(uS),从计算机启动以来经历的us数，64位，默认不会溢出
//      g_s64OsTicks 为64位变量，非64位系统中，读取 g_s64OsTicks 需要超过1个
//      周期,需要使用原子操作。
//参数：无
//返回：当前时钟
//说明: 这是一个桩函数,被rtc.c文件的 DjyGetSysTime 函数调用
//-----------------------------------------------------------------------------
s64 __DjyGetSysTime(void)
{
    s64 time;
    static s64 BakTime = 0;
    u32 temp;
    atom_low_t atom_low;
    temp =CN_CFG_FINE_HZ/CN_CFG_TICK_HZ - pg_timer_reg->TCNTO3;

    atom_low = Int_LowAtomStart();
    time = g_s64OsTicks;
    Int_LowAtomEnd(atom_low);
    time = time*CN_CFG_TICK_US + (temp*CN_CFG_FINE_US >>16);
    if(time < BakTime)
        time += CN_CFG_TICK_US;
    BakTime = time;

    return time;
}

void reset(void)
{
    //wait for adding
}
extern void reboot(void)
{

}
extern void restart_system(void)
{

}

