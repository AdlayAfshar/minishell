#include <stdio.h>
#include <stdlib.h>

int ft_exit(int argc, char **argv)
{
    int exit_status = 0;

    if (argc > 2)
    {
        fprintf(stderr, "exit: too many arguments\n");
        return(1); // Indicate error due to too many arguments
    }
    if (argc == 2)
    {
        char *endptr;
        exit_status = strtol(argv[1], &endptr, 10); // strtol to convert string to long, base 10, handle errors, long int strol(const char *nptr, char **endptr, int base);
        if (*endptr != '\0')
        {
            fprintf(stderr, "exit: numeric argument required\n");
            exit_status = 255; // Set exit status to 255 for invalid argument
        }
    }
    exit(exit_status);
}

int main(int argc, char **argv)
{
    return ft_exit(argc, argv);
}