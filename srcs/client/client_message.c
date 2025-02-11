/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:41:28 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/11 12:34:34 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_message(t_client_response message_type, pid_t receiver_pid)
{
	if (message_type == COM_ESTABLISHED)
	{
		write(STDOUT_FILENO,
			"Communication established, sending message to PID ", 50);
		ft_putnbr(receiver_pid);
		write(STDOUT_FILENO, " in progress...\n", 16);
	}
	else if (message_type == COM_LOST)
	{
		write(STDOUT_FILENO, "The PID ", 8);
		ft_putnbr(receiver_pid);
		write(STDOUT_FILENO, " does not respond.\n", 19);
	}
}
