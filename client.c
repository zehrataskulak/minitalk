/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:38:23 by zzehra            #+#    #+#             */
/*   Updated: 2025/11/03 23:32:17 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

static volatile int	g_ack_received = 0;

void	check_ack(int sig)
{
	if (sig == SIGUSR1)
		g_ack_received = 1;
}

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
			g_ack_received = 0;
			bit = (argv[i] >> j) & 1;
			if (bit == 0)
				kill(pid, SIGUSR1);
			else if (bit == 1)
				kill(pid, SIGUSR2);
			usleep(100);
			while (!g_ack_received)
				pause();
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		exit (0);
	signal(SIGUSR1, check_ack);
	pid = ft_atoi(argv[1]);
	send_message(pid, argv[2]);
	return (0);
}
