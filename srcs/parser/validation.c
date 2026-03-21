/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:29:54 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 15:47:46 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static bool is_valid_format(char *str)
 * @brief Validates the format of a numeric string.
 * @details Checks if a string consists only of digits, optionally preceded by 
 * a single sign ('+' or '-'). Also ensures the string length doesn't blatantly 
 * exceed integer bounds.
 * @param str The string to validate.
 * @return    true if the format is strictly numeric, false otherwise.
 */
static bool	is_valid_format(char *str)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	if (str[j] == '-' || str[j] == '+')
		j++;
	if (!str[j])
		return (false);
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (false);
		j++;
		len++;
	}
	return (len <= 10);
}

/**
 * @fn static bool check_format_and_limits(char **words)
 * @brief Validates format and integer limits for an array of strings.
 * @details Iterates through all strings, ensuring they pass format checks and 
 * fit within the strict bounds of a 32-bit signed integer (INT_MIN to INT_MAX).
 * @param words The null-terminated array of strings.
 * @return      true if all strings are valid integers within limits, false 
 * otherwise.
 */
static bool	check_format_and_limits(char **words)
{
	int		i;
	long	num;

	i = -1;
	while (words[++i])
	{
		if (!is_valid_format(words[i]))
			return (false);
		num = ft_atol(words[i]);
		if (num > INT_MAX || num < INT_MIN)
			return (false);
	}
	return (true);
}

/**
 * @fn static bool has_duplicate_values(long *arr, int len)
 * @brief Checks a numeric array for duplicate values.
 * @details Iterates through an array of long integers using nested loops to 
 * cross-reference each element against all subsequent elements, identifying 
 * if any value appears more than once.
 * @param arr The array of long integers to verify.
 * @param len The number of elements in the array.
 * @return    true if a duplicate is found, false otherwise.
 */
static bool	has_duplicate_values(long *arr, int len)
{
	int	i;
	int	j;

	i = -1;
	while (++i < len)
	{
		j = i;
		while (++j < len)
			if (arr[i] == arr[j])
				return (true);
	}
	return (false);
}

/**
 * @fn static bool check_duplicates(char **words)
 * @brief Checks for duplicate numbers within the input strings.
 * @details Allocates an array of long integers, populates it by converting 
 * the input strings using ft_atol, and leverages has_duplicate_values to 
 * ensure all numbers are unique. Safely frees the allocated memory before 
 * returning.
 * @param words The null-terminated array of strings representing the numbers.
 * @return      true if no duplicates are found, false if a duplicate exists or 
 * if memory allocation fails.
 */
static bool	check_duplicates(char **words)
{
	bool	has_dup;
	long	*arr;
	int		len;
	int		i;

	len = -1;
	while (words[++len])
		;
	arr = malloc(sizeof(long) * len);
	if (!arr)
		return (false);
	i = -1;
	while (++i < len)
		arr[i] = ft_atol(words[i]);
	has_dup = has_duplicate_values(arr, len);
	free(arr);
	return (!has_dup);
}

/**
 * @fn bool validation(char **words)
 * @brief Performs all necessary validation on the input strings.
 * @details Acts as a wrapper to execute both format/limit checks and duplicate 
 * checks.
 * @param words The null-terminated array of strings.
 * @return      true if the input passes all validation checks, false otherwise.
 */
bool	validation(char **words)
{
	if (!check_format_and_limits(words) || !check_duplicates(words))
		return (false);
	return (true);
}
