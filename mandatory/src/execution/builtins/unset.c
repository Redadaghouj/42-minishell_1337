/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:23:35 by rben-ais          #+#    #+#             */
/*   Updated: 2025/08/06 19:55:44 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void remove_env_variable(char *key, t_env **env)
{
    t_env   *current;
    t_env   *prev;

    if (!env || !*env)
        return;
    current = *env;
    prev = NULL;
    while (current)
    {
        if (!ft_strcmp(current->key, key))
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            free(current->key);
            if (current->value)
                free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

static void unset_variable(char *arg, t_env **env)
{
    if (is_valid_identifier(arg))
        remove_env_variable(arg, env);
    else
        printf("Shellnobyl: unset: `%s': not a valid identifier\n", arg);
}

void	ft_unset(char **args, t_env **env)
{
    int i;

    if (!args || !env || !*env)
        return;
    if (!args[1])
        return;
    i = 1;
    while (args[i])
    {
        unset_variable(args[i], env);
        i++;
    }
}