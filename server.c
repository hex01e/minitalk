/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:45:49 by houmanso          #+#    #+#             */
/*   Updated: 2023/01/20 11:00:37 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>
#include <stdio.h>

typedef struct s_vars
{
	unsigned char	byte;
	int				pid;
	unsigned char	i;
}	t_vars;

void	get_bits(int sig, siginfo_t *si_info, void *v)
{
	static t_vars	info;

	(void)v;
	if (si_info->si_pid != info.pid)
	{
		info.i = 0;
		info.byte = 0;
		info.pid = si_info->si_pid;
	}
	if (sig == SIGUSR1)
		info.byte = info.byte << 1 | 1;
	else if (sig == SIGUSR2)
		info.byte = info.byte << 1 | 0;
	info.i++;
	if (info.i == 8)
	{
		ft_putchar_fd(info.byte, 1);
		info.byte = 0;
		info.i = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_bits;
	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
