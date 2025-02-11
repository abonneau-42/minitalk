/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:23:08 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/11 12:31:59 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

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

void	ft_putchar(char c);
void	ft_putnbr(unsigned int n);
void	client_message(t_client_response message_type, pid_t receiver_pid);

#endif