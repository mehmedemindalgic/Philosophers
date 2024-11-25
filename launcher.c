/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medalgic <medalgic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:10:09 by medalgic          #+#    #+#             */
/*   Updated: 2024/02/02 14:50:58 by medalgic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	routine_while(t_philosopher *philo, t_rules *rules)
{
	while (1)
	{
		philo_eats(philo);
		pthread_mutex_lock(&(rules->dieded_check));
		if (rules->dieded)
		{
			pthread_mutex_unlock(&(rules->dieded_check));
			break ;
		}
		pthread_mutex_unlock(&(rules->dieded_check));
		pthread_mutex_lock(&(rules->all_ate_check));
		if (rules->nb_eat != -1 && (rules->all_ate
				|| philo->x_ate >= rules->nb_eat))
		{
			pthread_mutex_unlock(&(rules->all_ate_check));
			break ;
		}
		pthread_mutex_unlock(&(rules->all_ate_check));
		action_print(rules, philo->id, "is sleeping");
		smart_sleep(rules->time_sleep, rules);
		action_print(rules, philo->id, "is thinking");
	}
}

void	*routine(void *void_philosopher)
{
	t_philosopher	*philo;
	t_rules			*rules;

	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (!(philo->id % 2))
		usleep(15000);
	routine_while(philo, rules);
	return (NULL);
}

void	exit_launcher(t_rules *rules, t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->die_check));
	pthread_mutex_destroy(&(rules->meal_check));
	pthread_mutex_destroy(&(rules->x_ate_check));
	pthread_mutex_destroy(&(rules->t_last_meal_check));
	pthread_mutex_destroy(&(rules->dieded_check));
	pthread_mutex_destroy(&(rules->all_ate_check));
	pthread_mutex_destroy(&(rules->die_write));
	ft_free(rules);
}

void	death_checker(t_rules *r, t_philosopher *p, int i, int j)
{
	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->nb_philo && !(r->dieded))
		{
			pthread_mutex_lock(&(r->t_last_meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_death)
			{
				pthread_mutex_lock(&(r->dieded_check));
				printf("%i ", (int)(timestamp() - r->first_timestamp));
				printf("%i ", i + 1);
				printf("%s\n", "died");
				r->dieded = 1;
				pthread_mutex_unlock(&(r->dieded_check));
				j = -1;
				while (++j < r->nb_philo)
					pthread_mutex_unlock(&(r->forks[j]));
			}
			pthread_mutex_unlock(&(r->t_last_meal_check));
			usleep(50);
		}
		if (r->dieded)
			break ;
		eat_control(r, p);
	}
}

int	launcher(t_rules *rules)
{
	int				i;
	t_philosopher	*phi;

	i = 0;
	phi = rules->philosophers;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, routine, &(phi[i])))
			exit_launcher(rules, phi);
		pthread_mutex_lock(&(rules->t_last_meal_check));
		phi[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(rules->t_last_meal_check));
		i++;
	}
	death_checker(rules, rules->philosophers, -1, -1);
	exit_launcher(rules, phi);
	return (0);
}
