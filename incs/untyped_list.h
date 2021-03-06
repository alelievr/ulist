/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nyancat.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 23:52:18 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/25 21:32:36 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NYANCAT_H
# define NYANCAT_H

# define DEBUG

# pragma clang diagnostic ignored "-Wgnu-statement-expression"
# pragma clang diagnostic ignored "-Wlanguage-extension-token"
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

/*
**	Untyped linked lists:
*/

typedef struct	s_node_data
{
	bool		addressing;
	long		:56;
}				t_node_data;

typedef struct	s_list_links
{
	struct s_list_links	*next;
	struct s_list_links	*prev;
	t_node_data			data;
}				t_list_links;

typedef struct	s_ulist
{
	t_list_links	*begin;
	t_list_links	*current;
	t_list_links	*end;
	size_t			count;
}				t_ulist;

# define LIST		t_ulist *

static size_t *		gap_sequence = (size_t *)(size_t []){701, 301, 132, 57, 23, 10, 4, 1};
static const int	gap_sequence_count = 8;

void			ulist_cleanup(LIST *lst);
void			ulist_cleanup(LIST *lst)
{
	(void)lst;
	//TODO: free list
}

# define NONE
# define MULTI_4_(_1, _2, _3, _4, NAME, ...) NAME
# define LIST_END_CHECK(lst, ...) ((lst->current == NULL) ? true : (__VA_ARGS__, true))

//TODO: use the type olo = ({type b = 0; b == 0; b}); feature

# define ADDRESS_OF(...) *((typeof(__VA_ARGS__)[1]){__VA_ARGS__})

# define GET_HARD_ADDR_(...) (void *)(unsigned long)(__VA_ARGS__)//*(void **)(unsigned long)&(__VA_ARGS__)

/*({ int64_t out = 0; asm volatile( \
			"movq %1, rax;\n" \
			"movq rax, %0;\n" \
 		   	: "=r"(out) : "r"(__VA_ARGS__) : "rax"); (void *)out; })*/

# define ELEM_GET_(type, l) ((l->data.addressing) ? (type)(l + 1) : *((type *)(l + 1)))

# define NEW_LIST(name)			LIST name = (LIST)malloc(sizeof(t_ulist)); LIST_INIT(name)
# define NEW_MANAGED_LIST(name)	LIST name __attribute((cleanup(ulist_cleanup))) = (LIST)malloc(sizeof(t_ulist)); LIST_INIT(name)

# define LIST_INIT(name) name->begin = NULL; name->current = NULL; name->end = NULL; name->count = 0

# define EXPAND(...) __VA_ARGS__ 

# define STRINGIFY(x) #x

# define NEW_ELEM(lst, ...)	({ \
		t_list_links * el = malloc(sizeof(t_list_links) + sizeof(__VA_ARGS__)); \
		el->next = NULL; \
		el->prev = NULL; \
		el->data.addressing = ((void *)&(__VA_ARGS__) == GET_HARD_ADDR_(__VA_ARGS__)); \
		memcpy(el + 1, &(__VA_ARGS__), sizeof(__VA_ARGS__)); \
		el; \
	})

# define LIST_PUSH_BACK(lst, ...) { \
	t_list_links * elem = NEW_ELEM(lst, __VA_ARGS__); \
	if (lst->count == 0) { \
		lst->begin = elem; \
		lst->end = elem; \
	} else { \
		elem->prev = lst->end; \
	} \
	lst->end->next = elem; \
	elem->next = NULL; \
	lst->end = elem; \
	lst->count++; \
}

# define LIST_PUSH_FRONT(lst, ...) { \
	t_list_links *elem = NEW_ELEM(lst, __VA_ARGS__); \
	if (lst->count == 0) {\
		lst->begin = elem; \
		lst->end = elem; \
	} \
	else { \
		elem->next = lst->begin; \
	} \
	elem->prev = NULL; \
	lst->begin = elem; \
	lst->count++; \
}

# define LIST_FOREACH_INDEX_(lst, type, elem, index) \
	lst->current = lst->begin; \
	type elem; \
	for (size_t index = 0; \
			lst->current && ((elem = ELEM_GET_(type, lst->current)), true); \
			index++, lst->current = lst->current->next)

# define LIST_FOREACH_(lst, type, elem) \
	type elem = ELEM_GET_(type, lst->begin); \
	for (lst->current = lst->begin; \
			lst->current, elem = ELEM_GET_(type, lst->current); \
			lst->current = lst->current->next)

# define LIST_FOREACH(...) MULTI_4_(__VA_ARGS__, LIST_FOREACH_INDEX_, LIST_FOREACH_, NONE, NONE)(__VA_ARGS__)

# define LIST_SWAP(lst, pos1, pos2)

