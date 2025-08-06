#include "../../../include/minishell.h"


char	*ft_jm3_str(char *s1, char *s2, char *s3)
{
    char	*res1;
    char    *res2;

    if (!s1 || !s2 || !s3)
        return (NULL);
    res2 = NULL;
    res1 = rb_strjoin(s1, s2);
    res2 = rb_strjoin(res2, s3);
    free(res1);
    return (res2);
}

void    ft_cd(char **args, t_env **env)
{
    char    *home;
    char    *error_str;

    if (!args[1])
    {
        home = rb_get_env_value("HOME", *env);
        if (!home || chdir(home))
            perror("Shellnobyl: cd:");
    }
    else if (args[2])
        perror("Shellnobyl: cd: too many arguments");
    else if (chdir(args[1]))
    {
        error_str = ft_jm3_str("Shellnobyl: cd: ", args[1], ": No such file or directory");
        perror(error_str);
        free(error_str);
    }

}
