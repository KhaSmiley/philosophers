/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:00:39 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/17 15:27:58 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	size_t			start_time;
	size_t			last_meal;
	int				eating;
	int				meals_eaten;

	pthread_mutex_t	*mutex_left_f;
	pthread_mutex_t	mutex_right_f;

	pthread_mutex_t	*mutex_stop_write;
	pthread_mutex_t	*mutex_death;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	*mutex_write;
	int				*stop_write;
	int				*death_flag;
	int				*eat_flag;
}					t_philo;

typedef struct s_monitoring
{
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_stop_write;
	int				stop_write;
	int				death_flag;
	int				eat_flag;
}					t_moni;

/* monitoring.c */

void				*monitor(void *args);
int					is_philo_dead(t_philo *philo);
int					enough_food(t_philo *philo);
void				ft_usleep(long int time_in_ms, t_philo *philo);
long int			actual_time(void);

/* philo_moves */

int					handle_one(t_philo *philo);
int					philo_eat(t_philo *philo);
int					philo_eat_two(t_philo *philo);
int					philo_write(t_philo *philo, char *str);
int					philo_sleep(t_philo *philo);

/* philosophers.c */

int					init_thread(t_philo *data);
int					init_mutex(t_philo data[], t_moni *check);
int					init_data(t_philo *data, t_moni *check, char **argv,
						int argc);
void				*routine(void *args);

/* utils_thread.c */

void				mutex_destroyer(t_philo *philo);
int					thread_destroyer(t_philo *philo);
int					ft_check_death(t_philo *philo);

/* utils.c */

int					ft_atoi(const char *str);
int					ft_parse(char **argv);
int					ft_isdigit(int c);

#endif