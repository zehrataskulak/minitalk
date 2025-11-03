/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:38:16 by zzehra            #+#    #+#             */
/*   Updated: 2025/11/03 23:35:31 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf/ft_printf.h"

void	find_ascii(int sig, siginfo_t *info, void *context)
{
	int					indx_tmp;
	static int			indx;
	unsigned int		ascii_tmp;
	static unsigned int	ascii;

	(void)context;
	indx_tmp = indx;
	ascii_tmp = 1;
	if (sig == SIGUSR1)
		indx++;
	else if (sig == SIGUSR2)
	{
		while (indx_tmp--)
			ascii_tmp *= 2;
		ascii += ascii_tmp;
		indx++;
	}
	if (indx == 8)
	{
		write(1, &ascii, 1);
		ascii = 0;
		indx = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = find_ascii;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("%d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
