/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:09:51 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:26:24 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn bool is_stack_sorted(t_stack *stack, const bool is_rev)
 * @brief Checks if the stack is fully sorted.
 * @details Iterates through the circular linked list to verify if the elements 
 * are in ascending order (or descending if is_rev is true).
 * @param stack  A pointer to the top of the stack.
 * @param is_rev A boolean indicating if the check should be for reverse 
 * (descending) order.
 * @return       true if the stack is sorted according to the criteria, false 
 * otherwise.
 */
bool	is_stack_sorted(t_stack *stack, const bool is_rev)
{
	t_stack	*head;

	if (!stack || stack->next == stack)
		return (true);
	head = stack;
	stack = stack->next;
	while (stack != head)
	{
		if ((!is_rev && stack->prev->val > stack->val)
			|| (is_rev && stack->prev->val < stack->val))
			return (false);
		stack = stack->next;
	}
	return (true);
}

/**
 * @fn bool is_stack_semi_sorted(t_stack *stack, const bool is_rev)
 * @brief Checks if the stack is sorted but simply shifted/rotated.
 * @details Determines if the stack can be considered sorted with just a series 
 * of rotate or reverse rotate operations.
 * @param stack  A pointer to the top of the stack.
 * @param is_rev A boolean indicating if the check is for reverse order.
 * @return       true if the stack is semi-sorted, false otherwise.
 */
bool	is_stack_semi_sorted(t_stack *stack, const bool is_rev)
{
	t_stack	*curr;

	if (!stack || stack->next == stack)
		return (true);
	curr = stack->next;
	while (curr != stack)
	{
		if (is_stack_sorted(curr, is_rev))
			return (true);
		curr = curr->next;
	}
	return (is_stack_sorted(stack, is_rev));
}

/**
 * @fn void reset_stack_indexes(t_stack **stack)
 * @brief Resets the indices and positional flags of the stack.
 * @details Iterates through the stack to update the current index (`idx`) of 
 * each node and determines if it sits in the top half of the stack (`top`).
 * @param stack A double pointer to the top of the stack.
 */
void	reset_stack_indexes(t_stack **stack)
{
	t_stack	*curr;
	int		size;
	int		i;

	if (!stack || !*stack)
		return ;
	size = ft_stack_size(*stack);
	curr = *stack;
	i = -1;
	while (++i < size)
	{
		curr->target = NULL;
		curr->idx = i;
		curr->top = (i < (size + 1) / 2);
		curr = curr->next;
	}
}
