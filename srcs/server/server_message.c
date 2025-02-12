/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:42:52 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/12 14:51:37 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	server_message_init(pid_t receiver_pid)
{
	write(STDOUT_FILENO, "The server has started up with the PID ", 39);
	ft_putnbr(receiver_pid);
	write(STDOUT_FILENO, ".\n", 2);
}
