/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:09:49 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 15:22:58 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn void print_error(void)
 * @brief Prints an error message and exits the program.
 * @details Outputs "Error\n" to the standard error file descriptor 
 * (STDERR_FILENO) and terminates the program with a failure status.
 */
void	print_error(void)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/**
 * @fn long ft_atol(const char *nptr)
 * @brief Converts a string to a long integer.
 * @details Parses a string, skipping whitespaces and handling signs, to 
 * convert it into a long integer. Includes basic overflow protection during 
 * parsing.
 * @param nptr The string to convert.
 * @return     The converted long integer.
 */
long	ft_atol(const char *nptr)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign *= -1;
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + (*nptr++ - '0');
		if (res > (long)INT_MAX + 1)
			break ;
	}
	return (res * sign);
}
