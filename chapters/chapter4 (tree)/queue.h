/*
 * @Description  : 
 * @Author       : CagedBird
 * @Date         : 2021-03-08 23:56:20
 * @FilePath     : /dataStructure/chapters/chapter4 (tree)/queue.h
 */

#ifndef QUEUE_H
#define QUEUE_H
typedef int T;
typedef struct {
        T *elements;
        int capacity;
        int size;
        int head;
        int rear;
        // (front) head <- -> rear (back)

} queue;
#define queue_is_full(q)  ((q)->size >= (q)->capicity)
#define queue_is_empty(q) ((q)->size <= 0)
#define queue_size(q)     ((q)->size)
#define queue_back(q) ((q)->elements[(q)->rear])
#define queue_front(q) ((q)->elements[(q)->head])

queue *queue_create(int _capicity);
void queue_push_back(queue *q, T element);
void push_front(queue *q, T element);
void queue_pop_back(queue *q);
void queue_pop_front(queue *q);

#endif