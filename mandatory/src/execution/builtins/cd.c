#include "../../../include/execution.h"

char	*ft_jm3_str(char *s1, char *s2, char *s3)
{
    char	*res1;
    char    *res2;

    if (!s1 || !s2 || !s3)
        return (NULL);
    res2 = NULL;
    res1 = ft_strjoin(s1, s2);
    res2 = ft_strjoin(res2, s3);
    free(res1);
    return (res2);
}

void    ft_cd(char **arv, t_env *env)
{
    char    *home;
    char    *error_str;

    if (!arv[1])
    {
        home = get_env_value("HOME", env);
        if (!home || chdir(home))
            perror("Shellnobyl: cd:");
    }
    else if (arv[2])
        perror("Shellnobyl: cd: too many arguments");
    else if (chdir(arv[1]))
    {
        error_str = ft_jm3_str("Shellnobyl: cd: ", arv[1], ": No such file or directory");
        perror(error_str);
        free(error_str);
    }

}

int main(int arc, char **arv)
{
    t_env	*env;
    
	env = init_env();
    if(!env)
        return(1);
    if(arc != 2)
        return (1);
    ft_pwd();
    ft_cd(arv, env);
    ft_pwd();
}