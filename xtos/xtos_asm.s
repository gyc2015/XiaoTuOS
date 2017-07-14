;********************************************************************************************************
;                                          XiaoTu-OS(XTOS)
;
;											   ���ҳ�
;										gaoyichao_2016@126.com
;											gaoyichao.com
;
;	��ϵͳ��ʵ�ֹ����вο��˦�C/OS������û��ô��
;
;********************************************************************************************************

	EXTERN gp_xtos_cur_task
	EXTERN gp_xtos_next_task

	EXPORT xtos_start
	EXPORT xtos_context_switch
	EXPORT xtos_pendsv_handler
;********************************************************************************************************

SCB_ICSR	    EQU     0xE000ED04                              ; �жϿ��ƺ�״̬�Ĵ���SCB->ICSR.
SCB_SHP14		EQU     0xE000ED22                              ; �ж����ȼ��Ĵ���SCB->SHP[14](priority 14).
PENDSV_PRI		EQU           0xFF                              ; PendSV�ж����ȼ�(���).
PENDSV_SET		EQU     0x10000000                              ; Value to trigger PendSV exception.

;********************************************************************************************************

    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

;********************************************************************************************************
;                                         ��������ϵͳ
;                                     void xtos_start(void)
;
; 1. ����PendSV���ж����ȼ�
;
; 2. ��ǵ�һ��ִ���������л�
;
; 3. ����PendSV, �ڵ�һ�ν����������л�֮ǰ, Threadģʽ��Handlerģʽ��ʹ�õ�ʱMSP��Ϊջ�ռ�ָ��
;    �л�֮��, Threadģʽʹ��PSP��Ϊջ�ռ�ָ��, ��Handlerģʽ��Ȼʹ��MSP��Ϊջ�ռ�ָ��
;
;********************************************************************************************************

xtos_start
    LDR     R0, =SCB_SHP14										; ����PendSV�����ȼ�
    LDR     R1, =PENDSV_PRI
    STRB    R1, [R0]

    MOVS    R0, #0                                              ; PSP = 0, ��ʶ��һ�ν����������л�
    MSR     PSP, R0

    LDR     R0, =SCB_ICSR										; ����PendSV,�����������л�
    LDR     R1, =PENDSV_SET
    STR     R1, [R0]

    CPSIE   I                                                   ; ���ж�

xtos_start_hang
    B       xtos_start_hang                                     ; Should never get here

;********************************************************************************************************
;                                        �����������л�
;                                     void xtos_context_switch(void)
;
; 1. ����PendSV�ж�, ���˶���
;
;********************************************************************************************************

xtos_context_switch
    LDR     R0, =SCB_ICSR										; ����PendSV,�����������л�
    LDR     R1, =PENDSV_SET
    STR     R1, [R0]
    BX      LR

;********************************************************************************************************
;                                         PendSV���жϷ�����
;                                     void XTOS_PendSV_Handler(void)
;
; 1. �����������л�����Ϊ�������ĺͻָ�������������
;
; 2. ��Ϊ�����ж�ʱϵͳ�Ѿ������ǰ�Caller Saved Registers�����ˣ���������ֻ���ڱ���Callee
;	 Saved Registers����
;
; 3. ʵ���϶���F407���ԣ����������FPU��Caller Saved Registers����R0-R3, R12, LR, PC, xPSR֮��
;    ������S0-S15��16��FPU�Ĵ���
;
; 4. �������������FPU����ôCallee Saved Registers����R4-R11֮�⣬������FPU��S16-S31
;
;********************************************************************************************************

xtos_pendsv_handler
context_switch_save_senario
	CPSID	I											; ���ж�
    MRS     R0, PSP                                     ; ��ȡ��ǰPSP
    CBZ     R0, context_switch_load_senario             ; ���PSPΪ0��˵�����״ε��ã�û�����ģ�ֱ�ӻָ�����

	TST 	R14, #0x10									; ����EXC_RETURN��bit4, �ж��Ƿ�����FPU
	IT 		EQ											; ��������, �򱣴�S16-S31
	VSTMDBEQ R0!, {S16-S31} 
	
    SUBS    R0, R0, #0x20                               ; 32λ, 4�ֽڶ���,8���Ĵ���, 0x08 * 4 = 0x20
    STM     R0, {R4-R11}								; ����R4-R11����ǰ���̵�ջ�ռ���

    LDR     R1, =gp_xtos_cur_task                       ; gp_xtos_cur_task->pTopOfStack = SP;
    LDR     R1, [R1]
    STR     R0, [R1]                                    ; R0�м�¼������ջ��

context_switch_load_senario
	LDR		R0, =gp_xtos_cur_task						; gp_xtos_cur_task = gp_xtos_next_task
	LDR		R1, =gp_xtos_next_task
	LDR		R2, [R1]
	STR		R2, [R0]

	LDR		R0, [R2]									; R0 = gp_xtos_next_task->pTopOfStack
	LDM		R0, {R4-R11}								; װ�����ĵ�Callee Saved Registers
	ADDS	R0, R0, #0x20

	TST 	R14, #0x10									; ����EXC_RETURN��bit4, �ж��Ƿ�����FPU
	IT 		EQ											; ��������, ��װ��S16-S31
	VLDMIAEQ R0!, {S16-S31} 

	MSR		PSP, R0										; ����PSP = gp_xtos_next_task->pTopOfStack
	ORR		LR, LR, #0x04								; ȷ������ʱʹ��PSP��Ϊջָ��

	CPSIE	I											; ���ж�
	BX		LR											; �жϷ��ػָ��ж��ֳ�ʱ����ջ�ռ���ȡ��Caller Saved Registers

	END
