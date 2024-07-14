ctrl c exit state : fixed

export key{anything except alpha or = or _}+=value shouldnt work : fixed

limiter state should change after joining them : the way to fix this is to fill the new variable t_data in each file/limiter
and then expand the data after executing the commands leading to it then join them all to get the proper limiter/filename

reset the in and out fds between the and/or commands : fixed

^\ should return 131 in child process fixed

fork every pipe then execute the pipes to get the correct exit state : soon to be fixed

expand * in execution after the normal expand : make your own match function and you should be good to go


// Function to check if a string matches a wildcard pattern
int wildcard_match(const char *pattern, const char *str)
{
    while (*pattern)
    {
        if (*pattern == '*')
        {
            pattern++;
            if (!*pattern)
                return 1;
            while (*str)
            {
                if (wildcard_match(pattern, str))
                    return 1;
                str++;
            }
            return 0;
        }
        else if (*pattern == *str)
        {
            pattern++;
            str++;
        }
        else
            return 0;
    }
    return !*str;
}
