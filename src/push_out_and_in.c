/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_out_and_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nickras <nickras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:44:48 by nickras           #+#    #+#             */
/*   Updated: 2022/08/25 12:59:27 by nickras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

//This function sorts stack a when there is only three numbers
t_push	*sort_3_numbers(t_push *stack, t_count *instr_2, int argc)
{
	t_push	*next_one;

	reset_count_rotations(instr_2);
	while (stack->next)
	{
		next_one = stack->next;
		if (stack->index != next_one->index + 1)
			stack = sa_first_and_last(go_to_first(stack), instr_2);
		if (stack->index == next_one->index + 1)
			execute_stack_a(stack, instr_2);
		sort_check_full(go_to_first(stack), instr_2, argc);
		instr_2->stack_a_pos++;
		stack = stack->next;
	}
	return (go_to_first(stack));
}

//If there is only 4 numbers in stack, it sorts them. If its 5 numbers, it hands 
//stack to another functions. It pushes 1-2 numbers to stack b and sorts them back.
void	sort_five_numbers(t_push *stack_a, t_push *stack_b, t_count *instr_2)
{
	t_push	*tmp;

	tmp = stack_a->next;
	stack_b = pb_first_push(stack_a, stack_b);
	stack_a = tmp;
	if (length_list(stack_a) == 4)
	{
		tmp = stack_a->next;
		stack_b = pb(stack_a, stack_b);
		stack_a = tmp;
	}
	stack_a = use_sa_5(stack_a, instr_2);
	sorting_back(stack_a, stack_b, instr_2);
}

//This one sorts stack a when there is only 5 numbers
t_push	*use_sa_5(t_push *stack, t_count *instr_2)
{
	t_push	*next_one;
	int		length;

	stack = go_to_first(stack);
	length = length_list(stack);
	indexing_partial(stack, length);
	while (stack->next)
	{
		next_one = stack->next;
		if (stack->index_tmp != next_one->index_tmp + 1)
			stack = sa_first_and_last(go_to_first(stack), instr_2);
		if (stack->index_tmp == next_one->index_tmp + 1)
			execute_stack_a(stack, instr_2);
		if (sort_check_partial(go_to_first(stack)))
			break ;
		instr_2->stack_a_pos++;
		stack = stack->next;
	}
	return (go_to_first(stack));
}

//if bottom element on stack a is the closest lower index of stack a.
//It then revers rotate stack a and swaps the two element
t_push	*sa_first_and_last(t_push *stack, t_count *instr_2)
{
	if (stack->index + 1 == ft_lstlast_new(stack)->index \
	|| stack->index_tmp + 1 == ft_lstlast_new(stack)->index_tmp)
	{
		instr_2->ra = -1;
		instr_2->rr = 0;
		stack = execute_instructions(stack, NULL, instr_2);
		stack = sa(stack);
	}
	reset_count_rotations(instr_2);
	return (stack);
}

//All element of stack a, which is not part of longest increasing subsequent,
//are being pushed to stack b. In the end it invokes another function
//which pushed them back to stack a (this function has many subfunctions)
void	push_out_and_in(t_push *stack_a, int argc, t_count *instr_2)
{
	t_push	*stack_b;
	t_push	*tmp;

	stack_b = NULL;
	while (argc > 1)
	{
		if (sort_check_partial(stack_a))
			break ;
		if (stack_a->subs)
		{
			write(1, "ra\n", 3);
			stack_a = r(stack_a);
		}
		else
		{
			tmp = stack_a->next;
			if (!stack_b)
				stack_b = pb_first_push(stack_a, stack_b);
			else
				stack_b = pb(stack_a, stack_b);
			stack_a = tmp;
		}
		argc--;
	}
	sorting_back(go_to_first(stack_a), stack_b, instr_2);
}

//Sorting numbers in stack b back to stack a, by using a lower number of commands.
void	sorting_back(t_push *stack_a, t_push *stack_b, t_count *instr_2)
{
	initialize_instructions_struct(instr_2);
	while (stack_b)
	{
		make_instructions(stack_a, go_to_first(stack_a), stack_b, instr_2);
		if (abs_val(instr_2->ra_bg) + abs_val(instr_2->rr_bg) \
		< abs_val(instr_2->ra) + abs_val(instr_2->rr))
		{
			instr_2->ra = instr_2->ra_bg;
			instr_2->rr = instr_2->rr_bg;
			stack_b = execute_instructions(stack_a, stack_b, instr_2);
		}
		else
			stack_b = execute_instructions(stack_a, stack_b, instr_2);
		stack_a = go_to_first(stack_a);
	}
	sort_low_to_high(stack_a, instr_2);
}
