/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:00:39 by kboulkri          #+#    #+#             */
/*   Updated: 2024/01/31 16:10:03 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
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
	pthread_mutex_t	*mutex_death;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	*mutex_write;
	pthread_mutex_t	*mutex_start;
	int 			*death_flag;
	int				*eat_flag;
}					t_philo;


typedef struct s_monitoring
{
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_start;
	int				death_flag;
	int				eat_flag;	
}					t_moni;

/* monitoring.c */

long int			actual_time(void);

/* utils.c */

int					ft_atoi(const char *str);
int					ft_parse(char **argv);
int					ft_isdigit(int c);

#endif