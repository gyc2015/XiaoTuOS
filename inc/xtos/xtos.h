#ifndef XTOS_H
#define XTOS_H

#include <types.h>
#include <list.h>

#include <xtos_time.h>

// xtos�������
typedef void(*xtos_task)(void);

#define XTOS_TASK_STATE_RUNNING		((uint16)0)
#define XTOS_TASK_STATE_SLEEPING	((uint16)1)

/*
 * xtos_task_struct - ����������
 */
typedef struct xtos_task_descriptor {
    uint32 *pTopOfStack;        /* ջ����ַ,��λ�β����Ը��� */
    uint32 *pBottomOfStack;     /* ջ�׵�ַ */
    uint16 pid;                 /* ����ID */
	uint16 taskState;			/* ����״̬ */
    struct list_head list;      /* ������� */
} xtos_task_desp_t;

extern struct xtos_task_descriptor *gp_xtos_cur_task;
extern struct xtos_task_descriptor *gp_xtos_next_task;


int xtos_lock(void);
void xtos_unlock(int key);
/*
 * xtos_init - ��ʼ������ϵͳ
 */
void xtos_init(void);
void xtos_start(void);

/*
 * ���̹���
 */
void xtos_block_task(struct xtos_task_descriptor *tcb);
void xtos_wakeup_task(struct xtos_task_descriptor *tcb);
void xtos_schedule(void);
void xtos_block(void);
/*
 * xtos_init_task_struct - ����һ�����񣬳�ʼ������ջ�ռ�
 *
 * @tcb: ����������
 * @task: ������ں���
 * @stk_bottom: ����ջ��
 * @pid: ����id
 */
void xtos_init_task_descriptor(struct xtos_task_descriptor *tcb, xtos_task task, uint32 *stk_bottom, uint16 pid);

void xtos_distroy_task(void);

#endif // !XTOS_H
