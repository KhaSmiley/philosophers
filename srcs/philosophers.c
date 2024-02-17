/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:05:48 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/17 15:08:31 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (92110)
	{
		if (ft_check_death(philo))
			return (NULL);
		if (philo->id % 2 == 0)
		{
			if (philo_eat(philo))
				return (NULL);
		}
		else
		{
			if (philo_eat_two(philo))
				return (NULL);
		}
		philo_sleep(philo);
	}
	return (NULL);
}

int	init_data(t_philo *data, t_moni *check, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		data[i].id = i + 1;
		data[i].death_flag = &check->death_flag;
		data[i].eat_flag = &check->eat_flag;
		data[i].stop_write = &check->stop_write;
		data[i].num_of_philos = ft_atoi(argv[1]);
		data[i].time_to_die = ft_atoi(argv[2]);
		data[i].time_to_eat = ft_atoi(argv[3]);
		data[i].time_to_sleep = ft_atoi(argv[4]);
		data[i].num_times_to_eat = -1;
		if (argc == 6)
			data[i].num_times_to_eat = ft_atoi(argv[5]);
		data[i].meals_eaten = 0;
		data[i].eating = 0;
		data[i].start_time = actual_time();
		data[i].last_meal = actual_time();
		pthread_mutex_init(&data[i].mutex_right_f, NULL);
		i++;
	}
	return (0);
}

int	init_mutex(t_philo data[], t_moni *check)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&check->mutex_death, NULL)
		|| pthread_mutex_init(&check->mutex_eat, NULL)
		|| pthread_mutex_init(&check->mutex_write, NULL)
		|| pthread_mutex_init(&check->mutex_stop_write, NULL))
		return (printf("Error on mutex init"), 1);
	while (i < data[0].num_of_philos)
	{
		if (i + 1 == data[i].num_of_philos)
			data[i].mutex_left_f = &data[0].mutex_right_f;
		else
			data[i].mutex_left_f = &data[i + 1].mutex_right_f;
		if (pthread_mutex_init(&data[i].mutex_right_f, NULL))
			return (printf("Error on mutex init"), 1);
		data[i].mutex_death = &check->mutex_death;
		data[i].mutex_eat = &check->mutex_eat;
		data[i].mutex_write = &check->mutex_write;
		data[i].mutex_stop_write = &check->mutex_stop_write;
		i++;
	}
	return (0);
}

int	init_thread(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data[0].num_of_philos)
	{
		if (pthread_create(&data[i].thread, NULL, &routine, &data[i]) != 0)
			return (printf("Error on thread creation"), 1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		data[200];
	t_moni		check;
	pthread_t	monitoring;

	check.death_flag = 0;
	check.eat_flag = 0;
	check.stop_write = 0;
	if (argc < 5 || argc > 6 || ft_parse(argv))
		return (1);
	if (init_data(data, &check, argv, argc))
		return (1);
	if (init_mutex(data, &check))
		return (1);
	if (data[0].num_of_philos == 1)
	{
		handle_one(&data[0]);
		return (0);
	}
	if (init_thread(data))
		return (1);
	pthread_create(&monitoring, NULL, &monitor, &data);
	pthread_join(monitoring, NULL);
	thread_destroyer(data);
	mutex_destroyer(data);
	return (0);
}
