/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:09:38 by hdargui           #+#    #+#             */
/*   Updated: 2025/06/19 13:22:08 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philos)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].meals = 0;
		rules->philo[i].last_meal = get_time();
		rules->philo[i].rules = rules;
		if (rules->philo[i].id == rules->nb_philos)
		{
			rules->philo[i].first_fork = &rules->forks[i];
			rules->philo[i].second_fork = &rules->forks[0];
		}
		else
		{
			rules->philo[i].first_fork = &rules->forks[i];
			rules->philo[i].second_fork = &rules->forks[(i + 1)];
		}
		i++;
	}
}

int	init_rules(t_rules *rules, int nb_philos)
{
	int	i;

	i = 0;
	rules->dead = false;
	rules->nb_philos = nb_philos;
	rules->philo = malloc(sizeof(t_philo) * nb_philos);
	if (!rules->philo)
		return (1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * nb_philos);
	if (!rules->forks)
		return (free(rules->philo), 1);
	while (i < rules->nb_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&rules->mutex_dead, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->print, NULL) != 0)
		return (1);
	init_philo(rules);
	return (0);
}
