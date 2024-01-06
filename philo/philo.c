/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallouan <rallouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:05:35 by rallouan          #+#    #+#             */
/*   Updated: 2023/11/13 13:05:25 by rallouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_data *data)
{
	data->start_time = get_current_time();
	if (pthread_create(&data->threads[0], NULL,
			&philo_routine, &data->philos[0]))
		return (error_handling(TH_CR, data));
	pthread_detach(data->threads[0]);
	while (! data->dead)
		ft_usleep(0);
	ft_end(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 6 || argc < 5)
		return (error_handling(ARGS, NULL));
	if (input_parsing(argc, argv))
		return (1);
	if (init_all(&data, argc, argv))
		return (1);
	if (data.num_philo == 1)
		return (one_philo(&data));
	if (start_threads(&data))
		return (1);
	ft_end(&data);
	return (0);
}
