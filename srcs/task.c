/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 16:53:36 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/11 18:13:15 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_talk(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->info->mend));
	if (!philo->info->end)
	{
		pthread_mutex_lock(&(philo->info->speak));
		printf("%ld %d %s\n", ft_time(philo->info), philo->id, str);
		pthread_mutex_unlock(&(philo->info->speak));
	}
	pthread_mutex_unlock(&(philo->info->mend));
}

void	ft_take_fork(t_philo *philo)
{
	if (!(philo->id % 2))
	{
		pthread_mutex_lock(&(philo->info->forks[philo->id]));
		ft_talk(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->info->forks[philo->prev]));
		ft_talk(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo->info->forks[philo->prev]));
		ft_talk(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->info->forks[philo->id]));
		ft_talk(philo, "has taken a fork");
	}
}

void	ft_leave_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->info->forks[philo->prev]));
	pthread_mutex_unlock(&(philo->info->forks[philo->id]));
}

void	ft_eat(t_philo *philo)
{
	long		time;

	ft_talk(philo, "is eating");
	time = ft_time(philo->info);
	pthread_mutex_lock(philo->info->access + philo->id);
	philo->last_eat = time;
	philo->eat++;
	pthread_mutex_unlock(philo->info->access + philo->id);
	usleep(1000 * philo->info->t_eat);
}

void	ft_sleep(t_philo *philo)
{
	ft_talk(philo, "is sleeping");
	usleep(1000 * philo->info->t_sleep);
}
