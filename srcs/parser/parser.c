/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:38:45 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 15:36:45 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static void find_final_index(t_stack **stack)
 * @brief Calculates the sorted target index for each node.
 * @details Compares each node's value against all others to determine its 
 * final position if the stack were sorted, storing this in the `idx` variable.
 * @param stack A double pointer to the top of the stack.
 */
static void	find_final_index(t_stack **stack)
{
	t_stack	*curr;
	t_stack	*cmp;
	int		count;

	curr = *stack;
	while (curr)
	{
		count = 0;
		cmp = *stack;
		while (cmp)
		{
			if (curr->val > cmp->val)
				count++;
			cmp = cmp->next;
		}
		curr->idx = count;
		curr = curr->next;
	}
}

/**
 * @fn static void normalize_values(t_stack **stack)
 * @brief Replaces actual stack values with their sorted indices.
 * @details Overwrites the original `val` data in each node with its 
 * pre-calculated `idx`. This simplifies algorithm logic by normalizing all 
 * data to a 0 to N-1 range.
 * @param stack A double pointer to the top of the stack.
 */
static void	normalize_values(t_stack **stack)
{
	t_stack	*node;

	node = *stack;
	while (node)
	{
		node->val = node->idx;
		node = node->next;
	}
}

/**
 * @fn static void set_stack_prev_nodes(t_stack **stack)
 * @brief Converts a standard linked list into a circular doubly linked list.
 * @details Iterates through the list to link `prev` pointers and connects the 
 * tail node back to the head node.
 * @param stack A double pointer to the top of the stack.
 */
static void	set_stack_prev_nodes(t_stack **stack)
{
	t_stack	*curr;

	if (!stack || !*stack)
		return ;
	curr = *stack;
	while (curr->next)
	{
		curr->next->prev = curr;
		curr = curr->next;
	}
	curr->next = *stack;
	(*stack)->prev = curr;
}

/**
 * @fn void parser(t_stack **stack, int argc, char **argv)
 * @brief Orchestrates the input parsing and stack formatting.
 * @details Fetches the raw stack, determines final indices, normalizes the 
 * node values, and wires the list into a circular doubly linked format.
 * @param stack A double pointer to the top of the stack.
 * @param argc  The argument count.
 * @param argv  The argument vector.
 */
void	parser(t_stack **stack, int argc, char **argv)
{
	*stack = get_stack(argc, argv);
	if (!*stack)
		return ;
	find_final_index(stack);
	normalize_values(stack);
	set_stack_prev_nodes(stack);
}
