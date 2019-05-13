#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20

typedef int status_t;
typedef int elem_type_t;

typedef struct node_t {
	elem_type_t data;
	struct node_t *next;
} node_t;

typedef struct node_t *link_list_t;

status_t init_list(link_list_t *L)
{
	*L = (link_list_t)malloc(sizeof(node_t));
	if(!L) {
		return ERROR;
	}
	(*L)->next = NULL;

	return OK;
}

int list_length(link_list_t L)
{
	int i=0;
	link_list_t p = L->next;
	while(p) {
		i++;
		p = p->next;
	}
	return i;
}

status_t clear_list(link_list_t *L)
{
	link_list_t p,q;
	p = (*L)->next;
	while(p) {
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	return OK;
}

status_t visit(elem_type_t c)
{
	printf("-> %d", c);
	return OK;
}

status_t list_traverse(link_list_t L)
{
	link_list_t p = L->next;
	while(p) {
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

status_t list_traverse_limit(link_list_t L, int n)
{
	int i = 0;
	link_list_t p = L->next;
	while(p && i < n) {
		visit(p->data);
		p = p->next;
		i++;
	}
	return OK;
}
status_t get_elem(link_list_t L, int i, elem_type_t *e)
{
	int j;
	link_list_t p;
	p = L->next;
	j = 1;
	while(p && j < i) {
		p = p->next;
		++j;
	}
	if(!p || j > i){
		return ERROR;
	}
	*e = p->data;
	return OK;
}

int locate_elem(link_list_t L, elem_type_t e)
{
	int i=0;
	link_list_t p = L->next;
	while(p){
		i++;
		if(p->data == e){
			return i;
		}
		p = p->next;
	}

	return 0;
}

void create_list_head(link_list_t * L, int n)
{
	link_list_t p;
	int i;
	srand(time(0));
	*L = (link_list_t)malloc(sizeof(node_t));
	(*L)->next = NULL;
	for(i = 0; i < n; i++){
		p = (link_list_t)malloc(sizeof(node_t));
		p->data = rand()%100 + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

void create_list_tail(link_list_t * L, int n)
{
	link_list_t p,r;
	int i;
	srand(time(0));
	*L = (link_list_t)malloc(sizeof(node_t));
	r = *L;
	for(i = 0; i < n; i++){
		p = (link_list_t)malloc(sizeof(node_t));
		p->data = rand()%100 + 1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

status_t list_insert(link_list_t *L, int i, elem_type_t e)
{
	int j;
	link_list_t p,s;
	p = *L;
	j = 1;
	while(p && j < i) {
		p = p->next;
		++j;
	}
	if(!p || j > i){
		return ERROR;
	}
	s = (link_list_t)malloc(sizeof(node_t));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

status_t list_delete(link_list_t *L, int i, elem_type_t *e)
{
	int j;
	link_list_t p,q;
	p = *L;
	j = 1;
	while(p->next && j < i) {
		p = p->next;
		++j;
	}
	if(!(p->next) || j > i) {
		return ERROR;
	}
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

status_t list_reverse(link_list_t L)
{
	link_list_t current, pnext, prev;
	if(L == NULL || L->next == NULL) {
		return ERROR;
	}
	current = L->next;
	pnext = current->next;
	current->next = NULL;
	while (pnext) {
		prev = pnext->next;
		pnext->next = current;
		current = pnext;
		pnext = prev;
	}
//	printf("current = %d,next = %d\n", current->data, current->next->data);
	L->next = NULL;
	return OK;
}

status_t list_reverse2(link_list_t L)
{
	link_list_t current,p;
	if(L == NULL) {
		return ERROR;
	}
	current = L->next;
	while(current->next != NULL) {
		p = current->next;
		current->next = p->next;
		p->next = L->next;
		L->next = p;
		list_traverse(L);
		printf("current = %d, \n", current->data);
	}
	return OK;
}

link_list_t  list_reverse3(link_list_t L)
{
	link_list_t new_list;
	link_list_t tmp;

	if(L == NULL || (new_list = (link_list_t)malloc(sizeof(node_t))) == NULL){
		return NULL;
	}

	new_list->data = L->data;
	new_list->next = NULL;

	while(L->next != NULL) {
		tmp = new_list->next;
		new_list->next = L->next;
		L->next = L->next->next;
		new_list->next->next = tmp;
	}
	free(L);
	return new_list;
}

status_t get_n_th_node_from_tail(link_list_t L, int n, elem_type_t *e) 
{
	int i=0;
	link_list_t first_node = L;
	while(i < n && first_node->next != NULL) {
		i++;
		first_node = first_node->next;
	}
	if(first_node->next == NULL && i < n-1) {
		printf("length list too short");
		return ERROR;
	}
	link_list_t sec_node = L;
	while(first_node != NULL) {
		sec_node = sec_node->next;
		first_node = first_node->next;
	}
	*e = sec_node->data;
	return OK;
}

status_t get_mid_node(link_list_t L, elem_type_t *e)
{
	link_list_t search,mid;
	mid = search = L;
	while(search->next != NULL) {
		if(search->next->next != NULL) {
			search = search->next->next;
			mid = mid->next;
		}
		else {
			search = search->next;
		}
	}
	*e = mid->data;
	return OK;
}

int has_loop(link_list_t L)
{
	link_list_t p = L;
	link_list_t q = L;
	while(p != NULL && q != NULL && q->next != NULL) {
		p = p->next;
		if (q->next != NULL) {
			q = q->next->next;
		}
		if (q == p) {
			return 1;
		}
	}
	return 0;
}

int has_loop2(link_list_t L) 
{
	link_list_t cur1 = L;
	int pos1 = 0;
	while(cur1) {
		link_list_t cur2 = L;
		int pos2 = 0;
		pos1++;
		while(cur2) {
			pos2++;
			if (cur2 == cur1) {
				break;
			} else {
				return 1;
			}
			cur2 = cur2->next;
		}
		cur1 = cur1->next;
	}
	return 0;
}

status_t build_list_loop(link_list_t *L, int num)
{
	int i = 0;
	link_list_t cur = *L;
	link_list_t tail = NULL;
	if (num <= 0 || L == NULL) {
		return ERROR;
	}
	for (i = 1; i < num; ++i) {
		if(cur == NULL) {
			return ERROR;
		}
		cur = cur->next;
	}
	tail = cur;
	while(tail->next) {
		tail = tail->next;
	}
	tail->next = cur;
	return OK;
}

link_list_t remove_dup_node(link_list_t L)
{
	link_list_t p,q,r;
	p = L->next;
	while(p) {
		q = p;
		while(q->next) {
			if (q->next->data == p->data) {
				r = q->next;
				q->next = r->next;
				free(r);
			} else {
				q = q->next;
			}
		}
		p = p->next;
	}
	return L;
}
int main(void)
{
	link_list_t L;
	status_t i;
	int j,k,pos,value;
	char opp;
	elem_type_t e;
	i = init_list(&L);
	printf("\nlist init done, list_length(L) = %d\n", list_length(L));
	printf("\n1. list create(head) \n2. list create(tail) \n3. list traverse \n4. list insert");
	printf("\n5. list delete \n6. get list node data \n7. fine data in list \n8. clear list");
	printf("\n9. list reverse");
	printf("\n0. exit \nplease input: \n");
	while(opp != '0') {
		scanf("%c", &opp);
		switch(opp){
			case 1:
				create_list_head(&L, 10);
				printf("list create (head)\n");
				list_traverse(L);
				printf("\n");
				break;
			case 2:
				create_list_tail(&L, 10);
				printf("list create (tail)\n");
				list_traverse(L);
				printf("\n");
				break;
			case 3:
				list_traverse(L);
				printf("\n");
				break;
			case 4:
				printf("which node to insert");
				scanf("%d", &pos);
				printf("nod value to insert");
				scanf("%d", &value);
				list_insert(&L, pos, value);
				list_traverse(L);
				printf("\n");
				break;
			case 5:
				printf("which node to delete");
				scanf("%d", &pos);
				list_delete(&L, pos, &e);
				printf("delete num %d node done, curren list: \n", pos);
				list_traverse(L);
				printf("\n");
			case 6:
				printf("which node to get");
				scanf("%d", &pos);
				get_elem(L, pos, &e);
				printf("num %d node value: %d\n", pos,e);
				printf("\n");
				break;
			case 7:
				printf("input data to find");
				scanf("%d", &pos);
				k = locate_elem(L, pos);
				if(k) {
					printf("num %d node value: %d\n", k,pos);
				}
				else {
					printf("no node vale %d\n", pos);
				}
				printf("\n");
				break;
			case 8:
				i = clear_list(&L);
				printf("\n after list cleared: list_length(L) = %d\n", list_length(L));
				list_traverse(L);
				printf("\n");
				break;
			case 9:
				list_reverse2(L);
				printf("\n after reverse\n");
				list_traverse(L);
				printf("\n");
				break;
			case 10:
				printf("which node value from tail to find");
				scanf("%d", &value);
				get_n_th_node_from_tail(L, value, &e);
				printf("%d node value from tail is: %d\n", value, e);
				printf("\n");
				break;
			case 11:
				get_mid_node(L, &e);
				printf("the mid node value is: %d\n", e);
				printf("\n");
				break;
			case 12:
				if(has_loop(L)) {
					printf("method 1: has loop\n");
				} else {
					printf("method 1: no loop\n");
				}
				if(has_loop2(L)) {
					printf("method 2: has loop\n");
				} else {
					printf("method 2: no loop\n");
				}
				printf("\n");
				break;
			case 13:
				printf("which node to build loop");
				scanf("%d", &pos);
				build_list_loop(&L, pos);
				list_traverse_limit(L, 20);
				printf("\n");
				break;
			case 14:
				remove_dup_node(L);
				list_traverse(L);
				printf("\n");
				break;
			case 0:
				exit(0);
		}
	}

	return 0;
}
