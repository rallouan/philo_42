/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallouan <rallouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:48:13 by rallouan          #+#    #+#             */
/*   Updated: 2023/11/12 19:37:49 by rallouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	if (data->threads)
		free(data->threads);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	ft_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->console);
	pthread_mutex_destroy(&data->lock);
	free_data(data);
}

int	error_handling(char *err, t_data *data)
{
	printf("Error: |%s|\n", err);
	if (data)
		ft_end(data);
	return (1);
}
