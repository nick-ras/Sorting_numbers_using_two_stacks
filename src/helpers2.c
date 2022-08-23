/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nickras <nickras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:23:03 by nickras           #+#    #+#             */
/*   Updated: 2022/08/23 09:27:43 by nickras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	indexing_partial(t_push *stack_a, int length)
{
	int		tmp;
	t_push	*first;
	t_push	*tmp_ptr;

	first = stack_a;
	while (stack_a)
	{
		stack_a->index_tmp = -1;
		stack_a = stack_a->next;
	}
	while (length--)
	{
		stack_a = first;
		tmp = -2147483648;
		while (stack_a)
		{
			if (stack_a->num > tmp && stack_a->index_tmp == -1)
			{
				tmp = stack_a->num;
				tmp_ptr = stack_a;
			}
			if (stack_a->next == NULL)
				break ;
			stack_a = stack_a->next;
		}
		tmp_ptr->index_tmp = length;
	}
}

t_push	*lowest_index(t_push *stack)
{
	int		i;
	t_push	*lowest;

	i = 2147483647;

	while (stack)
	{
		if (stack->index <= i)
			lowest = stack; 
		stack = stack->next;
	}
	return (lowest);
}

int	highest_index(t_push *stack)
{
	int		tmp;

	tmp = -2147483648;
	while (stack)
	{
		if (stack->index >= tmp)
			tmp = stack->index;
		stack = stack->next;
	}
	return (tmp);
}

t_push	*go_to_first(t_push *stack)
{
	while (stack->prev)
		stack = stack->prev;
	return (stack);
}
