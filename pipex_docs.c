{---------------------------------@PIPEX------------------------------------}
| 1) pipe & Fork first then check                                           |
|    'nbr of commands == nbr of pipes - 1 == nbr of forks == '              |
|                                                                           |
| 2) Method for all commnds                                                 |
|    $first  :   if ("here_doc")                                            |
|                {                                                          |
|                    while (1)                                              |
|                        read from 0 until "buff == limiter" || 'CONTROL D' |
|                    exit (0);                                              |
|                }                                                          |
|                else if ("there is no infile" || "cant read from infile")  |
|                    'ignore first command'                                 |
|                else                                                       |
|                    do $first command                                      |
|                                                                           |
|    $others :   do $other commands except $last command                    |
|                                                                           |
|    $last   :   if ("cant write to outfile" || "$last command is wrong")   |
|                    return 'stderr'                                        |
|                else                                                       |
|                    create outfile && do $last command                     |
{---------------------------------------------------------------------------}
