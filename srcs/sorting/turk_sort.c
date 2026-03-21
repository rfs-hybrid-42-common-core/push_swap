/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:07:35 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:27:47 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static int calculate_cost(const t_stack *node1, const t_stack *node2)
 * @brief Calculates the combined operation cost for two nodes.
 * @details Determines the total instructions needed to move both nodes to the 
 * top of their respective stacks. It subtracts operations if they share a 
 * rotation direction (rr/rrr).
 * @param node1 The node in stack b.
 * @param node2 The target node in stack a.
 * @return      The total computed integer cost.
 */
static int	calculate_cost(const t_stack *node1, const t_stack *node2)
{
	int	cost;

	cost = node1->cost;
	if (node2)
	{
		if (node1->top != node2->top)
			cost += node2->cost;
		else if (node1->cost < node2->cost)
			cost = node2->cost;
	}
	return (cost);
}

/**
 * @fn static t_stack *find_cheapest(t_stack **stack)
 * @brief Finds the node with the lowest movement cost.
 * @details Iterates through the stack to find the element that requires the 
 * fewest combined operations to be pushed back into its correct position in 
 * stack A.
 * @param stack A double pointer to the stack being evaluated (usually stack b).
 * @return      A pointer to the cheapest node.
 */
static t_stack	*find_cheapest(t_stack **stack)
{
	t_stack	*curr;
	t_stack	*cheapest;
	int		next_cost;
	int		prev_cost;

	cheapest = *stack;
	prev_cost = calculate_cost(*stack, (*stack)->target);
	curr = (*stack)->next;
	while (curr != *stack)
	{
		if (!(curr->lis))
		{
			next_cost = calculate_cost(curr, curr->target);
			if (next_cost < prev_cost)
			{
				cheapest = curr;
				prev_cost = next_cost;
			}
		}
		curr = curr->next;
	}
	return (cheapest);
}

/**
 * @fn static void find_target(t_stack **s1, t_stack *s2)
 * @brief Maps each node in stack b to its correct insertion target in stack a.
 * @details Determines where a node from stack b belongs in stack a by finding 
 * the closest larger number, or the minimum number if the current node is a 
 * new extreme.
 * @param s1 A double pointer to the source stack (stack b).
 * @param s2 A pointer to the destination stack (stack a).
 */
static void	find_target(t_stack **s1, t_stack *s2)
{
	t_stack	*curr;
	int		max;
	int		min;
	int		size;

	curr = *s1;
	max = ft_stack_max_value(s2);
	min = ft_stack_min_value(s2);
	size = ft_stack_size(*s1);
	while (size--)
	{
		if (curr->val > max || curr->val < min)
			while (s2->val != min)
				s2 = s2->next;
		else
			while (!(curr->val < s2->val && curr->val > s2->prev->val))
				s2 = s2->next;
		curr->target = s2;
		curr = curr->next;
	}
}

/**
 * @fn static void set_cost(t_stack **stack)
 * @brief Assigns the base movement cost to each node in a stack.
 * @details Calculates the absolute distance of a node from the top of the 
 * stack, determining if it's cheaper to rotate forward or backward.
 * @param stack A double pointer to the stack to process.
 */
static void	set_cost(t_stack **stack)
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
		if (curr->top)
			curr->cost = curr->idx;
		else
			curr->cost = size - curr->idx;
		curr = curr->next;
	}
}

/**
 * @fn void turk_sort(t_stack **a, t_stack **b)
 * @brief The core reintegration loop of the Turk algorithm.
 * @details Repeatedly updates indices and costs, finds targets, and pushes the 
 * absolute cheapest node from stack B back to stack A until B is empty.
 * @param a A double pointer to the top of stack a.
 * @param b A double pointer to the top of stack b.
 */
void	turk_sort(t_stack **a, t_stack **b)
{
	while (ft_stack_size(*b))
	{
		reset_stack_indexes(a);
		reset_stack_indexes(b);
		set_cost(a);
		set_cost(b);
		find_target(b, *a);
		execute(a, b, find_cheapest(b));
	}
}
