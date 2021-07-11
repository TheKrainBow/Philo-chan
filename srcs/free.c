/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 18:00:40 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/11 18:09:20 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_free_info(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->info->n_philo)
	{
		pthread_mutex_destroy(data->info->access + i);
		pthread_mutex_destroy(data->info->forks + i);
	}
	pthread_mutex_destroy(&(data->info->speak));
	free(data->philo);
	free(data->info->access);
	free(data->info->forks);
	free(data->info->philos);
	free(data->info);
	free(data);
}
