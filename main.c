/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medalgic <medalgic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:10:15 by medalgic          #+#    #+#             */
/*   Updated: 2024/02/02 13:10:16 by medalgic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (!(argc == 5 || argc == 6))
		return (write_error("Invalid Argument"), 0);
	if (parse(&rules, argv))
		return (write_error("Mutex Start Error"), 0);
	if (init_philosophers(&rules))
		return (write_error("Philosophers Init Error"), 0);
	if (init_mutex(&rules))
		return (write_error("Mutex Init Error"), 0);
	if (launcher(&rules))
		return (write_error("Thread Create Error"), 0);
}
