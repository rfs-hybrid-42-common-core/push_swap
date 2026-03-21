/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:50:05 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:29:00 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static int non_lis_forward_offset(t_stack *stack)
 * @brief Calculates the steps to reach the next non-LIS node moving forward.
 * @details Traverses the stack using the `next` pointer, counting operations 
 * until a node not marked as part of the LIS is found.
 * @param stack A pointer to the top of the stack.
 * @return      The number of forward rotations required.
 */
static int	non_lis_forward_offset(t_stack *stack)
{
	t_stack	*curr;
	int		offset;

	curr = stack;
	offset = 0;
	while (curr->lis)
	{
		curr = curr->next;
		offset++;
	}
	return (offset);
}

/**
 * @fn static int non_lis_backward_offset(t_stack *stack)
 * @brief Calculates the steps to reach the next non-LIS node moving backward.
 * @details Traverses the stack using the `prev` pointer, counting operations 
 * until a node not marked as part of the LIS is found.
 * @param stack A pointer to the top of the stack.
 * @return      The number of reverse rotations required.
 */
static int	non_lis_backward_offset(t_stack *stack)
{
	t_stack	*curr;
	int		offset;

	curr = stack;
	offset = 0;
	while (curr->lis)
	{
		curr = curr->prev;
		offset++;
	}
	return (offset);
}

/**
 * @fn static void rotate_to_non_lis(t_stack **stack)
 * @brief Rotates the stack to the nearest non-LIS node.
 * @details Compares forward and backward offsets to determine the cheapest 
 * rotation direction, executing rotations until a non-LIS node is at the top.
 * @param stack A double pointer to the top of the stack.
 */
static void	rotate_to_non_lis(t_stack **stack)
{
	if (non_lis_forward_offset(*stack) <= non_lis_backward_offset(*stack))
		while ((*stack)->lis)
			rotate(stack, NULL, A, false);
	else
		while ((*stack)->lis)
			reverse_rotate(stack, NULL, A, false);
}

/**
 * @fn void lis_sort(t_stack **a, t_stack **b, const t_lis lis)
 * @brief Pushes non-LIS elements to stack B.
 * @details Iterates through stack A, leaving LIS elements intact while pushing 
 * all others to stack B. Includes a minor optimization to rotate elements in B 
 * based on a calculated pivot.
 * @param a   A double pointer to the top of stack a.
 * @param b   A double pointer to the top of stack b.
 * @param lis A struct containing the LIS array and size.
 */
void	lis_sort(t_stack **a, t_stack **b, const t_lis lis)
{
	int	pivot;

	pivot = ft_stack_size(*a) / 2 + ft_stack_size(*a) % 2;
	while (ft_stack_size(*a) != lis.size && ft_stack_size(*a) > 3
		&& !is_stack_semi_sorted(*a, false))
	{
		if (ft_stack_size(*b) < 2 && ft_stack_size(*a) > 3)
		{
			if ((*a)->lis)
				rotate_to_non_lis(a);
			push(a, b, B, false);
			if (ft_stack_size(*b) == 2
				&& (*b)->val < pivot && (*b)->next->val > pivot)
				swap(NULL, b, B, false);
		}
		else if (!((*a)->lis))
		{
			push(a, b, B, false);
			if ((*b)->val < pivot)
				rotate(NULL, b, B, false);
		}
		else
			rotate_to_non_lis(a);
	}
}
