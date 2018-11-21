#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>

#include <util.h>

//-----------------------------------------------------------------------------
int main(int argc, char *argv [])
{
    char * port = NULL;
    char * port2= NULL;

    // parse comand line
    if (argc != 5)
    {
        fprintf(stderr, "Invalid usage: reader -p port_name\n");
        exit(EXIT_FAILURE);
    }

    char * options = "p:j:";
    int option;
    while((option = getopt(argc, argv, options)) != -1)
    {
        switch(option)
        {
                case 'p':
                    port = optarg; 
                    break;

                case 'j':
                    port2 = optarg;
                    break;

                case '?':
                    fprintf(stderr, "Invalid option %c\n", optopt);
                    exit(EXIT_FAILURE);
            }
        }
    // open serial port
    int fd = open(port, O_RDWR | O_NOCTTY);
    int fd2 = open(port2, O_RDWR | O_NOCTTY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    tcflush(fd, TCIOFLUSH);
   
    if (fd2 == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    tcflush(fd2, TCIOFLUSH);

    // read port
    char buff[50];
    char buff2[50];
    fd_set fdset;
    fd_set fd2set;

    while(1)
    {
        bzero(buff, sizeof(buff));
        bzero(buff2, sizeof(buff2));

        FD_ZERO(&fdset);
        FD_SET(fd, &fdset);
        select(fd+1, &fdset, NULL, NULL, NULL);

        FD_ZERO(&fd2set);
        FD_SET(fd2, &fd2set);

        select(fd2+1, &fd2set, NULL, NULL, NULL);

        if (FD_ISSET(fd, &fdset))
        {
            int bytes = read (fd, buff, sizeof(buff));
            int bytes2= read (fd2, buff2, sizeof(buff2));
            if (bytes > 0 && bytes2>0)
            {
                printf("%s, %s\n", buff, buff2);
                fflush(stdout);
            }
        }

    }

    // close serial port
    close(fd);

    exit(EXIT_SUCCESS);
}
