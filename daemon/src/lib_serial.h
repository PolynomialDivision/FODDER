#ifndef __LIB_SERIAL_H
#define __LIB_SERIAL_H

#include <errno.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int set_interface_attribs(int fd, int speed);
void set_mincount(int fd, int mcount);
int setup_serial_port(char* portname, int fd);

#endif