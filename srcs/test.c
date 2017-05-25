/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 23:51:29 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/25 21:32:04 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "untyped_list.h"

typedef struct	s_test
{
	int		t1;
	char	*t2;
	struct s_olol { int olol; } olol;
}				t_test;

static t_ulist	*init_list(void)
{
	NEW_LIST(lst2);

	char str1[] = "ABCDE1";
	char str2[] = "ABCDE1";
	char str3[] = "ABCDE1";

	LIST_PUSH_BACK(lst2, str1);
	LIST_PUSH_BACK(lst2, str2);
	LIST_PUSH_BACK(lst2, str3);
	LIST_PUSH_BACK(lst2, "OLOL1");
	LIST_PUSH_BACK(lst2, "OLOL2");
	LIST_PUSH_BACK(lst2, "OLOL3");
	LIST_PUSH_BACK(lst2, "OLOL4");
	LIST_PUSH_FRONT(lst2, "BEGIN");

	return (lst2);
}

int				main(void)
{
	NEW_MANAGED_LIST(lst); //this list will be free at the end of the current scope

	int		a = 32, b = 120, c = 60;

	LIST_PUSH_BACK(lst, ADDRESS_OF(10));
	LIST_PUSH_FRONT(lst, ADDRESS_OF(42));
	LIST_PUSH_FRONT(lst, a);
	LIST_PUSH_FRONT(lst, b);
	LIST_PUSH_FRONT(lst, c);

	//LIST_SHSORT(lst, int, e1 > e2);

	LIST_FOREACH(lst, int, elem, index)
		printf("element at index %zu = %i \n", index, elem);
	
	t_ulist *	lsti = init_list();

	LIST_FOREACH(lsti, char *, e, index)
		printf("strings: %s\n", e);

	NEW_LIST(struct_lst);

	//currently not working:
	//LIST_PUSH_FRONT(lst, ADDRESS_OF((t_test){42, NULL, {4}}));
	
//	t_test t1 = {42, NULL, {4}};
//	LIST_PUSH_FRONT(lst, t1)
}
