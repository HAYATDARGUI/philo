/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:50:36 by hdargui           #+#    #+#             */
/*   Updated: 2025/06/22 20:07:28 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_die(t_philo *philos)
{
	long	time;

	time = get_time();
	pthread_mutex_lock(&philos->rules->meals);
	if (time - philos->last_meal > philos->rules->time_to_die)
	{
		pthread_mutex_lock(&philos->rules->mutex_dead);
		if (!philos->rules->dead)
		{
			printf("%lld %d %s\n", get_time() - philos->rules->start_time,
				philos->id, "died");
			philos->rules->dead = true;
			if (philos->rules->nb_philos == 1)
				pthread_mutex_unlock(philos->first_fork);
		}
		philos->rules->dead = true;
		pthread_mutex_unlock(&philos->rules->mutex_dead);
		pthread_mutex_unlock(&philos->rules->meals);
		return (true);
	}
	pthread_mutex_unlock(&philos->rules->meals);
	return (false);
}

bool	check_dead(t_rules *rules)
{
	bool	status;

	pthread_mutex_lock(&rules->mutex_dead);
	status = rules->dead;
	pthread_mutex_unlock(&rules->mutex_dead);
	return (status);
}

void	*monitor(void *arg)
{
	t_rules	*rules;
	int		i;

	i = 0;
	rules = (t_rules *)arg;
	while (1)
	{
		if (i == rules->nb_philos)
			i = 0;
		if (ft_die(&rules->philo[i]))
			return (NULL);
		i++;
		if (all_philos_eat(rules))
		{
			pthread_mutex_lock(&rules->mutex_dead);
			rules->dead = true;
			pthread_mutex_unlock(&rules->mutex_dead);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}

void	create_thread(t_rules *rules)
{
	int			i;
	pthread_t	monitors;
	int			j;

	i = 0;
	while (i < rules->nb_philos)
	{
		pthread_create(&rules->philo[i].thread, NULL, routine,
			&rules->philo[i]);
		i++;
	}
	pthread_create(&monitors, NULL, monitor, rules);
	j = 0;
	while (j < rules->nb_philos)
	{
		pthread_join(rules->philo[j].thread, NULL);
		j++;
	}
	pthread_join(monitors, NULL);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		i;

	i = 0;
	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_rules(&rules, rules.nb_philos))
		return (1);
	rules.start_time = get_time();
	create_thread(&rules);
	while (i < rules.nb_philos)
	{
		pthread_mutex_destroy(&rules.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules.mutex_dead);
	pthread_mutex_destroy(&rules.print);
	pthread_mutex_destroy(&rules.meals);
	free(rules.philo);
	free(rules.forks);
	return (0);
}
