/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 03:14:00 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/22 17:33:37 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

useconds_t	philo_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_usleep(useconds_t usec)
{
	useconds_t		start;
	useconds_t		after;

	start = philo_get_time();
	after = start;
	while (after - start < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = philo_get_time();
	}
	return (0);
}

pthread_t	*tab_thread(pthread_t *tab, int nombre)
{
	tab = (pthread_t *)malloc(sizeof(pthread_t) * nombre);
	if (!tab)
		return (NULL);
	return (tab);
}

pthread_mutex_t	*tab_mutex(pthread_mutex_t *tab, int nb)
{
	tab = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb);
	if (!tab)
		return (NULL);
	return (tab);
}

void	*function(void *data)
{
	data = (t_all *)data;
	printf("flag_mutex[(t_all *)(data))->idx_philo] == %d\n", (((t_all *)(data))->flag_mutex[((t_all *)(data))->idx_philo]));
	printf("flag_mutex[(t_all *)(data))->idx_philo] == %d\n", (((t_all *)(data))->flag_mutex[((t_all *)(data))->idx_philo + 1]));
	
	// printf("Fork 1 = %d\n", (((t_all *)(data))->fork_mutex[0]));
    // printf("Fork 2 = %d\n", ((t_all *)(data))->fork_mutex[1]);
	if (((t_all *)(data))->flag_mutex[((t_all *)(data))->idx_philo] == 1)
	{
		printf("ici\n");
		printf("all->idx_philo == %d, Create_philo\n", ((t_all *)(data))->idx_philo);
	}
	else
	{
		// return (NULL);
		ft_usleep(500);
		pthread_mutex_lock(&((t_all *)(data))->fork_mutex[((t_all *)(data))->idx_philo]);
		pthread_mutex_lock(&((t_all *)(data))->fork_mutex[((t_all *)(data))->idx_philo + 1]);
		printf("all->idx_philo == %d, Create_philo\n", ((t_all *)(data))->idx_philo);
		printf("OUIII\n");
		pthread_mutex_unlock(&((t_all *)(data))->fork_mutex[((t_all *)(data))->idx_philo]);
	}
	// // pthread_join(((t_all *)(data))->tab_philo[((t_all *)(data))->idx_philo], NULL);
	// }
	// else
	// {
	// 	printf("la\n");
	// 	ft_usleep(10);
	((t_all *)(data))->flag_mutex[((t_all *)(data))->idx_philo] = 0;
	((t_all *)(data))->flag_mutex[((t_all *)(data))->idx_philo + 1] = 0;
	pthread_mutex_unlock(&((t_all *)(data))->fork_mutex[((t_all *)(data))->idx_philo]);
	pthread_mutex_unlock(&((t_all *)(data))->fork_mutex[((t_all *)(data))->idx_philo + 1]);
	// 	printf("all->idx_philo == %d, Create_philo\n", ((t_all *)(data))->idx_philo);
	// 	pthread_mutex_lock(&((t_all *)(data))->mutex[((t_all *)(data))->idx_philo]);
	// }
	// pthread_mutex_unlock(&((t_all *)(data))->mutex[((t_all *)(data))->idx_philo]);
	return ((void *)data);
}

int	*create_tab(int *tab, int nb)
{
	tab = (int *)malloc(sizeof(int) * nb + 1);
	if (!tab)
		return (NULL);
	tab[nb] = '\0';
	return (tab);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	t_all	*all;
	int			i = 0;
	int			x = 0;

	i = 0;
	x = 10;
	all = NULL;
	all = malloc(sizeof(t_all) * 1);
	if (!all)
		return (0);
	printf("oui\n");
	// pthread_mutex_init(&all->mutex, NULL);
	printf("ten sors\n");
	all->idx_philo = 0;
	all->tt_philo = x;
	all->tt_fork = x;
	all->idx_fork = 0;
	all->flag_mutex = create_tab(all->flag_mutex, x);
	all->tab_philo = tab_thread(all->tab_philo, x);
	all->mutex = tab_mutex(all->mutex, x);
	all->fork_mutex = tab_mutex(all->fork_mutex, x);
	while (i < x)
	{
		pthread_mutex_init(&all->fork_mutex[i], NULL);
		pthread_mutex_init(&all->fork_mutex[i + 1], NULL);
		all->idx_philo = i;
		all->idx_fork = i;
		// printf("i = %d, all->idx_philo = %d\n", i, all->idx_philo);
		// pthread_mutex_destroy(&all->mutex[i]);
		if (i % 2 == 0)
		{
			pthread_mutex_lock(&all->fork_mutex[i]);
			pthread_mutex_lock(&all->fork_mutex[i + 1]);
			all->flag_mutex[i] = 1;
			all->flag_mutex[i + 1] = 1;
		}
		else
		{
			pthread_mutex_unlock(&all->fork_mutex[i]);
			pthread_mutex_unlock(&all->fork_mutex[i + 1]);
			ft_usleep(50);
			// pthread_mutex_lock(&all->fork_mutex[i]);
			// pthread_mutex_lock(&all->fork_mutex[i + 1]);

			// pthread_mutex_lock(&all->fork_mutex[i]);
			// pthread_mutex_lock(&all->fork_mutex[i + 1]);
			all->flag_mutex[i] = 0;
			all->flag_mutex[i + 1] = 0;
		}
		// pthread_mutex_lock(&all->mutex[i]);
		pthread_create(&all->tab_philo[i], NULL, &function, all);
		pthread_join(all->tab_philo[all->idx_philo], NULL);
		i++;
		if (i == x)
			i = 0;
	}
}