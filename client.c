/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:55:59 by abonneau          #+#    #+#             */
/*   Updated: 2025/01/28 19:31:51 by abonneau         ###   ########.fr       */
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
	if (bit)
		kill(receiver_pid, SIGUSR1);
	else
		kill(receiver_pid, SIGUSR2);
	while (!g_ack_received)
		;
	g_ack_received = 0;
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
	char				*message;
	struct sigaction	sa;

	if (argc < 3)
	{
		printf("Utilisation : %s <PID_du_serveur> <message>\n", argv[0]);
		return (1);
	}
	receiver_pid = atoi(argv[1]);
	message = argv[2];
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	printf("Envoi du message au PID %d...\n", receiver_pid);
	send_message(receiver_pid, message);
	return (0);
}
