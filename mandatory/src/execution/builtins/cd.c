#include "../../../include/minishell.h"

void    ft_cd(t_shell *shell, char **args)
{
    char    *home;

	shell->exit_status = EXIT_SUCCESS;
    if (!args[1])
    {
        home = get_env_value(ft_strdup("HOME"), shell->env);
        if (!home || chdir(home))
		{
			shell->exit_status = EXIT_FAILURE;
            perror("Shellnobyl: cd");
		}
    }
    else if (args[2])
	{
		shell->exit_status = EXIT_FAILURE;
        printf("Shellnobyl: cd: too many arguments\n");
	}
    else if (chdir(args[1]))
    {
		shell->exit_status = EXIT_FAILURE;
        printf("Shellnobyl: cd: %s: No such file or directory\n", args[1]);
    }
}
