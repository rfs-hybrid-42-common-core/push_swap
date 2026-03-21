/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:08:12 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:39:19 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static void run_operation(t_stack **stack)
 * @brief Core logic to swap the top two elements of a stack.
 * @details Re-links the pointers of the top two nodes in a circular doubly 
 * linked list so they trade places, updating the head pointer accordingly.
 * @param stack A double pointer to the top of the stack.
 */
static void	run_operation(t_stack **stack)
{
	t_stack	*node1;
	t_stack	*node2;

	node1 = *stack;
	node2 = node1->next;
	if (node2->next != node1)
	{
		node1->prev->next = node2;
		node2->next->prev = node1;
		node1->next = node2->next;
		node2->prev = node1->prev;
		node2->next = node1;
		node1->prev = node2;
	}
	*stack = node2;
}

/**
 * @fn static void sa(t_stack **a, const bool check)
 * @brief Swaps the top two elements of stack a.
 * @details Executes the 'sa' instruction. Does nothing if there is only one 
 * element or none. Prints "sa" if the check flag is false.
 * @param a     A double pointer to stack a.
 * @param check A boolean flag; true silences output.
 */
static void	sa(t_stack **a, const bool check)
{
	if (a && *a && (*a)->next && *a != (*a)->next)
	{
		run_operation(a);
		if (!check)
			ft_putendl_fd("sa", STDOUT_FILENO);
	}
}

/**
 * @fn static void sb(t_stack **b, const bool check)
 * @brief Swaps the top two elements of stack b.
 * @details Executes the 'sb' instruction. Does nothing if there is only one 
 * element or none. Prints "sb" if the check flag is false.
 * @param b     A double pointer to stack b.
 * @param check A boolean flag; true silences output.
 */
static void	sb(t_stack **b, const bool check)
{
	if (b && *b && (*b)->next && *b != (*b)->next)
	{
		run_operation(b);
		if (!check)
			ft_putendl_fd("sb", STDOUT_FILENO);
	}
}

/**
 * @fn static void ss(t_stack **a, t_stack **b, const bool check)
 * @brief Swaps the top two elements of both stacks simultaneously.
 * @details Executes the 'ss' instruction. Only performs the swap if both 
 * stacks have at least two elements. Prints "ss" if the check flag is false.
 * @param a     A double pointer to stack a.
 * @param b     A double pointer to stack b.
 * @param check A boolean flag; true silences output.
 */
static void	ss(t_stack **a, t_stack **b, const bool check)
{
	bool	swap_a;
	bool	swap_b;

	swap_a = (a && *a && (*a)->next && *a != (*a)->next);
	swap_b = (b && *b && (*b)->next && *b != (*b)->next);
	if (swap_a && swap_b)
	{
		run_operation(a);
		run_operation(b);
		if (!check)
			ft_putendl_fd("ss", STDOUT_FILENO);
	}
}

/**
 * @fn void swap(t_stack **a, t_stack **b, const t_stack_id id, 
 * const bool check)
 * @brief Dispatcher for the swap operations.
 * @details Routes the execution to 'sa', 'sb', or 'ss' based on the stack 
 * identifier.
 * @param a     A double pointer to stack a.
 * @param b     A double pointer to stack b.
 * @param id    The identifier indicating the target stack(s) (A, B, or BOTH).
 * @param check A boolean flag indicating whether to silence standard output.
 */
void	swap(t_stack **a, t_stack **b, const t_stack_id id, const bool check)
{
	if (id == A)
		sa(a, check);
	else if (id == B)
		sb(b, check);
	else
		ss(a, b, check);
}
