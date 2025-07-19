/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:34:46 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/19 22:30:34 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "env.h"
# include "minishell.h"

void	execution(t_cmd *comand,t_env **env);
void	ft_echo(char **arv);
#endif