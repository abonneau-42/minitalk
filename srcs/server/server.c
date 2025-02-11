/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/11 14:43:57 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	add_bit_to_byte(int signo, t_server_state *state)
{
	if (signo == SIGUSR1)
		state->current_byte = (state->current_byte << 1) | 1;
	else if (signo == SIGUSR2)
		state->current_byte = (state->current_byte << 1) | 0;
	state->bit_count++;
}

void	print_message(t_server_state *state)
{
	write(1, state->message, state->message_size);
	write(1, "\n", 1);
	free(state->message);
	state->is_init = FALSE;
}

void	read_byte_message_size(t_server_state *state)
{
	state->message_size = (state->message_size << 8) | state->current_byte;
	if (state->bit_count / 8 == 4)
	{
		state->message = malloc(state->message_size + 1);
		if (!state->message)
			exit(EXIT_FAILURE);
	}
	state->current_byte = 0;
}

void	handle_signal(int signo, siginfo_t *info, void *context)
{
	static t_server_state	state = {.is_init = FALSE};

	if (!state.is_init)
		state = (t_server_state){.is_init = TRUE, .bit_count = 0,
			.sender_pid = 0, .current_byte = 0,
			.message = NULL, .message_size = 0};
	(void)context;
	if (state.sender_pid == 0)
		state.sender_pid = info->si_pid;
	add_bit_to_byte(signo, &state);
	if (state.bit_count % 8 == 0)
	{
		if (state.bit_count / 8 <= 4)
			read_byte_message_size(&state);
		else
		{
			state.message[state.bit_count / 8 - 5] = (char)state.current_byte;
			if (state.message[state.bit_count / 8 - 5] == '\0')
				print_message(&state);
		}
		state.current_byte = 0;
	}
	kill(state.sender_pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	server_message(PRINT_PID, getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
