/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medalgic <medalgic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:10:29 by medalgic          #+#    #+#             */
/*   Updated: 2024/02/02 13:10:31 by medalgic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			tmp;

	i = 0;
	tmp = 0;
	while (str[i] <= 32 && str[i + 1])
		i++;
	while (str[i] == '+')
		i++;
	if (str[i] == '-' || str[i] == 0)
		return (-1);
	tmp = i;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	i = 0;
	while (str[tmp] >= '0' && str[tmp] <= '9' && str[tmp])
	{
		i = (i * 10) + (str[tmp] - '0');
		tmp++;
	}
	return (i);
}

u_int64_t	timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, (void *)0) == -1)
		return (1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

u_int64_t	time_diff(u_int64_t past, u_int64_t pres)
{
	return (pres - past);
}

void	smart_sleep(u_int64_t time, t_rules *rules)
{
	u_int64_t	i;

	i = timestamp();
	while (1)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		pthread_mutex_lock(&(rules->dieded_check));
		if (rules->dieded)
		{
			pthread_mutex_unlock(&(rules->dieded_check));
			break ;
		}
		pthread_mutex_unlock(&(rules->dieded_check));
		usleep(50);
	}
}
