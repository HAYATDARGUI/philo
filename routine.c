/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:31:16 by hdargui           #+#    #+#             */
/*   Updated: 2025/06/23 11:15:52 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_philos_eat(t_rules *rules)
{
	int	i;

	i = 0;
	if (rules->must_eat == -1)
		return (false);
	while (i < rules->nb_philos)
	{
		if (rules->philo[i].meals < rules->must_eat)
			return (false);
		i++;
	}
	return (true);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->rules->time_to_sleep, philo->rules);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->rules->meals);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->rules->meals);
	pthread_mutex_lock(&philo->rules->meal_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->rules->meal_mutex);
	smart_sleep(philo->rules->time_to_eat, philo->rules);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->rules->meals);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->rules->meals);
	if (philo->id % 2 == 0)
		sleeping(philo);
	while (!check_dead(philo->rules))
	{
		print_action(philo, "is thinking");
		philo_eat(philo);
		sleeping(philo);
	}
	return (NULL);
}
