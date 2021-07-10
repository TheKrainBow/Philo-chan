/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:04:56 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/07/10 06:29:17 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "libft.h"
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct		s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
	pthread_mutex_t	speak;
	pthread_mutex_t	*forks;
	struct timeval	starting_time;
}					t_data;

typedef struct		s_philo
{
	int				id;
	int				prev;
	pthread_mutex_t	mut_alive;
	int				alive;
	pthread_t		thread_id;
	struct timeval	time;
	t_data			*data;
}					t_philo;

#endif
