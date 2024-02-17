/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:58:44 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/17 15:08:52 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_death);
	pthread_mutex_lock(philo->mutex_eat);
	if (*(philo->death_flag) == 1 || *(philo->eat_flag) == 1)
		return (pthread_mutex_unlock(philo->mutex_death),
			pthread_mutex_unlock(philo->mutex_eat), 1);
	pthread_mutex_unlock(philo->mutex_death);
	pthread_mutex_unlock(philo->mutex_eat);
	return (0);
}

int	thread_destroyer(t_philo *philo)
{
	int	i;

	(void)philo;
	i = 0;
	while (i < philo[0].num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	mutex_destroyer(t_philo *philo)
{
	pthread_mutex_destroy(philo->mutex_eat);
	pthread_mutex_destroy(philo->mutex_write);
	pthread_mutex_destroy(&philo->mutex_right_f);
	pthread_mutex_destroy(philo->mutex_left_f);
	pthread_mutex_destroy(philo->mutex_stop_write);
	pthread_mutex_destroy(philo->mutex_death);
}
