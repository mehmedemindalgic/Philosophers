/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medalgic <medalgic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:10:23 by medalgic          #+#    #+#             */
/*   Updated: 2024/02/02 15:35:33 by medalgic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philosopher
{
	u_int64_t		id;
	int				x_ate;
	int				left_fork_id;
	int				right_fork_id;
	u_int64_t		t_last_meal;
	struct s_rules	*rules;
	pthread_t		thread_id;
}					t_philosopher;

typedef struct s_rules
{
	int				nb_philo;
	u_int64_t		time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				all_ate;
	int				dieded;
	u_int64_t		first_timestamp;
	pthread_mutex_t	t_last_meal_check;
	pthread_mutex_t	x_ate_check;
	pthread_mutex_t	die_check;
	pthread_mutex_t	dieded_check;
	pthread_mutex_t	all_ate_check;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	die_write;
	t_philosopher	*philosophers;
}					t_rules;

int					write_error(char *str);
void				eat_control(t_rules *r, t_philosopher *p);
void				ft_free(t_rules *rules);
void				action_print(t_rules *rules, int id, char *string);
void				philo_eats(t_philosopher *philo);
int					parse(t_rules *rules, char **argv);
int					init_philosophers(t_rules *rules);
int					init_mutex(t_rules *rules);
int					ft_atoi(const char *str);
u_int64_t			timestamp(void);
u_int64_t			time_diff(u_int64_t past, u_int64_t pres);
void				smart_sleep(u_int64_t time, t_rules *rules);
int					launcher(t_rules *rules);
void				exit_launcher(t_rules *rules, t_philosopher *philos);
int					destroy_mutex(t_rules *rules);
void				chose_mutex(t_rules *rules, int x);
void				death_checker(t_rules *r, t_philosopher *p, int i, int j);
#endif
