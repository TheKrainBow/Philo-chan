/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 16:57:08 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/11 14:30:05 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

long	ft_time(t_info *info)
{
	struct timeval	current_time;
	long			dest;

	gettimeofday(&current_time, NULL);
	dest = (current_time.tv_sec * 1000 + (current_time.tv_usec / 1000)) - info->starting_time;
	return (dest);
}