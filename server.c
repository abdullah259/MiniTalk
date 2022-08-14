/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghazi <aghazi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:03:07 by aghazi            #+#    #+#             */
/*   Updated: 2022/03/30 15:40:16 by aghazi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static int	absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	int		k;

	k = n <= 0;
	i = n;
	while (i)
	{
		i /= 10;
		k++;
	}
	ptr = malloc(k * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	if (n == 0)
		ptr[0] = '0';
	ptr[k] = '\0';
	if (n < 0)
		ptr[0] = '-';
	while (n != 0)
	{
		ptr[--k] = absolute(n % 10) + '0';
		n /= 10;
	}
	return (ptr);
}

void	ft_hansdleus1(int sig)
{
	static int	i;
	static char	j;

	if (sig == SIGUSR2)
	{
		j |= 1;
	}
	i++;
	if (i == 8)
	{
		write(1, &j, 1);
		i = 0;
		j = 0;
	}
	j = j << 1;
}

int	main(void)
{
	int		pid;
	int		i;
	char	*printpid;

	pid = getpid();
	i = 0;
	printpid = ft_itoa(pid);
	while (printpid[i])
		write(1, &printpid[i++], 1);
	write(1, "\n", 1);
	signal(SIGUSR1, &ft_hansdleus1);
	signal(SIGUSR2, &ft_hansdleus1);
	while (1)
		pause();
	return (0);
}
