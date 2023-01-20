/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:30:08 by houmanso          #+#    #+#             */
/*   Updated: 2023/01/20 11:35:09 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>
#include <stdio.h>

typedef struct s_vars
{
	unsigned char	byte;
	unsigned char	bytes[4];
	unsigned char	i;
	unsigned char	j;
	int				nbyte;
	int				pid;
}	t_vars;

void	reset_all(t_vars *info, int pid)
{
	info->i = 0;
	info->j = 0;
	info->byte = 0;
	info->nbyte = 0;
	ft_bzero(info->bytes, 4);
	info->pid = pid;
}

void	check(t_vars *info, siginfo_t *si_info)
{
	int	k;

	if (info->nbyte == 0 && info->byte <= 0b01111111)
	{
		if (info->byte == '\0')
			kill(si_info->si_pid, SIGUSR1);
		ft_putchar_fd(info->byte, 1);
	}
	else if (info->nbyte == 0 && info->byte >= 0b11110000)
		info->nbyte = 4;
	else if (info->nbyte == 0 && info->byte >= 0b11100000)
		info->nbyte = 3;
	else if (info->nbyte == 0 && info->byte >= 0b11000000)
		info->nbyte = 2;
	if (info->j < info->nbyte)
		info->bytes[info->j++] = info->byte;
	if (info->j == info->nbyte)
	{
		k = 0;
		while (k < info->j)
			ft_putchar_fd(info->bytes[k++], 1);
		ft_bzero(info->bytes, 4);
		info->nbyte = 0;
		info->j = 0;
	}
}

void	get_bits(int sig, siginfo_t *si_info, void *v)
{
	static t_vars	info;

	(void)v;
	if (si_info->si_pid != info.pid)
		reset_all(&info, si_info->si_pid);
	if (sig == SIGUSR1)
		info.byte = info.byte << 1 | 1;
	else if (sig == SIGUSR2)
		info.byte = info.byte << 1 | 0;
	info.i++;
	if (info.i == 8)
	{
		check(&info, si_info);
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
