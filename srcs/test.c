/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 23:51:29 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/25 18:38:07 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "untyped_list.h"

int		main(void)
{
/*	NEW_MANAGED_LIST(lst); //this list will be free at the end of the current scope

	LIST_PUSH_BACK(lst, 10);
	LIST_PUSH_FRONT(lst, 42);
	LIST_PUSH_FRONT(lst, 32);
	LIST_PUSH_FRONT(lst, 120);
	LIST_PUSH_FRONT(lst, 60);

	//LIST_SHSORT(lst, int, e1 > e2);

	LIST_FOREACH(lst, int, elem, index)
		printf("element at index %zu = %i \n", index, elem);*/

	NEW_LIST(lst2);

	LIST_PUSH_BACK(lst2, "olol1");
	LIST_PUSH_BACK(lst2, "olol2");
	LIST_PUSH_BACK(lst2, "olol3");
	LIST_PUSH_BACK(lst2, "olol4");
	LIST_PUSH_BACK(lst2, "olol5");

	LIST_FOREACH(lst2, const char *, elem)
		printf("strings: %s\n", elem);
}
