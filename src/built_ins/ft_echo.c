#include <stdio.h>
#include <string.h>
//#include "ft_printf/ft_printf.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int ft_echo(int argc, char **argv)
{
    int newline = 1; // By default, print newline
    int start_index = 1; // Start from the first argument
    
    // Check for -n option
    if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
    {
        newline = 0; // Do not print newline
        start_index = 2; // Skip the -n argument
    }
    int i = start_index;
    // Print the arguments
    while(i < argc)
    {
        printf("%s", argv[i]);
        if (i < argc - 1)
            printf(" "); // Print space between arguments
        i++;
    }
    if (newline)
        printf("\n"); // Print newline if required
    return(0);
}

int main(int argc, char **argv)
{
    return ft_echo(argc, argv);
}