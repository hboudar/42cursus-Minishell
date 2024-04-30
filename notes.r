definitions_to_help(char *args)
{

    if (args[0] == {'<' || '>' || '>>' || '<<'} && args[1])
    {
        if (args[0] == '<')
            args[1] == 'IN_FILE';
        else if (args[0] == '>')
            args[1] == 'OUT_FILE';
        else if (args[0] == '>>')
            args[1] == 'APPEND_FILE';
        else if (args[0] == '<<')
            args[1] == 'LIMETER';
    }
}

execution()
{
    if (NONE)
    {
        //CMD       :   builtins_cmd([echo "ok"])
                        none_builtins_cmd([ls])

        //PIPECMD   :   pipe_with_cmds([ls | wc -l])
                        pipe_with_here_doc([cat << limt | wc])

        //HERE_DOC  :   here_doc([cat << limt])
                        here_doc_with_pipe([cat << limit | wc])
    }
    else if (OR)
    {
        if (!execution(prompt->left, env))
            execution(prompt->right, env);
    }
    else if (AND)
    {
        if (execution(prompt->left, env))
            execution(prompt->right, env);
}

//  cd with only a relative or absolute path. when no path is given, syntax error.


//  add a variable to (t_prompt) (char *env[]) & allociih fl main function.

//$?  :   return value of the last executed command.

// what about : 
typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

//intilize the exit_status to 0 in the main function.