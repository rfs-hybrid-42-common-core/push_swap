/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:19:28 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 17:17:29 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

/**
 * @fn static void invalid_command(t_stack **a, t_stack **b, char *cmd)
 * @brief Handles invalid instruction inputs.
 * @details Safely clears both stacks and frees the offending command string 
 * before calling print_error() to display "Error\n" and terminate the program.
 * @param a   A double pointer to stack a.
 * @param b   A double pointer to stack b.
 * @param cmd The invalid command string read from standard input.
 */
static void	invalid_command(t_stack **a, t_stack **b, char *cmd)
{
	ft_stackclear(a);
	ft_stackclear(b);
	free(cmd);
	print_error();
}

/**
 * @fn static void run_operation(t_stack **a, t_stack **b, char *cmd)
 * @brief Parses and executes a single instruction string.
 * @details Compares the input string against all valid push_swap operations 
 * and executes the corresponding function with the `check` flag set to true 
 * (silencing standard output). If no match is found, triggers invalid_command.
 * @param a   A double pointer to stack a.
 * @param b   A double pointer to stack b.
 * @param cmd The instruction string (including newline) to execute.
 */
static void	run_operation(t_stack **a, t_stack **b, char *cmd)
{
	if (!ft_strcmp(cmd, "sa\n"))
		swap(a, b, A, true);
	else if (!ft_strcmp(cmd, "sb\n"))
		swap(a, b, B, true);
	else if (!ft_strcmp(cmd, "ss\n"))
		swap(a, b, BOTH, true);
	else if (!ft_strcmp(cmd, "pa\n"))
		push(a, b, A, true);
	else if (!ft_strcmp(cmd, "pb\n"))
		push(a, b, B, true);
	else if (!ft_strcmp(cmd, "ra\n"))
		rotate(a, b, A, true);
	else if (!ft_strcmp(cmd, "rb\n"))
		rotate(a, b, B, true);
	else if (!ft_strcmp(cmd, "rr\n"))
		rotate(a, b, BOTH, true);
	else if (!ft_strcmp(cmd, "rra\n"))
		reverse_rotate(a, b, A, true);
	else if (!ft_strcmp(cmd, "rrb\n"))
		reverse_rotate(a, b, B, true);
	else if (!ft_strcmp(cmd, "rrr\n"))
		reverse_rotate(a, b, BOTH, true);
	else
		invalid_command(a, b, cmd);
}

/**
 * @fn int main(int argc, char **argv)
 * @brief Entry point for the checker bonus program.
 * @details Parses the initial arguments to populate stack A, reads instructions 
 * continuously from standard input using get_next_line, and applies them. 
 * Finally, evaluates if stack A is fully sorted while stack B is empty, 
 * outputting "OK" or "KO" accordingly.
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return     EXIT_SUCCESS upon successful completion or if no parameters 
 * are specified.
 */
int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	char	*line;

	a = NULL;
	b = NULL;
	line = NULL;
	if (argc < 2)
		return (EXIT_SUCCESS);
	parser(&a, argc, argv);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		run_operation(&a, &b, line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (is_stack_sorted(a, false) && !ft_stack_size(b))
		ft_putendl_fd("OK", STDOUT_FILENO);
	else
		ft_putendl_fd("KO", STDOUT_FILENO);
	ft_stackclear(&a);
	ft_stackclear(&b);
	return (EXIT_SUCCESS);
}
