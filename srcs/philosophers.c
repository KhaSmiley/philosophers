/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:05:48 by kboulkri          #+#    #+#             */
/*   Updated: 2024/01/31 18:31:51 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void *philo(void *args)
{
	t_moni *data = (t_moni *)args;
	pthread_mutex_lock(data->mutex_start);
	data->death_flag = 0;
	pthread_mutex_unlock(data->mutex_start);
	return NULL;
}

int	init_data(t_philo *data, t_moni *check, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		data[i].id = i + 1;
		data[i].num_of_philos = ft_atoi(argv[1]);
		data[i].time_to_die = ft_atoi(argv[2]);
		data[i].time_to_eat = ft_atoi(argv[3]);
		data[i].time_to_sleep = ft_atoi(argv[4]);
		data[i].num_times_to_eat = -1;
		if (argc == 6)
			data[i].num_times_to_eat = ft_atoi(argv[5]);
		data[i].meals_eaten = 0;
		data[i].start_time = actual_time();
		data[i].last_meal = actual_time();
		pthread_mutex_init(&data[i].mutex_right_f, NULL);
		i++;
	}
	printf("Data has been init");
	return (0);
}

int	init_mutex(t_philo data[], t_moni *check)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&check->mutex_death, NULL)
		|| pthread_mutex_init(&check->mutex_eat, NULL)
		|| pthread_mutex_init(&check->mutex_write, NULL)
		|| pthread_mutex_init(&check->mutex_start, NULL))
		return (printf("Error on mutex init"), 1);
	while (i < data[0].num_of_philos)
	{
		if (i + 1 == data->num_of_philos)
			data[i].mutex_left_f = &data[0].mutex_right_f;
		else
			data[i].mutex_left_f = &data[i + 1].mutex_right_f;
		if(pthread_mutex_init(&data[i].mutex_right_f, NULL))
			return (printf("Error on mutex init"), 1);
		data[i].death_flag = &check->death_flag;
		data[i].mutex_death = &check->mutex_death;
		data[i].mutex_eat = &check->mutex_eat;
		data[i].mutex_write = &check->mutex_write;
		data[i].mutex_start = &check->mutex_start;
		data[i].death_flag = &check->death_flag;
		if (pthread_create(&data[i].thread, NULL, &philo, NULL))
			return (printf("Error on thread creation"), 1);
		i++;
	}
	return (0);
}

void *monitor(void *args)
{
	t_moni *check = (t_moni *)args;
	while (1)
	{
		if (check->death_flag == 10)
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int i = 0;
	t_philo data[200];
	t_moni check;
	pthread_t monitoring;

	check.death_flag = 1;
	check.eat_flag = 0;
	if (argc < 5 || argc > 6 || ft_parse(argv))
		return (1);
	if (init_data(data, &check, argv, argc))
		return (1);
	if (init_mutex(data, &check))
		return (1);
	pthread_create(&monitoring, NULL, &monitor, NULL);
	pthread_join(monitoring, NULL);
	printf("All philosophers are dead\n");
	return (0);
}