/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallouan <rallouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:46:09 by rallouan          #+#    #+#             */
/*   Updated: 2023/11/13 17:59:44 by rallouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	u_int64_t	now;

	pthread_mutex_lock(&philo->data->console);
	now = get_current_time() - philo->data->start_time;
	if (ft_strncmp(status, DIE, 4) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", now, philo->id, status);
		pthread_mutex_lock(&philo->data->lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	if (philo->data->dead == 0)
		printf("%llu %d %s\n", now, philo->id, status);
	pthread_mutex_unlock(&philo->data->console);
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, FORK);
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, FORK);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	eat(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_current_time() + philo->data->death_time;
	print_status(philo, EAT);
	philo->ate_count++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	unlock_forks(philo);
	print_status(philo, SLEEP);
	ft_usleep(philo->data->sleep_time);
}
