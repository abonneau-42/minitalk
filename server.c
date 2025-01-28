/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/01/28 18:25:59 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server_state state = {.bit_count=0, .current_byte=0, .message_size=0, .sender_pid=0};

void handle_signal(int signo, siginfo_t *info, void *context)
{
    (void)context;
    if (state.sender_pid == 0) // On enregistre le PID de l'émetteur
        state.sender_pid = info->si_pid;

    if (signo == SIGUSR1)
        state.current_byte = (state.current_byte << 1) | 1;
    else if (signo == SIGUSR2)
        state.current_byte = (state.current_byte << 1) | 0;
    
    state.bit_count++;

    if (state.bit_count % 8 == 0) { // Un octet complet reçu
        if (state.bit_count / 8 <= 4) { // Récupération de la taille du message
            state.message_size = (state.message_size << 8) | state.current_byte;
            if (state.bit_count / 8 == 4) {
                state.message = malloc(state.message_size + 1);
                if (!state.message)
                    exit(EXIT_FAILURE);
            }
        } else { // Récupération du message
            state.message[state.bit_count / 8 - 5] = (char)state.current_byte;
            if (state.message[state.bit_count / 8 - 5] == '\0') {
                write(1, state.message, state.message_size);
                write(1, "\n", 1);
				if (state.message) {
					free(state.message);
					state.message = NULL;
				}
				state.bit_count = 0;
				state.current_byte = 0;
				state.message_size = 0;
            }
        }
        state.current_byte = 0;
    }

    // Envoyer un ACK au client
    kill(state.sender_pid, SIGUSR1);

	if (state.bit_count == 0) {
    	state.sender_pid = 0;
	}
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    printf("Serveur PID: %d\n", getpid());

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1) pause();
    return 0;
}
