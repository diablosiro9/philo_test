/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 03:00:09 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/22 18:11:59 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
// COMMENT FOR COMPIL : gcc -g -pthread main.c"

typedef struct s_philo
{
	long long	time_to_die;
	long long	time_to_eat;
	
}t_philo;

typedef	struct s_all
{
	int				tt_philo;
	int				tt_fork;
	int				*flag_mutex;	
	int				idx_philo;
	int				idx_fork;
	pthread_t		*tab_philo;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*fork_mutex;
	useconds_t		last_time;
	useconds_t		time_start;
}t_all;

# endif