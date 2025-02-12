/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:55:59 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/12 14:46:25 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_bool	g_server_response = FALSE;

static void	signal_handler(int signo)
{
	(void)signo;
	g_server_response = TRUE;
}

static void	send_bit(pid_t receiver_pid, int bit)
{
	static t_bool	in_progress = FALSE;
	unsigned int	elapsed;

	elapsed = 0;
	if (bit)
		kill(receiver_pid, SIGUSR1);
	else
		kill(receiver_pid, SIGUSR2);
	while (!g_server_response)
	{
		if (elapsed++ < 1000)
			usleep(100);
		else
		{
			client_message(COM_LOST, receiver_pid);
			exit(1);
		}
	}
	g_server_response = FALSE;
	if (!in_progress)
	{
		client_message(COM_ESTABLISHED, receiver_pid);
		in_progress = TRUE;
	}
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	send_message(pid_t receiver_pid, const char *message)
{
	int		bit;
	size_t	message_size;

	message_size = ft_strlen((char *)message);
	bit = 32;
	while (--bit >= 0)
		send_bit(receiver_pid, (message_size >> bit) & 1);
	while (*message)
	{
		bit = 8;
		while (--bit >= 0)
			send_bit(receiver_pid, (*message >> bit) & 1);
		message++;
	}
	bit = 8;
	while (--bit >= 0)
		send_bit(receiver_pid, 0);
}

int	main(int argc, char *argv[])
{
	pid_t			receiver_pid;
	unsigned int	i;

	if (argc < 3 || !*argv[1])
	{
		write(STDOUT_FILENO, "Usage: ./client [PID] [message]\n", 32);
		return (1);
	}
	i = 0;
	receiver_pid = 0;
	while (argv[1][i])
	{
		if (!(argv[1][i] >= '0' && argv[1][i] <= '9'))
		{
			write(STDOUT_FILENO, "PID is not an integer.\n", 23);
			return (1);
		}
		receiver_pid = receiver_pid * 10 + argv[1][i++] - '0';
	}
	signal(SIGUSR1, signal_handler);
	send_message(receiver_pid, argv[2]);
	write(STDOUT_FILENO, "Message sent successfully.\n", 27);
	return (0);
}
