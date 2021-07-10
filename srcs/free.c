/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 18:00:40 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/10 19:11:12 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_free_info(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->info->n_philo)
	{
		pthread_mutex_destroy(&(data->philo[i]->access));
		free(data->philo[i]);
	}
	free(data->philo);
	i = -1;
	while (++i < data->info->n_philo)
		pthread_mutex_destroy(&(data->info->forks[i]));
	pthread_mutex_destroy(&(data->info->speak));
	pthread_mutex_destroy(&(data->access_info));
	free(data->info);
}