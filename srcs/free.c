/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 18:00:40 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/09 19:52:06 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_free_info(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->info->n_philo)
		pthread_mutex_destroy(data->info->forks + i);
	pthread_mutex_destroy(&(data->info->speak));
	free(data->philo);
	free(data->info->forks);
	free(data->philo_threads);
	free(data->info);
	free(data);
}
