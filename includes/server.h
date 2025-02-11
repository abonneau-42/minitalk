/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:40:26 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/11 12:31:48 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_server_response
{
	PRINT_PID = 0,
	COM_LOST = 1,
}	t_server_response;

typedef struct s_server_state
{
	int		bit_count;
	int		sender_pid;
	int		current_byte;
	char	*message;
	size_t	message_size;
	t_bool	is_init;
}	t_server_state;

void	ft_putchar(char c);
void	ft_putnbr(unsigned int n);
void	server_message(t_server_response message_type, pid_t receiver_pid);

#endif
