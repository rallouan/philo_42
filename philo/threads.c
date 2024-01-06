/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallouan <rallouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:01:39 by rallouan          #+#    #+#             */
/*   Updated: 2023/11/13 18:00:44 by rallouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (! philo->data->dead)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->num_philo)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*supervisor_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (! philo->data->dead)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_current_time() >= philo->time_to_die && ! philo->eating)
		{
			print_status(philo, DIE);
		}
		pthread_mutex_lock(&philo->data->lock);
		if (philo->ate_count == philo->data->num_meals)
		{
			philo->ate_count++;
			philo->data->finished++;
		}
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = philo->data->death_time + get_current_time();
	if (pthread_create(&philo->th, NULL, &supervisor_routine, (void *)philo))
		return ((void *)1);
	while (! philo->data->dead)
	{
		print_status(philo, THINK);
		eat(philo);
	}
	if (pthread_join(philo->th, NULL))
		return ((void *)1);
	return (NULL);
}

int	start_threads(t_data *data)
{
	int			i;
	pthread_t	main;

	i = -1;
	data->start_time = get_current_time();
	if (data->num_meals > 0)
	{
		if (pthread_create(&main, NULL, &monitor_routine, &data->philos[0]))
			return (error_handling(TH_CR, data));
		pthread_detach(main);
	}
	while (++i < data->num_philo)
	{
		if (pthread_create(&data->threads[i], NULL,
				&philo_routine, &data->philos[i]))
			return (error_handling(TH_CR, data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_join(data->threads[i], NULL))
			return (error_handling(TH_JOIN, data));
	}
	return (0);
}
