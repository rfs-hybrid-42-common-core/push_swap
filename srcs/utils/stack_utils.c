/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:33:55 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:40:14 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn void ft_stackadd_back(t_stack **stack, t_stack *new)
 * @brief Adds a new node to the end of the stack.
 * @details Appends a newly allocated node to the end of a non-circular linked 
 * list. If the stack is empty, it sets the new node as the head.
 * @param stack A double pointer to the top of the stack.
 * @param new   The new node to be added.
 */
void	ft_stackadd_back(t_stack **stack, t_stack *new)
{
	t_stack	*last;

	if (!stack || !new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = new;
}

/**
 * @fn void ft_stackclear(t_stack **stack)
 * @brief Frees all nodes in the stack.
 * @details Iterates through the circular linked list, safely freeing each node 
 * until the entire stack is cleared, then sets the head pointer to NULL.
 * @param stack A double pointer to the top of the stack.
 */
void	ft_stackclear(t_stack **stack)
{
	t_stack	*head;
	t_stack	*tmp;

	if (!stack || !*stack)
		return ;
	head = *stack;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		if (tmp == head || tmp == NULL)
			break ;
		*stack = tmp;
	}
	*stack = NULL;
}

/**
 * @fn int ft_stack_size(t_stack *stack)
 * @brief Calculates the number of elements in the stack.
 * @details Traverses the circular linked list to count the total number of 
 * nodes.
 * @param stack A pointer to the top of the stack.
 * @return      The total number of elements in the stack.
 */
int	ft_stack_size(t_stack *stack)
{
	t_stack	*head;
	int		size;

	size = 0;
	if (stack)
	{
		size++;
		head = stack;
		stack = stack->next;
		while (stack && stack != head)
		{
			size++;
			stack = stack->next;
		}
	}
	return (size);
}

/**
 * @fn int ft_stack_max_value(t_stack *stack)
 * @brief Finds the maximum value present in the stack.
 * @details Iterates through the circular linked list comparing values to find 
 * the highest integer.
 * @param stack A pointer to the top of the stack.
 * @return      The maximum integer value found.
 */
int	ft_stack_max_value(t_stack *stack)
{
	t_stack	*head;
	int		max;

	head = stack;
	max = stack->val;
	stack = stack->next;
	while (stack != head)
	{
		if (max < stack->val)
			max = stack->val;
		stack = stack->next;
	}
	return (max);
}

/**
 * @fn int ft_stack_min_value(t_stack *stack)
 * @brief Finds the minimum value present in the stack.
 * @details Iterates through the circular linked list comparing values to find 
 * the lowest integer.
 * @param stack A pointer to the top of the stack.
 * @return      The minimum integer value found.
 */
int	ft_stack_min_value(t_stack *stack)
{
	t_stack	*head;
	int		min;

	head = stack;
	min = stack->val;
	stack = stack->next;
	while (stack != head)
	{
		if (min > stack->val)
			min = stack->val;
		stack = stack->next;
	}
	return (min);
}
