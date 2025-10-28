/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:38:16 by zzehra            #+#    #+#             */
/*   Updated: 2025/10/28 20:21:01 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>

void find_ascii(int sig)
{
    static int indx;
    int indx_tmp;
    static unsigned int ascii;
    unsigned int ascii_tmp;
    
    indx_tmp = indx;
    ascii_tmp = 1;
    if (sig == SIGUSR1)
    {
        indx++;
    }
    else if (sig == SIGUSR2)
    {
        while(indx_tmp--)
            ascii_tmp *= 2;
        ascii += ascii_tmp;
        indx++;
    }
    if(indx == 8)
    {
        write(1, &ascii, 1);
        ascii = 0;
        indx = 0;  
    }
}

int main()
{
    ft_printf("%d\n", getpid());
    
    signal(SIGUSR1, find_ascii);
    signal(SIGUSR2, find_ascii);
    while (1)
        pause();
    return 0;
}