/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 16:53:36 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/09 20:10:48 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_talk(t_philo *philo, char *str, int unlock)
{/*
	if (philo->id == 0)
		printf(BRED);
	if (philo->id == 1)
		printf(BGREEN);
	if (philo->id == 2)
		printf(BBLUE);
	if (philo->id == 3)
		printf(BCYAN);
	if (philo->id == 4)
		printf(BYELLOW);
	*/pthread_mutex_lock(&(philo->info->mutex_end));
	if (!philo->info->end)
	{
		pthread_mutex_lock(&(philo->info->speak));
		printf("%ld %d %s\n", ft_time(philo->info), philo->id + 1, str);
		if (unlock)
			pthread_mutex_unlock(&(philo->info->speak));
	}
	pthread_mutex_unlock(&(philo->info->mutex_end));
	printf(WHITE);
}

void	ft_take_fork(t_philo *philo)
{
	if (!(philo->id % 2))
	{
		usleep(100);
		pthread_mutex_lock(&(philo->info->forks[philo->id]));
		ft_talk(philo, "has taken a fork", 1);
		pthread_mutex_lock(&(philo->info->forks[philo->prev]));
		ft_talk(philo, "has taken a fork", 1);
	}
	else
	{
		pthread_mutex_lock(&(philo->info->forks[philo->prev]));
		ft_talk(philo, "has taken a fork", 1);
		pthread_mutex_lock(&(philo->info->forks[philo->id]));
		ft_talk(philo, "has taken a fork", 1);
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

	ft_talk(philo, "is eating", 1);
	time = ft_time(philo->info);
	pthread_mutex_lock(&philo->access);
	philo->last_eat = time;
	philo->eat++;
	pthread_mutex_unlock(&philo->access);
	usleep(1000 * philo->info->t_eat);
}

void	ft_sleep(t_philo *philo)
{
	ft_talk(philo, "is sleeping", 1);
	usleep(1000 * philo->info->t_sleep);
}
