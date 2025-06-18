/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:21 by hdargui           #+#    #+#             */
/*   Updated: 2025/06/18 12:38:13 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
void	smart_sleep(long duration_ms, t_rules *rules)
{
	long start;

	start = get_time();
	while (!check_dead(rules))
	{
		if (get_time() - start >= duration_ms)
			break ;
		usleep(100);
	}
}
