/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:01:23 by magostin          #+#    #+#             */
/*   Updated: 2021/07/10 06:53:55 by mdelwaul         ###   ########.fr       */
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

void	ft_fill_data(t_data **data, int ac, char **av)
{
	int	i;

	(*data)->n_philo = ft_atoi(av[1]);
	(*data)->t_die = ft_atoi(av[2]);
	(*data)->t_eat = ft_atoi(av[3]);
	(*data)->t_sleep = ft_atoi(av[4]);
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->n_philo);
	i = -1;
	while (++i < (*data)->n_philo)
		pthread_mutex_init(&((*data)->forks[i]), NULL);
	pthread_mutex_init(&((*data)->speak), NULL);
	if (ac == 6)
		(*data)->max_eat = ft_atoi(av[5]);
	else
		(*data)->max_eat = -1;
	printf("We have %d philo that die in %dms, take %dms to eat and %dms to sleep\n", (*data)->n_philo, (*data)->t_die, (*data)->t_eat, (*data)->t_sleep);
}

void	ft_free_data(t_data *data, t_philo **philo)
{
	int		i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&(philo[i]->mut_alive));
		free(philo[i]);
	}
	free(philo);
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->speak));
	free(data);
}

void	ft_talk(t_philo *philo, char *str)
{
	struct timeval	time;

	gettimeofday(&(time), NULL);
	pthread_mutex_lock(&(philo->data->speak));
	printf("%ld.%ld %d %s\n", time.tv_sec - philo->data->starting_time.tv_sec, time.tv_usec - philo->data->starting_time.tv_usec, philo->id, str);
	pthread_mutex_unlock(&(philo->data->speak));
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&(philo->data->forks[philo->id]));
		ft_talk(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->data->forks[philo->prev]));
		ft_talk(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[philo->prev]));
		ft_talk(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->data->forks[philo->id]));
		ft_talk(philo, "has taken a fork");
	}
	ft_talk(philo, "is eating");
	usleep(1000 * philo->data->t_eat);
	pthread_mutex_unlock(&(philo->data->forks[philo->prev]));
	pthread_mutex_unlock(&(philo->data->forks[philo->id]));
	ft_talk(philo, "is sleeping");
	usleep(1000 * philo->data->t_sleep);
}

void	*philochan(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	ft_talk(philo, "is thinking");
	ft_eat(philo);
	pthread_mutex_lock(&(philo->mut_alive));
	philo->alive = 0;
	pthread_mutex_unlock(&(philo->mut_alive));
	ft_talk(philo, "died");
	return (NULL);
}

void	ft_create_philo(t_philo ***philo, t_data *data)
{
	int		i;

	(*philo) = malloc(sizeof(t_philo *) * (data->n_philo + 1));
	i = -1;
	while (++i < data->n_philo)
	{
		(*philo)[i] = malloc(sizeof(t_philo));
		(*philo)[i]->data = data;
		(*philo)[i]->id = i;
		pthread_mutex_init(&((*philo)[i]->mut_alive), NULL);
		(*philo)[i]->alive = 1;
		if ((*philo)[i]->id > 0)
			(*philo)[i]->prev = (*philo)[i]->id - 1;
		else
			(*philo)[i]->prev = (*philo)[i]->data->n_philo;
	}
	gettimeofday(&(data->starting_time), NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_create(&((*philo)[i]->thread_id), NULL, philochan, (*philo)[i]);
		pthread_detach((*philo)[i]->thread_id);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	**philo;
	int	alive;
	int	i;

	data = malloc(sizeof(t_data));
	if (!data || ft_arg_error(ac, av))
		return (1);
	ft_fill_data(&data, ac, av);
	ft_create_philo(&philo, data);

	alive = 1;
	while (alive)
	{
		i = -1;
		while (++i < data->n_philo && alive)
		{
			pthread_mutex_lock(&(philo[i]->mut_alive));
			if (philo[i]->alive == 0)
			{
				printf("SIMULATION SHOULD STOP HERE\n");
				alive = 0;
			}
			pthread_mutex_unlock(&(philo[i]->mut_alive));
		}
		usleep(1000);
	}
	while(1);
	ft_free_data(data, philo);
	return (0);
}