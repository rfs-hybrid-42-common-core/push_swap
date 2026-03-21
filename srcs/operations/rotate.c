/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:59:31 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:39:12 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static void ra(t_stack **a, const bool check)
 * @brief Shifts up all elements of stack a by 1.
 * @details Executes the 'ra' instruction by simply moving the head pointer of 
 * the circular linked list forward by one node. The first element becomes the 
 * last.
 * @param a     A double pointer to stack a.
 * @param check A boolean flag; true silences output.
 */
static void	ra(t_stack **a, const bool check)
{
	if (a && *a && *a != (*a)->next)
	{
		*a = (*a)->next;
		if (!check)
			ft_putendl_fd("ra", STDOUT_FILENO);
	}
}

/**
 * @fn static void rb(t_stack **b, const bool check)
 * @brief Shifts up all elements of stack b by 1.
 * @details Executes the 'rb' instruction by moving the head pointer forward 
 * by one node. The first element becomes the last.
 * @param b     A double pointer to stack b.
 * @param check A boolean flag; true silences output.
 */
static void	rb(t_stack **b, const bool check)
{
	if (b && *b && *b != (*b)->next)
	{
		*b = (*b)->next;
		if (!check)
			ft_putendl_fd("rb", STDOUT_FILENO);
	}
}

/**
 * @fn static void rr(t_stack **a, t_stack **b, const bool check)
 * @brief Shifts up all elements of both stacks by 1 simultaneously.
 * @details Executes the 'rr' instruction. Only performs the rotations if both 
 * stacks have at least two elements.
 * @param a     A double pointer to stack a.
 * @param b     A double pointer to stack b.
 * @param check A boolean flag; true silences output.
 */
static void	rr(t_stack **a, t_stack **b, const bool check)
{
	bool	rotate_a;
	bool	rotate_b;

	rotate_a = (a && *a && *a != (*a)->next);
	rotate_b = (b && *b && *b != (*b)->next);
	if (rotate_a && rotate_b)
	{
		*a = (*a)->next;
		*b = (*b)->next;
		if (!check)
			ft_putendl_fd("rr", STDOUT_FILENO);
	}
}

/**
 * @fn void rotate(t_stack **a, t_stack **b, const t_stack_id id, 
 * const bool check)
 * @brief Dispatcher for the rotate operations.
 * @details Routes the execution to 'ra', 'rb', or 'rr' based on the stack 
 * identifier.
 * @param a     A double pointer to stack a.
 * @param b     A double pointer to stack b.
 * @param id    The identifier indicating the target stack(s) (A, B, or BOTH).
 * @param check A boolean flag indicating whether to silence standard output.
 */
void	rotate(t_stack **a, t_stack **b, const t_stack_id id, const bool check)
{
	if (id == A)
		ra(a, check);
	else if (id == B)
		rb(b, check);
	else
		rr(a, b, check);
}
