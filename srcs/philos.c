/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 16:57:08 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/09 20:03:47 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	*philochan(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		if (ft_task(philo, TAKE_FORK))
			break ;
		if (ft_task(philo, EAT))
		{
			ft_task(philo, LEAVE_FORK);
			break ;
		}
		if (ft_task(philo, LEAVE_FORK))
			break ;
		if (ft_task(philo, SLEEP))
			break ;
		if (ft_task(philo, THINK))
			break ;
	}
	pthread_mutex_lock(&philo->access);
	philo->alive = 0;
	pthread_mutex_unlock(&philo->access);
	return (NULL);
}

void ft_one_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(1000 * data->info->t_die);
	printf("%d 1 died\n", data->info->t_die);
	free(data->philo);
	free(data->info->forks);
	free(data->philo_threads);
	free(data->info);
	free(data);
	exit(1);
}

void	ft_start_philo(t_data *d)
{
	int				i;
	struct timeval	time;

	gettimeofday(&time, NULL);
	d->info->starting_time = time.tv_sec * 1000 + (time.tv_usec / 1000);
	if (d->info->n_philo == 1)
		ft_one_philo(d);
	i = -1;
	while (++i < d->info->n_philo)
	{
		pthread_create(&(d->philo_threads[i]), NULL, philochan, d->philo + i);
		usleep(100);
		pthread_detach(d->philo_threads[i]);
	}
}

int	ft_task(t_philo *philo, int task)
{
	if (task == LEAVE_FORK)
		ft_leave_fork(philo);
	pthread_mutex_lock(&(philo->info->mutex_end));
	if (philo->info->end)
	{
		pthread_mutex_unlock(&(philo->info->mutex_end));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->mutex_end));
	if (task == TAKE_FORK)
		ft_take_fork(philo);
	if (task == EAT)
		ft_eat(philo);
	if (task == SLEEP)
		ft_sleep(philo);
	if (task == THINK)
		ft_talk(philo, "is thinking", 1);
	return (0);
}
