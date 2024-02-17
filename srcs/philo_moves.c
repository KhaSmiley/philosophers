/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:49:54 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/17 15:00:06 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	handle_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_right_f);
	philo_write(philo, "has taken a fork");
	ft_usleep(philo->time_to_die, philo);
	philo_write(philo, "died");
	return (pthread_mutex_unlock(&philo->mutex_right_f), 1);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_right_f);
	if (philo_write(philo, "has taken a fork"))
		return (pthread_mutex_unlock(&philo->mutex_right_f), 1);
	pthread_mutex_lock(philo->mutex_left_f);
	if (philo_write(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->mutex_left_f),
			pthread_mutex_unlock(&philo->mutex_right_f), 1);
	if (philo_write(philo, "is eating"))
		return (pthread_mutex_unlock(philo->mutex_left_f),
			pthread_mutex_unlock(&philo->mutex_right_f), 1);
	pthread_mutex_lock(philo->mutex_eat);
	philo->meals_eaten += 1;
	philo->last_meal = actual_time();
	pthread_mutex_unlock(philo->mutex_eat);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(&philo->mutex_right_f);
	pthread_mutex_unlock(philo->mutex_left_f);
	return (0);
}

int	philo_eat_two(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_left_f);
	if (philo_write(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->mutex_left_f), 1);
	pthread_mutex_lock(&philo->mutex_right_f);
	if (philo_write(philo, "has taken a fork"))
		return (pthread_mutex_unlock(&philo->mutex_right_f),
			pthread_mutex_unlock(philo->mutex_left_f), 1);
	if (philo_write(philo, "is eating"))
		return (pthread_mutex_unlock(&philo->mutex_right_f),
			pthread_mutex_unlock(philo->mutex_left_f), 1);
	pthread_mutex_lock(philo->mutex_eat);
	philo->meals_eaten += 1;
	philo->last_meal = actual_time();
	pthread_mutex_unlock(philo->mutex_eat);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(&philo->mutex_right_f);
	pthread_mutex_unlock(philo->mutex_left_f);
	return (0);
}

int	philo_write(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->mutex_stop_write);
	if (*(philo->stop_write) == 1)
		return (pthread_mutex_unlock(philo->mutex_stop_write), 1);
	pthread_mutex_unlock(philo->mutex_stop_write);
	pthread_mutex_lock(philo->mutex_death);
	if (*(philo->death_flag) == 1)
		return (pthread_mutex_unlock(philo->mutex_death), 1);
	pthread_mutex_unlock(philo->mutex_death);
	pthread_mutex_lock(philo->mutex_write);
	printf("%ld %d %s\n", actual_time() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(philo->mutex_write);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (philo_write(philo, "is sleeping"))
		return (1);
	ft_usleep(philo->time_to_sleep, philo);
	if (philo_write(philo, "is thinking"))
		return (1);
	pthread_mutex_lock(philo->mutex_death);
	pthread_mutex_lock(philo->mutex_eat);
	while ((philo->time_to_die - (actual_time()
				- philo->last_meal) > philo->time_to_eat)
		&& *philo->death_flag == 0)
	{
		pthread_mutex_unlock(philo->mutex_eat);
		pthread_mutex_unlock(philo->mutex_death);
		ft_usleep(1, philo);
		pthread_mutex_lock(philo->mutex_death);
		pthread_mutex_lock(philo->mutex_eat);
	}
	pthread_mutex_unlock(philo->mutex_eat);
	pthread_mutex_unlock(philo->mutex_death);
	return (0);
}
