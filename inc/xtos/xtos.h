#ifndef XTOS_H
#define XTOS_H

#include <types.h>
#include <list.h>

#include <xtos_time.h>

// xtos�������
typedef void(*xtos_task)(void);

/*
 * xtos_task_struct - ����������
 */
typedef struct xtos_task_descriptor {
    uint32 *pTopOfStack;        /* ջ����ַ,��λ�β����Ը��� */
    uint32 *pBottomOfStack;     /* ջ�׵�ַ */
    uint16 pid;                 /* ����ID */
    struct list_head list;      /* ������� */
} xtos_task_desp_t;

extern struct xtos_task_descriptor *gp_xtos_cur_task;
extern struct xtos_task_descriptor *gp_xtos_next_task;

/*
 * xtos_init - ��ʼ������ϵͳ
 */
void xtos_init(void);
void xtos_start(void);
void xtos_schedule(void);

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
