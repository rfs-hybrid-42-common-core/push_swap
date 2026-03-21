/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:13:27 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:04:50 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static void finish_rotation(t_stack **s1, t_stack **s2, t_stack *node, 
 * t_stack_id id)
 * @brief Completes any remaining isolated rotations for a single stack.
 * @details After synchronized rotations (rr/rrr) are exhausted, this finishes 
 * moving a specific node to the top using single stack rotations 
 * (ra/rb/rra/rrb).
 * @param s1   A double pointer to stack a.
 * @param s2   A double pointer to stack b.
 * @param node The specific node being rotated to the top.
 * @param id   The identifier indicating which stack to apply operations to.
 */
static void	finish_rotation(t_stack **s1, t_stack **s2, t_stack *node,
	t_stack_id id)
{
	while (node->cost > 0)
	{
		if (node->top)
			rotate(s1, s2, id, false);
		else
			reverse_rotate(s1, s2, id, false);
		node->cost--;
	}
}

/**
 * @fn void execute(t_stack **s1, t_stack **s2, t_stack *node)
 * @brief Executes the planned moves to push the cheapest node to stack a.
 * @details Performs synchronized rotations (rr/rrr) if both target nodes share 
 * a direction, resolves remaining individual rotations, and finally pushes the 
 * node.
 * @param s1   A double pointer to stack a.
 * @param s2   A double pointer to stack b.
 * @param node The node from stack b selected to be moved.
 */
void	execute(t_stack **s1, t_stack **s2, t_stack *node)
{
	if (node->top == node->target->top)
	{
		while (node->cost > 0 && node->target->cost > 0)
		{
			if (node->top)
				rotate(s1, s2, BOTH, false);
			else
				reverse_rotate(s1, s2, BOTH, false);
			node->cost--;
			node->target->cost--;
		}
	}
	finish_rotation(s1, s2, node, B);
	finish_rotation(s1, s2, node->target, A);
	push(s1, s2, A, false);
}
