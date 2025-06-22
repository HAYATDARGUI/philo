/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:51:51 by hdargui           #+#    #+#             */
/*   Updated: 2025/06/22 15:26:31 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (res > 9223372036854775807 && sign == 1)
			return (-1);
		if (res > 9223372036854775807 && sign == -1)
			return (0);
		str++;
	}
	return (res * sign);
}

int	parse_args(int arc, char **arv, t_rules *rules)
{
	int	i;

	i = 1;
	if (arc != 5 && arc != 6)
		return (printf("Error: Wrong number of arguments.\n"), 1);
	while (i < arc)
	{
		if (!ft_is_digit(arv[i]) || ft_atoi(arv[i]) <= 0)
			return (printf("error : invalide argument %s\n", arv[i]), 1);
		i++;
	}
	rules->nb_philos = ft_atoi(arv[1]);
	rules->time_to_die = ft_atoi(arv[2]);
	rules->time_to_eat = ft_atoi(arv[3]);
	rules->time_to_sleep = ft_atoi(arv[4]);
	if (arc == 6)
		rules->must_eat = ft_atoi(arv[5]);
	else
		rules->must_eat = -1;
	if (rules->time_to_die < 60 || rules->time_to_eat < 60
		|| rules->time_to_sleep < 60)
		return (write(2, "Error:time must be greater than 60ms.\n", 39), 1);
	return (0);
}
