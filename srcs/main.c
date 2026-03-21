/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:40:15 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 17:17:19 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn int main(int argc, char **argv)
 * @brief Entry point for the push_swap program.
 * @details Initializes stacks, parses input, and triggers the sorting 
 * algorithm if the stack is not already sorted. Cleans up memory before 
 * exiting.
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return     EXIT_SUCCESS upon successful completion or if no parameters 
 * are specified.
 */
int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (EXIT_SUCCESS);
	parser(&a, argc, argv);
	if (!is_stack_sorted(a, false))
		push_swap(&a, &b, ft_stack_size(a));
	ft_stackclear(&a);
	ft_stackclear(&b);
	return (EXIT_SUCCESS);
}
