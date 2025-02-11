/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:55:59 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/11 16:02:19 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_ack_received = 0;

void	ack_handler(int signo)
{
	(void)signo;
	g_ack_received = 1;
}

void	send_bit(pid_t receiver_pid, int bit)
{
	static t_bool	in_progress = FALSE;
	unsigned int	elapsed;

	elapsed = 0;
	if (bit)
		kill(receiver_pid, SIGUSR1);
	else
		kill(receiver_pid, SIGUSR2);
	while (!g_ack_received)
	{
		if (elapsed++ < 1000)
			usleep(1000);
		else
		{
			client_message(COM_LOST, receiver_pid);
			exit(1);
		}
	}
	g_ack_received = 0;
	if (!in_progress)
	{
		client_message(COM_ESTABLISHED, receiver_pid);
		in_progress = TRUE;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	send_message(pid_t receiver_pid, const char *message)
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
	pid_t				receiver_pid;

	if (argc < 3)
	{
		write(STDOUT_FILENO, "Usage: ./client [PID] [message]\n", 32);
		return (1);
	}
	receiver_pid = atoi(argv[1]);
	signal(SIGUSR1, ack_handler);
	send_message(receiver_pid, argv[2]);
	write(STDOUT_FILENO, "Message sent successfully.\n", 27);
	return (0);
}
