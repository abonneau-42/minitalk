/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:40:26 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/12 14:52:12 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_client_response
{
	COM_ESTABLISHED = 0,
	COM_LOST = 1,
}	t_client_response;

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
void	server_message_init(pid_t receiver_pid);
void	client_message(t_client_response message_type, pid_t receiver_pid);

#endif
