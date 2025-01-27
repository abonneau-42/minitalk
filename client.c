/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:55:59 by abonneau          #+#    #+#             */
/*   Updated: 2025/01/27 19:14:23 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void	send_bit(pid_t receiver_pid, int bit) {
    if (bit)
        kill(receiver_pid, SIGUSR1);
    else
        kill(receiver_pid, SIGUSR2);

    usleep(10000);
}

int	ft_strlen(char *str)
{
	int i;

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
	bit = 31;
	while (bit >= 0) {
        send_bit(receiver_pid, (message_size >> bit) & 1);
        bit--;
    }
	while (*message)
	{
		bit = 7;
		while (bit >= 0)
		{
			send_bit(receiver_pid, (*message >> bit) & 1);
			bit--;
		}
		message++;
	}
    bit = 8;
    while (bit--) {
        send_bit(receiver_pid, 0);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Utilisation : %s <PID_du_receveur> <message>\n", argv[0]);
        return 1;
    }

    pid_t receiver_pid = atoi(argv[1]);
    char *message = argv[2];

    printf("Envoi du message au PID %d...\n", receiver_pid);
    send_message(receiver_pid, message);

    return 0;
}