/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:59:36 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:38:55 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static void run_operation(t_stack **s1, t_stack **s2, t_stack *s1_node)
 * @brief Detaches a node from one stack and attaches it to the top of another.
 * @details Handles the complex pointer updates required to safely move a node 
 * between two circular doubly linked lists. Handles edge cases for empty 
 * stacks or stacks with a single element.
 * @param s1      A double pointer to the source stack.
 * @param s2      A double pointer to the destination stack.
 * @param s1_node The specific node being moved from the source stack.
 */
static void	run_operation(t_stack **s1, t_stack **s2, t_stack *s1_node)
{
	t_stack	*tmp;

	if (s1_node == s1_node->next)
		*s1 = NULL;
	else
	{
		s1_node->prev->next = s1_node->next;
		s1_node->next->prev = s1_node->prev;
		*s1 = s1_node->next;
	}
	if (!*s2)
	{
		s1_node->next = s1_node;
		s1_node->prev = s1_node;
		*s2 = s1_node;
		return ;
	}
	tmp = (*s2)->prev;
	tmp->next = s1_node;
	s1_node->prev = tmp;
	s1_node->next = *s2;
	(*s2)->prev = s1_node;
	*s2 = s1_node;
}

/**
 * @fn static void pa(t_stack **a, t_stack **b, const bool check)
 * @brief Pushes the top element of stack b to stack a.
 * @details Executes the 'pa' instruction. If the check flag is false, it 
 * prints the instruction to standard output.
 * @param a     A double pointer to stack a (destination).
 * @param b     A double pointer to stack b (source).
 * @param check A boolean flag; true silences output (useful for the checker).
 */
static void	pa(t_stack **a, t_stack **b, const bool check)
{
	if (b && *b)
	{
		run_operation(b, a, *b);
		if (!check)
			ft_putendl_fd("pa", STDOUT_FILENO);
	}
}

/**
 * @fn static void pb(t_stack **a, t_stack **b, const bool check)
 * @brief Pushes the top element of stack a to stack b.
 * @details Executes the 'pb' instruction. If the check flag is false, it 
 * prints the instruction to standard output.
 * @param a     A double pointer to stack a (source).
 * @param b     A double pointer to stack b (destination).
 * @param check A boolean flag; true silences output.
 */
static void	pb(t_stack **a, t_stack **b, const bool check)
{
	if (a && *a)
	{
		run_operation(a, b, *a);
		if (!check)
			ft_putendl_fd("pb", STDOUT_FILENO);
	}
}

/**
 * @fn void	push(t_stack **a, t_stack **b, const t_stack_id id, 
 * const bool check)
 * @brief Dispatcher for the push operations.
 * @details Routes the execution to either 'pa' or 'pb' based on the provided 
 * stack identifier enum.
 * @param a     A double pointer to stack a.
 * @param b     A double pointer to stack b.
 * @param id    The identifier indicating the target stack (A or B).
 * @param check A boolean flag indicating whether to silence standard output.
 */
void	push(t_stack **a, t_stack **b, const t_stack_id id, const bool check)
{
	if (id == A)
		pa(a, b, check);
	else
		pb(a, b, check);
}
