/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallouan <rallouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:24:27 by rallouan          #+#    #+#             */
/*   Updated: 2023/11/12 16:25:15 by rallouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
	{
		return (1);
	}
	else
		return (0);
}

int	ft_is_number(char *src)
{
	int	i;

	i = 0;
	if ((src[i] == '-' || src[i] == '+') && src[i + 1] != '\0')
		i++;
	while (src[i] && ft_isdigit(src[i]))
		i++;
	if (src[i] != '\0' && !ft_isdigit(src[i]))
		return (0);
	return (1);
}

int	input_parsing(int argc, char **argv)
{
	int	i;
	int	n;

	i = 1;
	while (argv[i])
	{
		if (! ft_is_number(argv[i]))
			return (error_handling(NONUM, NULL));
		i++;
	}
	n = ft_atoi(argv[1]);
	if (n > 200 || n <= 0)
		return (error_handling(PHILO, NULL));
	i = 2;
	while (i < argc)
	{
		n = ft_atoi(argv[i]);
		if (n <= 0)
			return (error_handling(NEG, NULL));
		i++;
	}
	return (0);
}
