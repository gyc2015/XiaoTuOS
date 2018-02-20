#ifndef XTOS_H
#define XTOS_H

#include <types.h>
#include <list.h>

#include <xtos_time.h>

// xtos任务入口
typedef void(*xtos_task)(void);

#define XTOS_TASK_STATE_RUNNING		((uint16)0)
#define XTOS_TASK_STATE_SLEEPING	((uint16)1)

/*
 * xtos_task_struct - 任务描述符
 */
typedef struct xtos_task_descriptor {
    uint32 *pTopOfStack;        /* 栈顶地址,该位段不可以更改 */
    uint32 *pBottomOfStack;     /* 栈底地址 */
    uint16 pid;                 /* 进程ID */
	uint16 taskState;			/* 进程状态 */
    struct list_head list;      /* 链表对象 */
} xtos_task_desp_t;

extern struct xtos_task_descriptor *gp_xtos_cur_task;
extern struct xtos_task_descriptor *gp_xtos_next_task;


int xtos_lock(void);
void xtos_unlock(int key);
/*
 * xtos_init - 初始化操作系统
 */
void xtos_init(void);
void xtos_start(void);

/*
 * 进程管理
 */
void xtos_block_task(struct xtos_task_descriptor *tcb);
void xtos_wakeup_task(struct xtos_task_descriptor *tcb);
void xtos_schedule(void);
void xtos_block(void);
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
