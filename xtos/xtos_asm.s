;********************************************************************************************************
;                                          XiaoTu-OS(XTOS)
;
;											   高乙超
;										gaoyichao_2016@126.com
;											gaoyichao.com
;
;	本系统在实现过程中参考了μC/OS，基本没怎么改
;
;********************************************************************************************************

	EXTERN gp_xtos_cur_task
	EXTERN gp_xtos_next_task

	EXPORT xtos_start
	EXPORT xtos_context_switch
	EXPORT xtos_pendsv_handler
;********************************************************************************************************

SCB_ICSR	    EQU     0xE000ED04                              ; 中断控制和状态寄存器SCB->ICSR.
SCB_SHP14		EQU     0xE000ED22                              ; 中断优先级寄存器SCB->SHP[14](priority 14).
PENDSV_PRI		EQU           0xFF                              ; PendSV中断优先级(最低).
PENDSV_SET		EQU     0x10000000                              ; Value to trigger PendSV exception.

;********************************************************************************************************

    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

;********************************************************************************************************
;                                         启动操作系统
;                                     void xtos_start(void)
;
; 1. 配置PendSV的中断优先级
;
; 2. 标记第一次执行上下文切换
;
; 3. 触发PendSV, 在第一次进行上下文切换之前, Thread模式和Handler模式都使用的时MSP作为栈空间指针
;    切换之后, Thread模式使用PSP作为栈空间指针, 而Handler模式仍然使用MSP作为栈空间指针
;
;********************************************************************************************************

xtos_start
    LDR     R0, =SCB_SHP14										; 设置PendSV的优先级
    LDR     R1, =PENDSV_PRI
    STRB    R1, [R0]

    MOVS    R0, #0                                              ; PSP = 0, 标识第一次进行上下文切换
    MSR     PSP, R0

    LDR     R0, =SCB_ICSR										; 触发PendSV,进行上下文切换
    LDR     R1, =PENDSV_SET
    STR     R1, [R0]

    CPSIE   I                                                   ; 开中断

xtos_start_hang
    B       xtos_start_hang                                     ; Should never get here

;********************************************************************************************************
;                                        任务级上下文切换
;                                     void xtos_context_switch(void)
;
; 1. 触发PendSV中断, 仅此而已
;
;********************************************************************************************************

xtos_context_switch
    LDR     R0, =SCB_ICSR										; 触发PendSV,进行上下文切换
    LDR     R1, =PENDSV_SET
    STR     R1, [R0]
    BX      LR

;********************************************************************************************************
;                                         PendSV的中断服务函数
;                                     void XTOS_PendSV_Handler(void)
;
; 1. 用作上下文切换，分为保存上文和恢复下文两个部分
;
; 2. 因为进入中断时系统已经帮我们把Caller Saved Registers保存了，所以这里只需在保存Callee
;	 Saved Registers即可
;
; 3. 实际上对于F407而言，如果开启了FPU，Caller Saved Registers除了R0-R3, R12, LR, PC, xPSR之外
;    还包括S0-S15共16个FPU寄存器
;
; 4. 这里如果开启了FPU，那么Callee Saved Registers除了R4-R11之外，还包括FPU的S16-S31
;
;********************************************************************************************************

xtos_pendsv_handler
context_switch_save_senario
	CPSID	I											; 关中断
    MRS     R0, PSP                                     ; 获取当前PSP
    CBZ     R0, context_switch_load_senario             ; 如果PSP为0，说明是首次调用，没有上文，直接恢复下文

	TST 	R14, #0x10									; 根据EXC_RETURN的bit4, 判定是否开启了FPU
	IT 		EQ											; 若开启了, 则保存S16-S31
	VSTMDBEQ R0!, {S16-S31} 
	
    SUBS    R0, R0, #0x20                               ; 32位, 4字节对齐,8个寄存器, 0x08 * 4 = 0x20
    STM     R0, {R4-R11}								; 保存R4-R11到当前进程的栈空间中

    LDR     R1, =gp_xtos_cur_task                       ; gp_xtos_cur_task->pTopOfStack = SP;
    LDR     R1, [R1]
    STR     R0, [R1]                                    ; R0中记录了上文栈顶

context_switch_load_senario
	LDR		R0, =gp_xtos_cur_task						; gp_xtos_cur_task = gp_xtos_next_task
	LDR		R1, =gp_xtos_next_task
	LDR		R2, [R1]
	STR		R2, [R0]

	LDR		R0, [R2]									; R0 = gp_xtos_next_task->pTopOfStack
	LDM		R0, {R4-R11}								; 装载下文的Callee Saved Registers
	ADDS	R0, R0, #0x20

	TST 	R14, #0x10									; 根据EXC_RETURN的bit4, 判定是否开启了FPU
	IT 		EQ											; 若开启了, 则装载S16-S31
	VLDMIAEQ R0!, {S16-S31} 

	MSR		PSP, R0										; 更新PSP = gp_xtos_next_task->pTopOfStack
	ORR		LR, LR, #0x04								; 确保返回时使用PSP作为栈指针

	CPSIE	I											; 开中断
	BX		LR											; 中断返回恢复中断现场时，从栈空间中取出Caller Saved Registers

	END
