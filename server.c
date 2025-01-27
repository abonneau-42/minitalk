/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/01/27 19:13:31 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server_state state = {.bit_count=0, .current_byte=0, .message_size=0};

void handle_signal(int signo) {
	
	
    if (signo == SIGUSR1) {
        state.current_byte = (state.current_byte << 1) | 1;  // Décale et ajoute 1
    } else if (signo == SIGUSR2) {
        state.current_byte = (state.current_byte << 1) | 0;  // Décale et ajoute 0
    }

    state.bit_count++;

    if (state.bit_count % 8 == 0) {  // Un caractère complet reçu

		if (state.bit_count / 8 <= 4)
		{
			state.message_size = state.message_size << 8 | state.current_byte;
			if (state.bit_count / 8 == 4)
				state.message = malloc(sizeof(char) * (state.message_size + 1));
		}
		else
		{
			state.message[state.bit_count / 8 - 5] = (char)state.current_byte;
			state.current_byte = 0;

			if (state.message[state.bit_count / 8 - 5] == '\0') {
				printf("Message reçu : %s\n", state.message);
				state.bit_count = 0;
			}
		}
    }
}

int main() {
    printf("Récepteur en attente... (PID: %d)\n", getpid());

    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while (1) pause();  // Attendre un signal
    return 0;
}