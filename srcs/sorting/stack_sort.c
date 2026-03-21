/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:15:40 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:29:10 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static void rotate_to_min_val(t_stack **stack)
 * @brief Finalizes the sorting by rotating the absolute minimum value to the 
 * top.
 * @details Once all elements are sorted relatively, this calculates the 
 * cheapest direction (ra or rra) to bring the smallest integer to the top of 
 * the stack.
 * @param stack A double pointer to the top of the stack.
 */
static void	rotate_to_min_val(t_stack **stack)
{
	t_stack	*curr;
	int		min;
	int		size;
	int		rotations;

	reset_stack_indexes(stack);
	curr = *stack;
	min = ft_stack_min_value(*stack);
	while (curr->val != min)
		curr = curr->next;
	size = ft_stack_size(*stack);
	rotations = curr->idx;
	if (rotations < (size + 1) / 2)
	{
		while (rotations--)
			rotate(stack, NULL, A, false);
	}
	else
	{
		rotations = size - rotations;
		while (rotations--)
			reverse_rotate(stack, NULL, A, false);
	}
}

/**
 * @fn void stack_sort(t_stack **a, t_stack **b, const t_lis lis)
 * @brief Coordinates the multi-phase LIS and Turk sorting algorithms.
 * @details Executes the LIS separation phase, handles the 3-element edge case, 
 * runs the main Turk sort to reintegrate elements, and finalizes the rotation.
 * @param a   A double pointer to the top of stack a.
 * @param b   A double pointer to the top of stack b.
 * @param lis A struct containing the LIS array and size.
 */
void	stack_sort(t_stack **a, t_stack **b, const t_lis lis)
{
	lis_sort(a, b, lis);
	if (ft_stack_size(*a) == 3 && !is_stack_semi_sorted(*a, false))
		swap(a, NULL, A, false);
	turk_sort(a, b);
	if (!is_stack_sorted(*a, false))
		rotate_to_min_val(a);
}
