#include <xtos.h>

struct xtos_task_struct *gp_xtos_cur_task;
struct xtos_task_struct *gp_xtos_next_task;

/*
 * xtos_task_finished - ���������Ļص�����
 */
void xtos_distroy_task() {
    // to do...
    while(1){}
}
/*
 * xtos_create_task - ����һ�����񣬳�ʼ������ջ�ռ�
 *
 * @tcb: ����������
 * @task: ������ں���
 * @stk: ����ջ��
 */
void xtos_create_task(struct xtos_task_struct * tcb, xtos_task task, uint32 * stk) {
    uint32  *pstk;
    pstk = stk;
    pstk = (uint32 *)((uint32)(pstk) & 0xFFFFFFF8uL);

    *(--pstk) = (uint32)0x00000000L; //No Name Register  
    *(--pstk) = (uint32)0x00001000L; //FPSCR
    *(--pstk) = (uint32)0x00000015L; //s15
    *(--pstk) = (uint32)0x00000014L; //s14
    *(--pstk) = (uint32)0x00000013L; //s13
    *(--pstk) = (uint32)0x00000012L; //s12
    *(--pstk) = (uint32)0x00000011L; //s11
    *(--pstk) = (uint32)0x00000010L; //s10
    *(--pstk) = (uint32)0x00000009L; //s9
    *(--pstk) = (uint32)0x00000008L; //s8
    *(--pstk) = (uint32)0x00000007L; //s7
    *(--pstk) = (uint32)0x00000006L; //s6
    *(--pstk) = (uint32)0x00000005L; //s5
    *(--pstk) = (uint32)0x00000004L; //s4
    *(--pstk) = (uint32)0x00000003L; //s3
    *(--pstk) = (uint32)0x00000002L; //s2
    *(--pstk) = (uint32)0x00000001L; //s1
    *(--pstk) = (uint32)0x00000000L; //s0

    *(--pstk) = (uint32)0x01000000uL; // xPSR
    *(--pstk) = (uint32)task;         // Entry Point
    *(--pstk) = (uint32)xtos_distroy_task; // R14 (LR)
    *(--pstk) = (uint32)0x12121212uL; // R12
    *(--pstk) = (uint32)0x03030303uL; // R3
    *(--pstk) = (uint32)0x02020202uL; // R2
    *(--pstk) = (uint32)0x01010101uL; // R1
    *(--pstk) = (uint32)0x00000000u;  // R0

    *(--pstk) = (uint32)0x00000031L; //s31
    *(--pstk) = (uint32)0x00000030L; //s30
    *(--pstk) = (uint32)0x00000029L; //s29
    *(--pstk) = (uint32)0x00000028L; //s28
    *(--pstk) = (uint32)0x00000027L; //s27
    *(--pstk) = (uint32)0x00000026L; //s26	
    *(--pstk) = (uint32)0x00000025L; //s25
    *(--pstk) = (uint32)0x00000024L; //s24
    *(--pstk) = (uint32)0x00000023L; //s23
    *(--pstk) = (uint32)0x00000022L; //s22
    *(--pstk) = (uint32)0x00000021L; //s21
    *(--pstk) = (uint32)0x00000020L; //s20
    *(--pstk) = (uint32)0x00000019L; //s19
    *(--pstk) = (uint32)0x00000018L; //s18
    *(--pstk) = (uint32)0x00000017L; //s17
    *(--pstk) = (uint32)0x00000016L; //s16

    *(--pstk) = (uint32)0x11111111uL; // R11
    *(--pstk) = (uint32)0x10101010uL; // R10
    *(--pstk) = (uint32)0x09090909uL; // R9
    *(--pstk) = (uint32)0x08080808uL; // R8
    *(--pstk) = (uint32)0x07070707uL; // R7
    *(--pstk) = (uint32)0x06060606uL; // R6
    *(--pstk) = (uint32)0x05050505uL; // R5
    *(--pstk) = (uint32)0x04040404uL; // R4

    tcb->pTopOfStack = pstk;
}
