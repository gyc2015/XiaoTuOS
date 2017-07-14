#ifndef XTOS_H
#define XTOS_H

#include <types.h>

// xtos�������
typedef void(*xtos_task)(void);

/*
 * xtos_task_struct - ����������
 */
struct xtos_task_struct {
    uint32 *pTopOfStack;   /* ջ����ַ */
};

extern struct xtos_task_struct *gp_xtos_cur_task;
extern struct xtos_task_struct *gp_xtos_next_task;

void xtos_start(void);
void xtos_context_switch(void);
void xtos_pendsv_handler(void);

void xtos_create_task(struct xtos_task_struct *tcb, xtos_task task, uint32 *stk);
void xtos_distroy_task(void);

#endif // !XTOS_H