//FIXME
# define LIST_SHSORT(lst, type, ...) { \
	type			e1; \
	type			e2; \
	t_list_links	*tmp; \
 \
	for (size_t gap = 0; gap < gap_sequence_count; gap++) \
	{ \
		for (size_t i = gap; i < lst->count; i++) \
		{ \
			tmp = LIST_AT_(lst, type, i); \
 \
			e1 = ELEM_GET_(type, tmp); \
			e2 = LIST_AT(lst, type, i - gap); \
			for (size_t j = i; j >= gap && ({__VA_ARGS__;}); j -= gap) \
			{ \
				LIST_SWAP(lst, j, j - gap); \
				e2 = LIST_AT(lst, type, j - gap); \
			} \
			LIST_SET(lst, j, tmp); \
		} \
	} \
}

# define LIST_SET(lst, index, e)

# define LIST_AT_(lst, type, index) ({ \
	t_list_links *el = NULL; \
 \
	if (index == lst->count - 1) \
		el = lst->end; \
	else if (index == 0) \
		el = lst->begin; \
	else \
	{ \
		lst->current = lst->begin; \
		for (size_t __i = 0; __i < index && lst->current; __i++) \
			lst->current = lst->current->next; \
	} \
	el; \
})

# define LIST_AT(lst, type, index) ({ \
	ELEM_GET_(type, LIST_AT_(lst, type, index));\
})

# define LIST_FIND(lst, pred) //TODO

# define LIST_INSERT(lst, e, index) //TODO

# define LIST_INSERT_SORT(lst, e, cmp) //TODO

# define LIST_ANY(lst, pred) //TODO

# define LIST_ALL(lst, pred) //TODO

# define LIST_REMOVEALL(lst, pred) //TODO

# define LIST_REMOVE(lst, index) //TODO

# define LIST_CLEAR(lst) //TODO

# define LIST_TOARRAY(lst, type) //TODO

# define LIST_FINDALL(lst, pref) //TODO

# define LIST_REVERSE(lst) //TODO

# define LIST_CONCAT(lst1, lst2) //TODO

# define LIST_FIRST(lst)	ELEM_GET_(lst->begin)

# define LIST_END(lst)		ELEM_GET_(lst->end);

# define LIST_COUNT(lst)	lst->count

/*
# define VOID				void
# define LAST_ADDR(x)		(*((VOID *[1]){0} + x))
# define LIST				t_untyped_list *
# define LIST_INIT(l,p)		l = malloc(sizeof(t_untyped_list)); l->base = NULL; l->current = NULL; l->end = NULL; l->pointer = p;
# define LIST_NEXT_(ptr)	*((unsigned long *)ptr)
# define LIST_PREV_(ptr)	*((unsigned long *)ptr + 1)
# define LIST_NEW(l, e)		*((VOID *[1]){malloc(sizeof(t_list_links) + sizeof(e))}); \
	LIST_NEXT_(LAST_ADDR(1)) = 0llu; \
	LIST_PREV_(LAST_ADDR(2)) = 0llu; \
	memcpy(LAST_ADDR(3) + sizeof(t_list_links), (l->pointer) ? (VOID *)e : (VOID *)(typeof(e)[]){e}, sizeof(e)); \

# define LIST_PUSH_BACK(l,e)if (!l->base) { l->base = LIST_NEW(l, e); l->end = l->base; l->current = l->base; } else { l->end->next = LIST_NEW(l, e); l->end = l->end->next; l->current = l->end; }
# define LIST_PUSH_FRONT(l,e)if (!l->base) { l->base = LIST_NEW(l, e); l->end = l->base; l->current = l->base; } else { l->base->prev = LIST_NEW(l, e); l->base = l->base->prev; l->current = l->base; }

# define LIST_DATA_(node) ((VOID *)node + sizeof(t_list_links))
# define LIST_GET_(l, type, node) (l->pointer) ? (type)LIST_DATA_(node) : *(type *)LIST_DATA_(node)

# define LIST_CURRENT(l, type) LIST_GET_(l, type, l->current)

# define LIST_AT(l, i) 

#define LIST_CONTENT(elem, type) ((type)((VOID *)elem + sizeof(t_list_links))) 
# define LIST_FOREACH(l, type, as) type __##as; t_untyped_list *__iter##as; \
	for ((__##as = LIST_CONTENT(l->base, type), __iter##as = l->begin); \
			__iter##as; (__##as = LIST_CONTENT(__iter##as, type), __iter##as = __iter##as->next))

# define LIST_SWAP(l, i, j)

# define LIST_SORT(l, cmp)

# define LIST_INSERT_AT(l, e)

# define LIST_INSERT_SORT(l, e, cmp)

# define LIST_FIND(l, pred)

# define LIST_FIRST(l, type) LIST_GET_(l, type, l->base)

# define LIST_LAST(l, type) LIST_GET_(l, type, l->end)*/

#endif
