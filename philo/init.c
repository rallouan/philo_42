/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallouan <rallouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:07:50 by rallouan          #+#    #+#             */
/*   Updated: 2023/11/13 14:01:42 by rallouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philo = (int) ft_atoi(argv[1]);
	data->death_time = (u_int64_t) ft_atoi(argv[2]);
	data->eat_time = (u_int64_t) ft_atoi(argv[3]);
	data->sleep_time = (u_int64_t) ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = (int) ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->console, NULL);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].ate_count = 0;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		data->philos[i].time_to_die = data->death_time;
		if (pthread_mutex_init(&data->philos[i].lock, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->num_philo - 1];
	i = 1;
	while (i < data->num_philo)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (1);
}

int	init_all(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv))
		return (error_handling(MUTEX, data));
	data->threads = malloc(data->num_philo * sizeof(pthread_t));
	if (! data->threads)
		return (error_handling(ALLOC, data));
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	if (! data->forks)
		return (error_handling(ALLOC, data));
	data->philos = malloc(data->num_philo * sizeof(t_philo));
	if (! data->philos)
		return (error_handling(ALLOC, data));
	if (! init_forks(data))
		return (error_handling(MUTEX, data));
	if (! init_philos(data))
		return (error_handling(MUTEX, data));
	return (0);
}
