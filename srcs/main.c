/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:01:23 by magostin          #+#    #+#             */
/*   Updated: 2021/07/11 17:54:15 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	ft_arg_error(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Number of argument incorrect.\nMust be ");
		printf("./Philo-chan number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	while (++i < ac)
	{
		if (av[i] < 0 || !ft_strisint(av[i]))
		{
			printf("Arg %d is either negatif or not a valid int.\n", i);
			return (1);
		}
	}
	return (0);
}

void	*philochan(void *p)
{
	t_philo *philo;

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

void	ft_start_philo(t_data *data)
{
	int	i;
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->info->starting_time = time.tv_sec * 1000 + (time.tv_usec / 1000);
	i = -1;
	while (++i < data->info->n_philo)
	{
		pthread_create(&(data->info->philos[i]), NULL, philochan, data->philo + i);
		pthread_detach(data->info->philos[i]);
		usleep(10);
	}
}

void	ft_philo_loop(t_data *data, t_philo *philo)
{
	int	i;
	long	time;
	int	eat;
	int	end;

	end = 0;
	while (end == 0)
	{
		i = -1;
		eat = 0;
		while (++i < data->info->n_philo)
		{
			pthread_mutex_lock(data->info->access + i);
			time = ft_time(data->info);
			if (data->info->t_die + philo[i].last_eat < time)
			{
				ft_talk(philo + i, "died");
				end = 1;
			}
			if (data->info->max_eat != -1 && philo[i].eat >= data->info->max_eat)
				eat++;
			pthread_mutex_unlock(data->info->access + i);
			if (end)
				break ;
			usleep(100);
		}
		if (eat == data->info->n_philo)
			break ;
	}
	pthread_mutex_lock(&(data->info->mend));
	data->info->end = 1;
	pthread_mutex_unlock(&(data->info->mend));
	end = 1;
	while (end)
	{
		end = 0;
		i = -1;
		while (++i < data->info->n_philo)
		{
			pthread_mutex_lock(data->info->access + i);
			if (data->philo[i].alive == 1)
				end = 1;
			pthread_mutex_unlock(data->info->access + i);
		}
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->info = malloc(sizeof(t_info));
	if (!data->info || ft_arg_error(ac, av))
		return (1);
	ft_init_info(&data, ac, av);
	ft_init_philo(&data);
	ft_start_philo(data);
	ft_philo_loop(data, data->philo);
	ft_free_info(data);
	return (0);
}