#include "queue.h"

void sq_addlast(sq_entry_t *node, sq_queue_t *queue)
{
    node->flink = NULL;
    if (!queue->head) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->flink = node;
        queue->tail = node;
    }
}

void sq_addfirst(sq_entry_t *node, sq_queue_t *queue)
{
    node->flink = queue->head;
    if (!queue->head) {
        queue->tail = node;
    }

    queue->head = node;
}

size_t sq_count(sq_queue_t *queue)
{
    sq_entry_t *node;
    size_t count;

    assert(queue != NULL);

    for (node = queue->head, count = 0;
         node != NULL;
         node = node->flink, count++);

    return count;
}
