#include "../push_swap.h"

void	make_instructions(t_push *stack_a, t_push *stack_b, \
t_count *instructions)
{
	t_push	*tmp_a;

	tmp_a = stack_a;
	initialize_instructions_struct(instructions);
	while (stack_b)
	{
		stack_a = ft_lstlast_new(tmp_a);
		instructions->stack_a_pos = 0;
		while (stack_a)
		{
			make_instructions_subfunction(stack_a, stack_b, instructions);
			stack_a = stack_a->prev;
			instructions->stack_a_pos++;
		}
		stack_b = stack_b->prev;
		instructions->stack_b_pos++;
	}
	if (instructions->lowest)
	{
		final_rotations(stack_a, instructions);
		pa(stack_a, stack_b);
	}
}

//you could throw it into two dif function depending if its plus or minus
void	make_instructions_subfunction(t_push *stack_a, t_push *stack_b, \
t_count *instructions)
{
	int	a_min_b;

	a_min_b = stack_a->num - stack_b->num;
	if (a_min_b < 0)
	{
		instructions->lowest = 1;
		if (absolute_value(a_min_b) < instructions->dif)
		{
			if (absolute_value(fastest_route(instructions->stack_a_pos \
			- instructions->stack_b_pos, stack_a) \
			< absolute_value(instructions->ra)))
				set_commands(stack_a, stack_b, instructions);
		}
	}
/*  	else if (a_min_b > 0)
	{
		if (a_min_b < instructions->dif && \
		absolute_value(fastest_route(instructions->stack_a_pos + 1 \
		- instructions->stack_b_pos, stack_a)\
		< absolute_value(instructions->ra)))
		{
			instructions->a_bigger = 1;
			set_commands(stack_a, stack_b, instructions);
		}
	} */
}

int	fastest_route(int rotations, t_push *stack_a)
{
	int	length;

	length = length_list(stack_a);
	if (rotations > length / 2 && rotations > 0)
		rotations = -length + rotations;
	if (rotations > length / 2 && rotations < 0)
		rotations = length + rotations;
	return (rotations);
}

void	set_commands(t_push *stack_a, t_push *stack_b, t_count *instructions)
{
	/* if (instructions->a_bigger == 1)
	{
		instructions->ra = fastest_route(instructions->stack_a_pos + 1 \
		- instructions->stack_b_pos, stack_a);
		instructions->a_bigger = 0;
	}
	else
	{ */
	instructions->ra = fastest_route(instructions->stack_a_pos \
	- instructions->stack_b_pos, stack_a);
	instructions->dif = stack_b->num - stack_a->num;
	instructions->rr = instructions->stack_b_pos;
}

t_push	*execute_instructions(t_push *stack_a, t_push *stack_b, \
t_count *instructions)
{
	while (instructions->rr > 0)
	{
		stack_a = r(stack_a);
		stack_b = r(stack_b);
		instructions->rr--;
	}
	while (instructions->rr < 0)
	{
		stack_a = rr(stack_a);
		stack_b = rr(stack_b);
		instructions->rr++;
	}
	while (instructions->ra > 0)
	{
		stack_a = r(stack_a);
		instructions->ra--;
	}
	while (instructions->ra < 0)
	{
		stack_a = rr(stack_a);
		instructions->ra++;
	}
	if (stack_b)
		return (pa(stack_a, stack_b));
	return (NULL);
}
