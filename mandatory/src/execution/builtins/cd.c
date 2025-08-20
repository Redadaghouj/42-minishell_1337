#include "../../../include/minishell.h"

void    ft_cd(char **args, t_env **env)
{
    char    *home;

    if (!args[1])
    {
        home = get_env_value(ft_strdup("HOME"), *env);
        if (!home || chdir(home))
            perror("Shellnobyl: cd:");
    }
    else if (args[2])
        perror("Shellnobyl: cd: too many arguments");
    else if (chdir(args[1]))
    {
        printf("Shellnobyl: cd: %s: No such file or directory\n", args[1]);
        
    }

}
