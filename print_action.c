/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:14:22 by hdargui           #+#    #+#             */
/*   Updated: 2025/06/18 13:22:34 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->rules->print);
	if (!check_dead(philo->rules))
		printf("[%lld] Philo %d %s\n", get_time() - philo->rules->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print);
}
