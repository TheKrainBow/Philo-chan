/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:04:56 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/10 19:11:45 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "libft.h"
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

# define TAKE_FORK 1
# define LEAVE_FORK 2
# define EAT 3
# define SLEEP 4
# define THINK 5


typedef struct		s_info
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
	int				end;
	pthread_mutex_t	speak;
	pthread_mutex_t	*forks;
	long			starting_time;
}					t_info;

typedef struct		s_philo
{
	int				id;
	int				prev;
	int				alive;
	long			last_eat;
	pthread_t		thread_id;
	pthread_mutex_t	access;
	t_info			*info;
}					t_philo;


typedef struct		s_data
{
	t_info			*info;
	pthread_mutex_t	access_info;
	t_philo			**philo;
}					t_data;

void	ft_init_philo(t_data *data);
void	ft_init_info(t_data *data, int ac, char **av);

void	*philochan(void *p);

void	ft_free_info(t_data *data);

long	ft_time(t_info *info);
int		ft_task(t_philo *philo, int task);
void	ft_take_fork(t_philo *philo);
void	ft_leave_fork(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_talk(t_philo *philo, char *str);
#endif
