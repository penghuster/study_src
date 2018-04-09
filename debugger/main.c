int main(int argc, char** argv)
{
    pid_t child_pid;

    if(argc < 2)
    {
        fprintf(stderr, "Expected a program name as argument.\n");
        return -1;
    }

    child_pid = fork();
    if(0 == child_pid)
    {
        run_target(argv[1]);
    }
    else
    {
        run_debugger(child_pid);
    }
    else
    {
        perror("fork");
        return -1;
    }

    return 0;
}
