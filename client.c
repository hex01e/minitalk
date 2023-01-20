/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:16:39 by houmanso          #+#    #+#             */
/*   Updated: 2023/01/20 11:36:50 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>

void	ft_error(char *s)
{
	ft_putstr_fd(s, 2);
	exit(1);
}

void	send_byte(unsigned char byte, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		usleep(910);
		if ((byte >> i) % 2 == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error("Cheak the PID!.\nusage: ./client PID message");
		}
		else if (((byte >> i) % 2) == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error("Cheak the PID!.\nusage: ./client PID message");
		}
		i--;
	}
}

int	main(int argc, char const *argv[])
{
	int	i;
	int	pid;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
			ft_error("Cheak the PID!.\nusage: ./client PID message");
		while (argv[2][i])
			send_byte(argv[2][i++], ft_atoi(argv[1]));
	}
	else
		ft_error("usage: ./client PID message");
	return (0);
}
