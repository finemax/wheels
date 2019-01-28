#ifndef __QUEUE_H
#define __QUEUE_H

#include <sys/types.h>

#define sq_init(q) \
    do \
      { \
        (q)->head = NULL; \
        (q)->tail = NULL; \
      } \
    while (0)

#define sq_next(q) ((q)->flink)

#define sq_empty(q) ((q)->head == NULL)

#define sq_peek(q) ((q)->head)


struct sq_entry_s
{
    struct sq_entry_s *flink;
};
typedef sq_entry_s sq_queue_t;

struct sq_queue_s
{
    sq_entry_t *head;
    sq_entry_t *tail;
};
typedef struct sq_queue_s sq_queue_t;


#ifdef __cplusplus
extern "C"
{
#endif


void sq_addfirst(sq_entry_t *node, sq_queue_t *queue);
void sq_addlast(sq_entry_t *node, sq_queue_t *queue);

size_t sq_count(sq_queue_t *queue);


#ifdef __cplusplus
}
#endif

#endif
