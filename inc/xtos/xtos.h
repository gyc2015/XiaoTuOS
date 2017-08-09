#ifndef XTOS_H
#define XTOS_H

#include <types.h>
#include <list.h>

#include <xtos_time.h>

// xtos任务入口
typedef void(*xtos_task)(void);

/*
 * xtos_task_struct - 任务描述符
 */
typedef struct xtos_task_descriptor {
    uint32 *pTopOfStack;        /* 栈顶地址,该位段不可以更改 */
    uint32 *pBottomOfStack;     /* 栈底地址 */
    uint16 pid;                 /* 进程ID */
    struct list_head list;      /* 链表对象 */
} xtos_task_desp_t;

extern struct xtos_task_descriptor *gp_xtos_cur_task;
extern struct xtos_task_descriptor *gp_xtos_next_task;

/*
 * xtos_init - 初始化操作系统
 */
void xtos_init(void);
void xtos_start(void);
void xtos_schedule(void);

/*
 * xtos_init_task_struct - 创建一个任务，初始化任务栈空间
 *
 * @tcb: 任务描述符
 * @task: 任务入口函数
 * @stk_bottom: 任务栈底
 * @pid: 任务id
 */
void xtos_init_task_descriptor(struct xtos_task_descriptor *tcb, xtos_task task, uint32 *stk_bottom, uint16 pid);

void xtos_distroy_task(void);

#endif // !XTOS_H
