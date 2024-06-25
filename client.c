/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:52:06 by ineimatu          #+#    #+#             */
/*   Updated: 2024/06/25 18:57:41 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	salto(int pid)
{
	int bit;

	bit = 0;
	while (bit < 8)
	{
		kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

void	str_handl(int pid, char *string)
{
	size_t	i;
	int	bit;

	i = 0;
	bit = 0;
	while (string[i] != '\0')
	{
		bit = 0;
		while (bit < 8)
		{
			if (string[i] & (1 << bit))
			{
				if (kill(pid, SIGUSR1) == -1)
				{
					write (2, "Error!\n", 7);
					exit(EXIT_FAILURE);
				}
				usleep(100);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
				{
					write (2, "Error!\n", 7);
					exit(EXIT_FAILURE);
				}
				usleep(100);
			}
			bit++;
		}
		i++;
	}
}

int	check_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int pid;
	if (argc != 3 || check_digit(argv[1]) == 0 || ft_strlen(argv[2]) == 0)
		return (write(2, "incorrect arguments\n", 20));
	else
	{
		pid = ft_atoi(argv[1]);
		str_handl(pid, argv[2]);
		salto(pid);
	}
	exit(0);
	return (0);
}
