/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:01:23 by magostin          #+#    #+#             */
/*   Updated: 2021/11/05 22:46:35 by magostin         ###   ########.fr       */
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

void	ft_wait_death(t_data *d)
{
	int	i;
	int	end;

	pthread_mutex_lock(&(d->info->mend));
	d->info->end = 1;
	pthread_mutex_unlock(&(d->info->mend));
	end = 1;
	while (end)
	{
		end = 0;
		i = -1;
		while (++i < d->info->n_philo)
		{
			pthread_mutex_lock(d->info->access + i);
			if (d->philo[i].alive == 1)
				end = 1;
			pthread_mutex_unlock(d->info->access + i);
		}
	}
}

void	ft_philo_loop(t_data *d, t_philo *philo)
{
	int		i;
	int		eat;

	while (d->end == 0)
	{
		i = -1;
		eat = 0;
		while (++i < d->info->n_philo)
		{
			pthread_mutex_lock(d->info->access + i);
			if (d->info->t_die + philo[i].last_eat < ft_time(d->info))
			{
				ft_talk(philo + i, "died");
				d->end = 1;
				d->info->end = 1;
			}
			if (d->info->max_eat != -1 && philo[i].eat >= d->info->max_eat)
				eat++;
			pthread_mutex_unlock(d->info->access + i);
			if (d->end)
				break ;
			usleep(100);
		}
		if (eat == d->info->n_philo)
			break ;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->info = malloc(sizeof(t_info));
	if (!data->info || ft_arg_error(ac, av))
	{
		free(data->info);
		free(data);
		return (1);
	}
	ft_init_info(&data, ac, av);
	ft_init_philo(&data);
	ft_start_philo(data);
	ft_philo_loop(data, data->philo);
	ft_wait_death(data);
	ft_free_info(data);
	return (0);
}
