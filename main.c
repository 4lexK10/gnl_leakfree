#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = 0;

    fd = open("test", O_RDONLY);
    char * str = get_next_line(fd);
    printf("%s", str);
    str = get_next_line(fd);
    printf("%s", str);
    while (str)
    {
        str = get_next_line(fd);
        printf("%s", str);
    }
    close(fd);

    return (0);
}