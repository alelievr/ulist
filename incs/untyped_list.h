/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nyancat.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 23:52:18 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/25 05:08:42 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NYANCAT_H
# define NYANCAT_H

# pragma clang diagnostic ignored "-Wgnu-statement-expression"
# pragma clang diagnostic ignored "-Wlanguage-extension-token"
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

/*
**	Untyped linked lists:
*/

typedef struct	s_list_links
{
	struct s_list_links	*next;
	struct s_list_links	*prev;
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
	printf("free the list here\n");
}

# define NONE
# define MULTI_4_(_1, _2, _3, _4, _5, NAME, ...) NAME
# define LIST_END_CHECK(lst, ...) ((lst->current == NULL) ? true : (__VA_ARGS__, true))

//TODO: use the type olo = ({type b = 0; b == 0; b}); feature

# define ELEM_GET_(type, l) *((type *)((t_list_links *)l + 1))

# define NEW_LIST(name)			LIST name = (LIST)malloc(sizeof(t_ulist)); LIST_INIT(name);
# define NEW_MANAGED_LIST(name)	LIST name __attribute((cleanup(ulist_cleanup))) = (LIST)malloc(sizeof(t_ulist));; LIST_INIT(name);

# define LIST_INIT(name) name->begin = NULL; name->current = NULL; name->end = NULL; name->count = 0;

# define NEW_ELEM(lst, e)	({ \
		t_list_links * el = malloc(sizeof(t_list_links) + sizeof(e)); \
		el->next = NULL; \
		el->prev = NULL; \
		memcpy(el + 1, (typeof(e) *)(typeof(e)[1]){e}, sizeof(e)); el; \
	})

# define LIST_PUSH_BACK(lst, e) do { \
	t_list_links * elem = NEW_ELEM(lst, e); \
	if (lst->count == 0) { \
		lst->begin = elem; \
		lst->end = elem; \
	} else { \
		elem->prev = lst->end; \
	} \
	lst->end->next = elem; \
	elem->next = NULL; \
	lst->count++; \
} while (false)

# define LIST_PUSH_FRONT(lst, e) { \
	t_list_links *elem = NEW_ELEM(lst, e); \
	elem->prev = NULL; \
	elem->next = lst->begin; \
	lst->begin = elem; \
	lst->count++; \
}

# define LIST_FOREACH_INDEX_(lst, type, elem, index) \
	lst->current = lst->begin; \
	type elem = ELEM_GET_(type, lst->begin); \
	for (size_t index = 0; \
			lst->current && LIST_END_CHECK(lst, elem = ELEM_GET_(type, lst->current)); \
			index++, lst->current = lst->current->next)

# define LIST_FOREACH_(lst, type, elem) \
	type elem = ELEM_GET_(type, lst->begin); \
	for (lst->current = lst->begin; \
			lst->current, elem = ELEM_GET_(type, lst->current); \
			index++, lst->current->next)

# define LIST_FOREACH(lst, type, elem, ...) MULTI_4_(lst, type, elem, __VA_ARGS__, LIST_FOREACH_, LIST_FOREACH_INDEX_, NONE)(lst, type, elem, __VA_ARGS__)

# define LIST_SWAP(lst, pos1, pos2)

# define LIST_SHSORT(lst, type, ...) { \
	type		e1; \
	type		e2; \
	t_list_links *tmp; \
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
	printf("el = %p for index: %zu\n\n", (void *)el, index); \
	el; \
})

# define LIST_AT(lst, type, index) ({ \
	ELEM_GET_(type, LIST_AT_(lst, type, index));\
})

# define LIST_FIND(lst, pred)

# define LIST_INSERT(lst, e, index)

# define LIST_INSERT_SORT(lst, e, cmp)

# define LIST_ANY(lst, pred)

# define LIST_ALL(lst, pred)

# define LIST_REMOVEALL(lst, pred)

# define LIST_REMOVE(lst, index)

# define LIST_CLEAR(lst)

# define LIST_TOARRAY(lst, type)

# define LIST_FINDALL(lst, pref)

# define LIST_REVERSE(lst)

# define LIST_CONCAT(lst1, lst2)

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
