/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghazi <aghazi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:24:13 by aghazi            #+#    #+#             */
/*   Updated: 2022/03/31 13:29:34 by aghazi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_isalpha(char *s)
{
	int	k;

	k = 0;
	while (s[k])
	{
		if ((s[k] >= 'A' && s[k] <= 'Z') || (s[k] >= 'a' && s[k] <= 'z'))
		{
			write(1, "invalid PID", 11);
			exit(1);
		}
		k++;
	}
}

int	ft_atoi(const char *str)
{
	int				i;
	int				pon;
	unsigned int	num;

	num = 0;
	i = 0;
	pon = 1;
	if (!str)
	{
		return (0);
	}
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		pon *= 1 - 2 * (str[i++] == '-');
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	if (num > 2147483648 && pon == -1)
		return (0);
	else if (num > 2147483647 && pon == 1)
		return (-1);
	return ((int)(pon * num));
}

void	ft_print_error(void)
{
	write (1, "invalid PID", 11);
	exit(1);
}

void	ft_send_pid(char c, int pid)
{
	int		e;
	int		j;

	e = 7;
	while (e >= 0)
	{
		j = c >> e & 1;
		if (j)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_print_error();
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_print_error();
		}
		--e;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	j;
	int	k;
	int	at;

	j = 0;
	k = 0;
	if (argc != 3)
	{
		write(1, "invalid argument Usage: ./client PID string-to-send\n", 52);
		return (1);
	}
	ft_isalpha(argv[1]);
	at = ft_atoi(argv[1]);
	if (argc == 3)
	{
		while (argv[2][k])
		{
			ft_send_pid(argv[2][k], at);
			k++;
		}
	}
	return (0);
}
