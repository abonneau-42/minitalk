/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:55:59 by abonneau          #+#    #+#             */
/*   Updated: 2025/01/28 18:25:46 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t ack_received = 0;

void ack_handler(int signo) {
    (void)signo;
    ack_received = 1;
}

void send_bit(pid_t receiver_pid, int bit) {
    if (bit)
        kill(receiver_pid, SIGUSR1);
    else
        kill(receiver_pid, SIGUSR2);

    // Attendre l'ACK du serveur
    while (!ack_received);
    ack_received = 0;
}

int	ft_strlen(char *str) {
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void send_message(pid_t receiver_pid, const char *message) {
    int bit;
    size_t message_size = ft_strlen((char *)message);

    // Envoyer la taille du message (32 bits)
    for (bit = 31; bit >= 0; bit--) {
        send_bit(receiver_pid, (message_size >> bit) & 1);
    }

    // Envoyer le message caractère par caractère
    while (*message) {
        for (bit = 7; bit >= 0; bit--) {
            send_bit(receiver_pid, (*message >> bit) & 1);
        }
        message++;
    }

    // Envoyer un octet NULL pour marquer la fin du message
    for (bit = 7; bit >= 0; bit--) {
        send_bit(receiver_pid, 0);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Utilisation : %s <PID_du_serveur> <message>\n", argv[0]);
        return 1;
    }

    pid_t receiver_pid = atoi(argv[1]);
    char *message = argv[2];

    // Capturer le signal d'ACK du serveur
    struct sigaction sa;
    sa.sa_handler = ack_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Envoi du message au PID %d...\n", receiver_pid);
    send_message(receiver_pid, message);

    return 0;
}
