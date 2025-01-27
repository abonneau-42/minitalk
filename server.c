/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/01/27 20:00:38 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server_state state = {.bit_count=0, .current_byte=0, .message_size=0};

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

void handle_signal(int signo)
{
    if (signo == SIGUSR1)
        state.current_byte = (state.current_byte << 1) | 1;  // Décale et ajoute 1
    else if (signo == SIGUSR2)
        state.current_byte = (state.current_byte << 1) | 0;  // Décale et ajoute 0
    state.bit_count++;
    if (state.bit_count % 8 == 0) {  // Un caractère complet reçu
		if (state.bit_count / 8 <= 4)
		{
			state.message_size = state.message_size << 8 | state.current_byte;
			if (state.bit_count / 8 == 4)
			{
				state.message = malloc(sizeof(char) * (state.message_size + 1));
				if (state.message == NULL)
                	exit(EXIT_FAILURE);
			}
		}
		else
		{
			state.message[state.bit_count / 8 - 5] = (char)state.current_byte;
			state.current_byte = 0;

			if (state.message[state.bit_count / 8 - 5] == '\0')
			{
				write(1, state.message, state.message_size);
				ft_putchar('\n');
                free(state.message);
                state.message = NULL;
                state.bit_count = 0;
                state.message_size = 0;
			}
		}
    }
}

int main() {
	ft_putnbr(getpid());
	ft_putchar('\n');

    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while (1) pause();  // Attendre un signal
    return 0;
}