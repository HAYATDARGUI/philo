/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:31:16 by hdargui           #+#    #+#             */
/*   Updated: 2025/06/21 15:37:12 by hdargui          ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		sleeping(philo);
	while (!check_dead(philo->rules))
	{
		print_action(philo, "is thinking");
		pthread_mutex_lock(philo->first_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->second_fork);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		philo->last_meal = get_time();
		philo->meals++;
		smart_sleep(philo->rules->time_to_eat, philo->rules);
		pthread_mutex_unlock(philo->first_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_unlock(philo->second_fork);
		print_action(philo, "has taken a fork");
		sleeping(philo);
	}
	return (NULL);
}
