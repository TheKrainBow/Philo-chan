/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 17:59:33 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/10 19:07:39 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_init_info(t_data *data, int ac, char **av)
{
	int	i;

	data->info->n_philo = ft_atoi(av[1]);
	data->info->t_die = ft_atoi(av[2]);
	data->info->t_eat = ft_atoi(av[3]);
	data->info->t_sleep = ft_atoi(av[4]);
	data->info->forks = malloc(sizeof(pthread_mutex_t) * data->info->n_philo);
	data->info->end = 0;
	i = -1;
	while (++i < data->info->n_philo)
		pthread_mutex_init(&(data->info->forks[i]), NULL);
	pthread_mutex_init(&(data->info->speak), NULL);
	pthread_mutex_init(&(data->access_info), NULL);
	if (ac == 6)
		data->info->max_eat = ft_atoi(av[5]);
	else
		data->info->max_eat = -1;
	printf("We have %d philo that die in %dms, take %dms to eat and %dms to sleep\n", data->info->n_philo, data->info->t_die, data->info->t_eat, data->info->t_sleep);
}

void	ft_init_philo(t_data *data)
{
	int		i;

	data->philo = malloc(sizeof(t_philo *) * (data->info->n_philo + 1));
	i = -1;
	while (++i < data->info->n_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		data->philo[i]->info = data->info;
		data->philo[i]->id = i;
		pthread_mutex_init(&(data->philo[i]->access), NULL);
		data->philo[i]->alive = 1;
		if (data->philo[i]->id > 0)
			data->philo[i]->prev = data->philo[i]->id - 1;
		else
			data->philo[i]->prev = data->philo[i]->info->n_philo - 1;
	}
}