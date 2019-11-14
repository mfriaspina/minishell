/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:56:59 by mfrias            #+#    #+#             */
/*   Updated: 2019/07/02 13:38:34 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		split(t_files *src, t_files **front, t_files **back)
{
	t_files *fast;
	t_files *slow;

	slow = src;
	fast = src->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = src;
	*back = slow->next;
	slow->next = NULL;
}

static t_files	*merge_time(t_files *a, t_files *b)
{
	t_files *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->time > b->time)
	{
		result = a;
		result->next = merge_time(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge_time(a, b->next);
	}
	return (result);
}

static t_files	*merge(t_files *a, t_files *b)
{
	t_files *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->nopath, b->nopath) < 0)
	{
		result = a;
		result->next = merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge(a, b->next);
	}
	return (result);
}

void			sort(t_files **list, char sortby)
{
	t_files *head;
	t_files *a;
	t_files *b;

	head = *list;
	if ((head == NULL) || (head->next == NULL))
		return ;
	split(head, &a, &b);
	sort(&a, sortby);
	sort(&b, sortby);
	if (!sortby)
		*list = merge(a, b);
	else
		*list = merge_time(a, b);
}

void			reverse(t_files **list)
{
	t_files *last;
	t_files *this;
	t_files *next;

	last = NULL;
	this = *list;
	next = NULL;
	while (this != NULL)
	{
		next = this->next;
		this->next = last;
		last = this;
		this = next;
	}
	*list = last;
}
