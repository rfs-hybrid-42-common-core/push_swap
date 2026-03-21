/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:12:49 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:40:25 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static void rra(t_stack **a, const bool check)
 * @brief Shifts down all elements of stack a by 1.
 * @details Executes the 'rra' instruction by moving the head pointer of the 
 * circular linked list backward by one node. The last element becomes the 
 * first.
 * @param a     A double pointer to stack a.
 * @param check A boolean flag; true silences output.
 */
static void	rra(t_stack **a, const bool check)
{
	if (a && *a && *a != (*a)->prev)
	{
		*a = (*a)->prev;
		if (!check)
			ft_putendl_fd("rra", STDOUT_FILENO);
	}
}

/**
 * @fn static void rrb(t_stack **b, const bool check)
 * @brief Shifts down all elements of stack b by 1.
 * @details Executes the 'rrb' instruction by moving the head pointer backward 
 * by one node. The last element becomes the first.
 * @param b     A double pointer to stack b.
 * @param check A boolean flag; true silences output.
 */
static void	rrb(t_stack **b, const bool check)
{
	if (b && *b && *b != (*b)->prev)
	{
		*b = (*b)->prev;
		if (!check)
			ft_putendl_fd("rrb", STDOUT_FILENO);
	}
}

/**
 * @fn static void rrr(t_stack **a, t_stack **b, const bool check)
 * @brief Shifts down all elements of both stacks by 1 simultaneously.
 * @details Executes the 'rrr' instruction. Only performs the reverse rotations 
 * if both stacks have at least two elements.
 * @param a     A double pointer to stack a.
 * @param b     A double pointer to stack b.
 * @param check A boolean flag; true silences output.
 */
static void	rrr(t_stack **a, t_stack **b, const bool check)
{
	bool	rotate_a;
	bool	rotate_b;

	rotate_a = (a && *a && *a != (*a)->prev);
	rotate_b = (b && *b && *b != (*b)->prev);
	if (rotate_a && rotate_b)
	{
		*a = (*a)->prev;
		*b = (*b)->prev;
		if (!check)
			ft_putendl_fd("rrr", STDOUT_FILENO);
	}
}

/**
 * @fn void	reverse_rotate(t_stack **a, t_stack **b, const t_stack_id id, 
 * const bool check)
 * @brief Dispatcher for the reverse rotate operations.
 * @details Routes the execution to 'rra', 'rrb', or 'rrr' based on the stack 
 * identifier.
 * @param a     A double pointer to stack a.
 * @param b     A double pointer to stack b.
 * @param id    The identifier indicating the target stack(s) (A, B, or BOTH).
 * @param check A boolean flag indicating whether to silence standard output.
 */
void	reverse_rotate(t_stack **a, t_stack **b, const t_stack_id id,
	const bool check)
{
	if (id == A)
		rra(a, check);
	else if (id == B)
		rrb(b, check);
	else
		rrr(a, b, check);
}
