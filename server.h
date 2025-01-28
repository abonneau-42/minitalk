/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:40:26 by abonneau          #+#    #+#             */
/*   Updated: 2025/01/28 18:24:07 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

typedef struct s_server_state {
    int		bit_count;
    char	*message;
    int		current_byte;
	size_t	message_size;
    int     sender_pid;
}	t_server_state;

#endif