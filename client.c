/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:38:23 by zzehra            #+#    #+#             */
/*   Updated: 2025/10/31 12:17:33 by ztaskula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

void	send_message(int pid, char *argv)
{
	int				len;
	int				i;
	int				j;
	unsigned int	bit;

	i = 0;
	len = ft_strlen(argv);
	while (i < len)
	{
		j = 0;
		while (j < 8)
		{
			bit = (argv[i] >> j) & 1;
			if (bit == 0)
				kill(pid, SIGUSR1);
			else if (bit == 1)
				kill(pid, SIGUSR2);
			j++;
			usleep(500);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		exit (0);
	pid = ft_atoi(argv[1]);
	send_message(pid, argv[2]);
	kill(pid, '\0');
	return (0);
}
