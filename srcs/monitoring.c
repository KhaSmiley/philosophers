/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:44:40 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/17 15:39:35 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	actual_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (printf("Gettimeofday returned -1\n"), -1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms, t_philo *philo)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	pthread_mutex_lock(philo->mutex_death);
	while ((actual_time() - start_time) < time_in_ms
		&& (*(philo->death_flag) == 0))
	{
		pthread_mutex_unlock(philo->mutex_death);
		usleep(999);
		pthread_mutex_lock(philo->mutex_death);
	}
	pthread_mutex_unlock(philo->mutex_death);
}

int	enough_food(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo->mutex_eat);
		if (philo[i].meals_eaten < philo[0].num_times_to_eat)
			return (pthread_mutex_unlock(philo->mutex_eat), 0);
		pthread_mutex_unlock(philo->mutex_eat);
		i++;
	}
	pthread_mutex_lock(philo->mutex_eat);
	pthread_mutex_lock(philo->mutex_stop_write);
	*(philo->eat_flag) = 1;
	*(philo->stop_write) = 1;
	pthread_mutex_unlock(philo->mutex_eat);
	pthread_mutex_unlock(philo->mutex_stop_write);
	return (1);
}

int	is_philo_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo->mutex_eat);
		if ((philo->time_to_die <= (actual_time() - philo[i].last_meal)))
		{
			pthread_mutex_unlock(philo->mutex_eat);
			philo_write(philo, "died");
			pthread_mutex_lock(philo->mutex_death);
			pthread_mutex_lock(philo->mutex_stop_write);
			*(philo->death_flag) = 1;
			*(philo->stop_write) = 1;
			pthread_mutex_unlock(philo->mutex_stop_write);
			pthread_mutex_unlock(philo->mutex_death);
			return (1);
		}
		pthread_mutex_unlock(philo->mutex_eat);
		i++;
	}
	return (0);
}

void	*monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (philo->num_times_to_eat != -1)
		{
			if (enough_food(philo) == 1)
				return (NULL);
		}
		if (is_philo_dead(philo))
			return (NULL);
	}
	return (NULL);
}
