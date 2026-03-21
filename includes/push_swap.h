/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:40:47 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 16:55:27 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

/* --------------------------- External Libraries --------------------------- */
# include "libft.h"

/* --------------------------- Internal Libraries --------------------------- */
# include <stdbool.h>
# include <limits.h>

/* ========================================================================== */
/* DATA STRUCTURES                                                            */
/* ========================================================================== */

/**
 * @enum e_stack_id
 * @brief Identifiers for the stacks.
 * @details Replaces magic numbers to cleanly specify which stack(s) an 
 * operation should target (A, B, or both simultaneously).
 * @var A    Targets stack A.
 * @var B    Targets stack B.
 * @var BOTH Targets both stacks simultaneously (e.g., for ss, rr, rrr).
 */
typedef enum e_stack_id
{
	A = 0,
	B = 1,
	BOTH = 2
}	t_stack_id;

/**
 * @struct s_stack
 * @brief Node structure for the circular doubly linked list stack.
 * @details Holds the core data, positional metadata, rotation costs, 
 * and relational pointers heavily utilized by the LIS and Turk algorithms.
 * @var val    The integer value (or normalized index) of the node.
 * @var idx    The current positional index of the node within the stack.
 * @var cost   The calculated operation cost to move this node to the top.
 * @var top    Boolean flag indicating if the node is in the top half of the 
 * stack.
 * @var lis    Boolean flag indicating if the node is part of the LIS.
 * @var target Pointer to the node's designated target in the opposite stack.
 * @var prev   Pointer to the previous node in the circular list.
 * @var next   Pointer to the next node in the circular list.
 */
typedef struct s_stack
{
	int				val;
	int				idx;
	int				cost;
	bool			top;
	bool			lis;
	struct s_stack	*target;
	struct s_stack	*prev;
	struct s_stack	*next;
}	t_stack;

/**
 * @struct s_lis
 * @brief Container for the Longest Increasing Subsequence data.
 * @details Groups the dynamically allocated array of LIS values with its size 
 * so it can be safely and easily passed around during the initial sorting 
 * phase.
 * @var arr  Pointer to the dynamically allocated array containing LIS values.
 * @var size The total number of elements in the LIS array.
 */
typedef struct s_lis
{
	int		*arr;
	int		size;
}	t_lis;

/* ========================================================================== */
/* FUNCTIONS                                                                  */
/* ========================================================================== */

/* ------------------------ Parsing & Initialization ------------------------ */
void	parser(t_stack **stack, int argc, char **argv);
t_stack	*get_stack(int argc, char **argv);
bool	validation(char **words);

/* ------------------------------- Operations ------------------------------- */
void	execute(t_stack **s1, t_stack **s2, t_stack *node);
void	push(t_stack **a, t_stack **b, const t_stack_id id, const bool check);
void	swap(t_stack **a, t_stack **b, const t_stack_id id, const bool check);
void	rotate(t_stack **a, t_stack **b, const t_stack_id id, const bool check);
void	reverse_rotate(t_stack **a, t_stack **b, const t_stack_id id,
			const bool check);

/* --------------------------- Sorting Algorithms --------------------------- */
void	push_swap(t_stack **a, t_stack **b, const int size);
void	sort_three(t_stack **stack);
void	stack_sort(t_stack **a, t_stack **b, const t_lis lis);
int		*lis_sequence(int *arr, int size, int *lis_len);
void	lis_sort(t_stack **a, t_stack **b, const t_lis lis);
void	turk_sort(t_stack **a, t_stack **b);

/* ------------------------------- Utilities -------------------------------- */
void	print_error(void);
long	ft_atol(const char *nptr);
void	ft_stackadd_back(t_stack **stack, t_stack *new);
void	ft_stackclear(t_stack **stack);
int		ft_stack_size(t_stack *stack);
int		ft_stack_max_value(t_stack *stack);
int		ft_stack_min_value(t_stack *stack);
bool	is_stack_sorted(t_stack *stack, const bool is_rev);
bool	is_stack_semi_sorted(t_stack *stack, const bool is_rev);
void	reset_stack_indexes(t_stack **stack);

#endif
