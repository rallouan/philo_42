/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallouan <rallouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:00:33 by rallouan          #+#    #+#             */
/*   Updated: 2023/11/13 13:36:17 by rallouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

// Circular dependecy so gotta tell the compiler s_data exists
// And will be defined later
struct		s_data;

typedef struct s_philo
{
	struct s_data		*data;
	pthread_t			th;
	int					id;
	int					ate_count;
	int					status;
	int					eating;
	u_int64_t			time_to_die;
	pthread_mutex_t		lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t			*threads;
	int					num_philo;
	int					num_meals;
	int					dead;
	int					finished;
	t_philo				*philos;
	u_int64_t			death_time;
	u_int64_t			eat_time;
	u_int64_t			sleep_time;
	u_int64_t			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		console;
}	t_data;

// Philo statuses
# define FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIE "died"

// Error messages
# define ARGS "Wrong number of arguments"
# define NONUM "Input contains a non-numeric character"
# define PHILO "Wrong number of philosophers"
# define NEG "Input is not a positive value"
# define MUTEX "Mutex initialization error"
# define ALLOC "Allocation error"
# define TH_CR "Thread creation error"
# define TH_JOIN "Thread join error"

// Utils functions
long int		ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
u_int64_t		get_current_time(void);
int				ft_usleep(useconds_t t);

// Parsing function
int				input_parsing(int argc, char **argv);
int				ft_is_number(char *src);
int				ft_isdigit(int c);

// Init functions
int				init_all(t_data *data, int argc, char **argv);
int				init_data(t_data *data, int argc, char **argv);
int				init_forks(t_data *data);
int				init_philos(t_data *data);

// Threads functions
int				start_threads(t_data *data);
void			*philo_routine(void *philo_ptr);
void			*supervisor_routine(void *philo_ptr);
void			*monitor_routine(void *philo_ptr);
int				one_philo(t_data *data);

// Philo action functions
void			print_status(t_philo *philo, char *status);
void			lock_forks(t_philo *philo);
void			unlock_forks(t_philo *philo);
void			eat(t_philo *philo);

// Exit fuctions
void			free_data(t_data *data);
void			ft_end(t_data *data);
int				error_handling(char *err, t_data *data);

#endif