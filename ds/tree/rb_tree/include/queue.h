/*
 * @Description  : 
 * @Author       : CagedBird
 * @Date         : 2021-03-08 23:56:20
 * @FilePath     : /dataStructure/ds/tree/rb_tree/include/queue.h
 */

#ifndef QUEUE_H
#define QUEUE_H
typedef void* T;
struct _queue;
typedef struct _queue queue;

int queue_is_full(queue* q);
int queue_is_empty(queue* q);
int queue_size(queue* q);
T queue_back(queue* q);
T queue_front(queue* q);
queue* queue_create(int _capacity);
void queue_push_back(queue* q, T element);
void queue_push_front(queue* q, T element);
void queue_pop_back(queue* q);
void queue_pop_front(queue* q);

#endif