/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:37:48 by hdargui           #+#    #+#             */
/*   Updated: 2025/06/19 13:31:20 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_rules
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	long long			start_time;
	bool				dead;
	pthread_mutex_t		mutex_dead;
	pthread_mutex_t		print;
	pthread_mutex_t		*forks;
	t_philo				*philo;
	pthread_mutex_t		meals;
}						t_rules;

typedef struct s_philo
{
	int					id;
	int					meals;
	bool				eat_all_meals;
	long long			last_meal;
	pthread_t			thread;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	t_rules				*rules;
}						t_philo;
void					*routine(void *arg);
long long				get_time(void);
int						parse_args(int arc, char **arv, t_rules *rules);
int						init_rules(t_rules *rules, int nb_philos);
void					print_action(t_philo *philo, char *msg);
bool					check_dead(t_rules *rules);
void					smart_sleep(long duration_ms, t_rules *rules);
bool					all_philos_eat(t_rules *rules);

#endif