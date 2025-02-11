/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:42:52 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/11 12:12:24 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_message(t_server_response message_type, pid_t receiver_pid)
{
	if (message_type == PRINT_PID)
	{
		write(STDOUT_FILENO, "The server has started up with the PID ", 39);
		ft_putnbr(receiver_pid);
		write(STDOUT_FILENO, ".\n", 2);
	}
}
