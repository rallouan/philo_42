/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallouan <rallouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:13:33 by rallouan          #+#    #+#             */
/*   Updated: 2023/11/12 18:53:12 by rallouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi(const char *str)
{
	long int	nb;
	int			isneg;
	int			i;

	nb = 0;
	isneg = 1;
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isneg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb * isneg);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		sim;

	i = 0;
	sim = 0;
	while (s1[i] != '\0' && i < n)
	{
		sim = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (sim != 0)
			return (sim);
		else
			i++;
	}
	if (s2[i] != '\0' && i < n)
		sim = - (unsigned char)s2[i];
	return (sim);
}

u_int64_t	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((u_int64_t)current_time.tv_sec * 1000)
		+ ((u_int64_t)current_time.tv_usec / 1000));
}

int	ft_usleep(useconds_t t)
{
	u_int64_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < t)
		usleep(t / 10);
	return (0);
}
