/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:57:51 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:31:25 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static void update_stack_lis_numbers(t_stack **a, t_lis lis)
 * @brief Flags the LIS nodes within the linked list stack.
 * @details Traverses the stack backwards, matching node values against the LIS 
 * array to toggle the boolean `lis` flag for nodes belonging to the sequence.
 * @param a   A double pointer to the top of stack a.
 * @param lis A struct containing the LIS array and size.
 */
static void	update_stack_lis_numbers(t_stack **a, t_lis lis)
{
	t_stack	*curr;

	curr = (*a)->prev;
	while (lis.size)
	{
		if (curr->val == lis.arr[lis.size - 1])
		{
			curr->lis = true;
			lis.size--;
		}
		curr = curr->prev;
	}
}

/**
 * @fn static int *stack_to_array(t_stack *s, int max)
 * @brief Converts the linked list stack to an integer array.
 * @details Allocates and populates an array with the values from the stack, 
 * which is necessary to run the LIS dynamic programming algorithm.
 * @param s    A pointer to the top of the stack.
 * @param size The number of elements to copy.
 * @return     A dynamically allocated array of stack values, or NULL on 
 * failure.
 */
static int	*stack_to_array(t_stack *s, const int size)
{
	int	*arr;
	int	i;

	arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		arr[i] = s->val;
		s = s->next;
	}
	return (arr);
}

/**
 * @fn void sort_three(t_stack **stack)
 * @brief Hardcoded sorting logic for a stack of 3 elements.
 * @details Checks the specific permutations of a 3-element stack and executes 
 * the exact operations (1 or 2 max) needed to sort it efficiently.
 * @param stack A double pointer to the top of the stack.
 */
void	sort_three(t_stack **stack)
{
	if ((*stack)->prev == (*stack)->next)
	{
		swap(stack, NULL, A, false);
		return ;
	}
	if (!((*stack)->prev->val < (*stack)->val
			&& (*stack)->prev->val > (*stack)->next->val)
		&& !((*stack)->val < (*stack)->next->val
			&& (*stack)->val > (*stack)->prev->val))
		swap(stack, NULL, A, false);
	if (!is_stack_sorted(*stack, false))
	{
		if ((*stack)->val > (*stack)->next->val
			&& (*stack)->prev->val > (*stack)->next->val)
			rotate(stack, NULL, A, false);
		else
			reverse_rotate(stack, NULL, A, false);
	}
}

/**
 * @fn void push_swap(t_stack **a, t_stack **b, const int size)
 * @brief The main sorting algorithm dispatcher.
 * @details Handles edge cases (size <= 3), otherwise extracts the LIS, 
 * flags the appropriate nodes, and triggers the Turk sort to place the 
 * remaining elements efficiently.
 * @param a    A double pointer to the top of stack a.
 * @param b    A double pointer to the top of stack b.
 * @param size The total number of elements in stack a.
 */
void	push_swap(t_stack **a, t_stack **b, const int size)
{
	t_lis	lis;
	int		*a_array;

	if (size <= 3)
	{
		sort_three(a);
		return ;
	}
	if (is_stack_sorted(*a, true))
		swap(a, NULL, A, false);
	a_array = stack_to_array(*a, size);
	lis.arr = lis_sequence(a_array, size, &(lis.size));
	free(a_array);
	if (!lis.arr)
	{
		ft_stackclear(a);
		print_error();
	}
	update_stack_lis_numbers(a, lis);
	stack_sort(a, b, lis);
	free(lis.arr);
}
