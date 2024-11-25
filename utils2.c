/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medalgic <medalgic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:10:35 by medalgic          #+#    #+#             */
/*   Updated: 2024/02/02 13:17:24 by medalgic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	action_print(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->dieded_check));
	if (!(rules->dieded))
	{
		printf("%lli ", timestamp() - rules->first_timestamp);
		printf("%i ", id);
		printf("%s\n", string);
		usleep(50);
	}
	pthread_mutex_unlock(&(rules->dieded_check));
	return ;
}

int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

void	ft_free(t_rules *rules)
{
	free (rules->forks);
	free (rules->philosophers);
}

void	eat_control(t_rules *r, t_philosopher *p)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(r->x_ate_check));
	while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
		i++;
	pthread_mutex_unlock(&(r->x_ate_check));
	if (i == r->nb_philo)
	{
		pthread_mutex_lock(&(r->all_ate_check));
		r->all_ate = 1;
		pthread_mutex_unlock(&(r->all_ate_check));
	}
}

void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	action_print(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	action_print(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_check));
	pthread_mutex_lock(&(rules->die_write));
	action_print(rules, philo->id, "is eating");
	pthread_mutex_unlock(&(rules->die_write));
	pthread_mutex_unlock(&(rules->meal_check));
	pthread_mutex_lock(&(rules->t_last_meal_check));
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->t_last_meal_check));
	smart_sleep(rules->time_eat, rules);
	pthread_mutex_lock(&(rules->x_ate_check));
	(philo->x_ate)++;
	pthread_mutex_unlock(&(rules->x_ate_check));
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}
