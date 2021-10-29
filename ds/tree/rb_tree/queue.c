#include <stdlib.h>

typedef void *T;

struct _queue {
        T *elements;
        int capacity;
        int size;
        int head;
        int rear;
        // (front) head <- -> rear (back)
};
typedef struct _queue queue;

int queue_is_full(queue *q)
{
        return q->size >= q->capacity;
}
int queue_is_empty(queue *q)
{
        return q->size <= 0;
}
int queue_size(queue *q)
{
        return q->size;
}
T queue_back(queue *q)
{
        return q->elements[q->rear];
}
T queue_front(queue *q)
{
        return q->elements[q->head];
}

queue *queue_create(int _capacity)
{
        queue *q = (queue *)malloc(sizeof(queue));
        q->capacity = _capacity;
        q->elements = (T *)malloc(q->capacity * sizeof(T));
        q->size = 0;
        q->head = 1;
        q->rear = 0;
        return q;
}
static void _queue_incrementCapicity(queue *q)
{
        int newCapicity = q->capacity * 2;
        T *newElements = (T *)malloc(newCapicity * sizeof(queue));
        /* T* newElements = new T[newCapicity]; cpp version*/
        int j = 0;
        for (int i = q->head; i < q->capacity; i++)
                newElements[j++] = q->elements[i];
        q->head = 0;
        for (int i = 0; j < q->capacity; i++)
                newElements[j++] = q->elements[i];
        q->rear = j - 1;
        /* delete[] elements; cpp version*/
        free(q->elements);
        q->elements = newElements;
        q->capacity = newCapicity;
}

void queue_push_back(queue *q, T element)
{
        if (queue_is_full(q))
                _queue_incrementCapicity(q);
        if (++q->rear >= q->capacity)
                q->rear = 0;
        q->elements[q->rear] = element;
        q->size++;
}
void queue_push_front(queue *q, T element)
{
        if (queue_is_full(q))
                _queue_incrementCapicity(q);
        if (--q->head < 0)
                q->head = q->capacity - 1;
        q->elements[q->head] = element;
        q->size++;
}
void queue_pop_back(queue *q)
{
        if (!queue_is_empty(q)) {
                if (--q->rear < 0)
                        q->rear = q->capacity - 1;
                q->size--;
        }
}
void queue_pop_front(queue *q)
{
        if (!queue_is_empty(q)) {
                if (++q->head >= q->capacity)
                        q->head = 0;
                q->size--;
        }
}

/* int main()
{
        queue *myQueue = queue_create(3);
        for (int i = 0; i < 10; i++) {
                queue_push_back(myQueue, i + 1);
                for (int i = 0; i < myQueue->capacity; i++) {
                        printf("%d ", myQueue->elements[i]);
                }
                printf("\nhead: %d, rear: %d\n", myQueue->head, myQueue->rear);
        }
} */