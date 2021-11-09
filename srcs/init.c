/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 17:59:33 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/09 19:57:09 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_init_info(t_data *d, int ac, char **av)
{
	int	i;

	d->end = 0;
	d->info->n_philo = ft_atoi(av[1]);
	d->info->t_die = ft_atoi(av[2]);
	d->info->t_eat = ft_atoi(av[3]);
	d->info->t_sleep = ft_atoi(av[4]);
	d->info->forks = malloc(sizeof(pthread_mutex_t) * d->info->n_philo);
	d->philo_threads = malloc(sizeof(pthread_t) * d->info->n_philo);
	d->info->end = 0;
	i = -1;
	while (++i < d->info->n_philo)
		pthread_mutex_init(&(d->info->forks[i]), NULL);
	pthread_mutex_init(&(d->info->speak), NULL);
	pthread_mutex_init(&(d->info->mutex_end), NULL);
	if (ac == 6)
		d->info->max_eat = ft_atoi(av[5]);
	else
		d->info->max_eat = -1;
}

void	ft_init_philo(t_data *d)
{
	int		i;

	d->philo = malloc(sizeof(t_philo) * (d->info->n_philo + 1));
	i = -1;
	while (++i < d->info->n_philo)
	{
		d->philo[i].info = d->info;
		d->philo[i].id = i;
		d->philo[i].alive = 1;
		d->philo[i].eat = 0;
		d->philo[i].last_eat = 0;
		pthread_mutex_init(&(d->philo[i].access), NULL);
		if (d->philo[i].id > 0)
			d->philo[i].prev = d->philo[i].id - 1;
		else
			d->philo[i].prev = d->philo[i].info->n_philo - 1;
	}
}
