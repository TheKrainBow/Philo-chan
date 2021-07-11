/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 16:57:08 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/11 18:13:18 by mdelwaul         ###   ########.fr       */
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
	pthread_mutex_lock(philo->info->access + philo->id);
	philo->alive = 0;
	pthread_mutex_unlock(philo->info->access + philo->id);
	return (NULL);
}

void	ft_start_philo(t_data *d)
{
	int				i;
	struct timeval	time;

	gettimeofday(&time, NULL);
	d->info->starting_time = time.tv_sec * 1000 + (time.tv_usec / 1000);
	i = -1;
	while (++i < d->info->n_philo)
	{
		pthread_create(&(d->info->philos[i]), NULL, philochan, d->philo + i);
		pthread_detach(d->info->philos[i]);
		usleep(10);
	}
}

int	ft_task(t_philo *philo, int task)
{
	if (task == LEAVE_FORK)
		ft_leave_fork(philo);
	pthread_mutex_lock(&(philo->info->mend));
	if (philo->info->end)
	{
		pthread_mutex_unlock(&(philo->info->mend));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->mend));
	if (task == TAKE_FORK)
		ft_take_fork(philo);
	if (task == EAT)
		ft_eat(philo);
	if (task == SLEEP)
		ft_sleep(philo);
	if (task == THINK)
		ft_talk(philo, "is thinking");
	return (0);
}
