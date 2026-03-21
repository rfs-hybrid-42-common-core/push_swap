/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_sequence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:32 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/21 15:51:48 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @fn static void lis_init(int *lis, int *pred, int size)
 * @brief Initializes the arrays used for LIS calculation.
 * @details Sets every element in the LIS lengths array to 1 and the 
 * predecessor array to -1, establishing the baseline for dynamic programming.
 * @param lis  The array storing the length of the LIS up to each index.
 * @param pred The array storing the predecessor indices to reconstruct the 
 * sequence.
 * @param size The total number of elements in the arrays.
 */
static void	lis_init(int *lis, int *pred, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		lis[i] = 1;
		pred[i] = -1;
	}
}

/**
 * @fn static void calculate_lis(int *lis, int *pred, int *arr, int size)
 * @brief Computes the Longest Increasing Subsequence lengths.
 * @details Uses a dynamic programming approach (O(N^2)) to calculate the 
 * length of the LIS ending at each index and records the predecessor for 
 * sequence pathing.
 * @param lis  The array to store LIS lengths.
 * @param pred The array to store predecessor indices.
 * @param arr  The original array of values.
 * @param size The size of the arrays.
 */
static void	calculate_lis(int *lis, int *pred, int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (++i < size)
	{
		j = -1;
		while (++j < i)
		{
			if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
			{
				lis[i] = lis[j] + 1;
				pred[i] = j;
			}
		}
	}
}

/**
 * @fn static void get_lis_max(int *lis, int size, int *lis_len, int *max)
 * @brief Finds the maximum LIS length and its ending index.
 * @details Iterates through the computed LIS array to locate the end of the 
 * longest sequence, passing the results back via pointers.
 * @param lis     The populated LIS length array.
 * @param size    The size of the array.
 * @param lis_len Pointer to store the maximum sequence length found.
 * @param max     Pointer to store the index where the maximum sequence ends.
 */
static void	get_lis_max(int *lis, int size, int *lis_len, int *max)
{
	int	i;

	i = 0;
	*lis_len = lis[i];
	*max = i;
	while (++i < size)
	{
		if (lis[i] > *lis_len)
		{
			*lis_len = lis[i];
			*max = i;
		}
	}
}

/**
 * @fn static int *generate_lis(int *pred, int *arr, int lis_len, int max)
 * @brief Reconstructs the actual Longest Increasing Subsequence.
 * @details Backtracks through the predecessor array starting from the maximum 
 * index to build a dynamically allocated array containing the LIS values.
 * @param pred    The predecessor indices array.
 * @param arr     The original array of values.
 * @param lis_len The length of the target sequence.
 * @param max     The starting index for the backtrack.
 * @return        A dynamically allocated array containing the LIS values.
 */
static int	*generate_lis(int *pred, int *arr, int lis_len, int max)
{
	int	*seq;
	int	i;

	seq = (int *)malloc(sizeof(int) * lis_len);
	if (!seq)
		return (NULL);
	i = max;
	while (i >= 0)
	{
		seq[--lis_len] = arr[i];
		i = pred[i];
	}
	return (seq);
}

/**
 * @fn int *lis_sequence(int *arr, int size, int *lis_len)
 * @brief Orchestrates the generation of the LIS.
 * @details Allocates temporary arrays, triggers the LIS calculation steps, 
 * builds the final sequence array, and cleans up the temporary memory.
 * @param arr     The input array of integers.
 * @param size    The size of the input array.
 * @param lis_len Pointer to store the final length of the returned sequence.
 * @return        A dynamically allocated array of the LIS values, or NULL on 
 * failure.
 */
int	*lis_sequence(int *arr, int size, int *lis_len)
{
	int	*lis;
	int	*pred;
	int	*seq;
	int	max;

	if (!arr)
		return (NULL);
	lis = (int *)malloc(sizeof(int) * size);
	pred = (int *)malloc(sizeof(int) * size);
	if (!lis || !pred)
	{
		free(lis);
		free(pred);
		return (NULL);
	}
	lis_init(lis, pred, size);
	calculate_lis(lis, pred, arr, size);
	get_lis_max(lis, size, lis_len, &max);
	seq = generate_lis(pred, arr, *lis_len, max);
	free(lis);
	free(pred);
	return (seq);
}
