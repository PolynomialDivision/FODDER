#include "lib_serial.h"

#define PPM25_LOW 2
#define PPM25_HIGH 3

#define PPM10_LOW 4
#define PPM10_HIGH 5

void convert_buf_dec(unsigned char* buf);

void convert_buf_dec(unsigned char* buf)
{

    int pm25_serial = buf[2] + (buf[3] << 8);

    int pm10_serial = buf[4] + (buf[5] << 8);



    //ppm25[3] = (signed) buf[PPM25_LOW];
    //ppm25[0] = '0';
    //ppm25[1] = 'x';
    //sprintf(ppm25[2], "%x", buf[PPM25_HIGH]);
    //ppm25[3] = (signed) buf[PPM25_LOW];
    //ppm25[4] = '\0';
    //printf("PP25 = %s\n", ppm25);
    //long ppm25_dec = strtol(ppm25, NULL, 16);
    float ppm25_dec =  pm25_serial / 10.0; //(((int)buf[PPM25_HIGH] * 256 ) + (int) buf[PPM25_LOW] ) / 10;


    //char ppm10[5];
    //ppm10[0] = '0';
    //ppm10[1] = 'x';
    //ppm10[2] = (signed) buf[PPM10_HIGH];
    //ppm10[3] = (signed) buf[PPM10_LOW];
    //ppm10[4] = '\0';
    //printf("PP10 = %s\n", ppm10);
    //long ppm10_dec = strtol(ppm10, NULL, 16);

    float ppm10_dec =  pm10_serial / 10.0; //(((int)buf[PPM10_HIGH] * 256 ) + (int) buf[PPM10_LOW] ) / 10;


    printf("Fine dust PPM25: %f\n", ppm25_dec);
    printf("Fine dust PPM10: %f\n", ppm10_dec);
}  

void set_mincount(int fd, int mcount)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error tcgetattr: %s\n", strerror(errno));
        return;
    }

    tty.c_cc[VMIN] = mcount ? 1 : 0;
    tty.c_cc[VTIME] = 5;        /* half second timer */

    if (tcsetattr(fd, TCSANOW, &tty) < 0)
        printf("Error tcsetattr: %s\n", strerror(errno));
}

int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int setup_serial_port(char* portname)
{
    int fd;

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }
    /*baudrate 115200, 8 bits, no parity, 1 stop bit */
    set_interface_attribs(fd, 9600);
    //set_mincount(fd, 0);                /* set to pure timed read */

    /* simple noncanonical input */
    do {
        unsigned char buf[12];
        int rdlen;

        rdlen = read(fd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
            unsigned char   *p;
            printf("Read %d:", rdlen);
            for (p = buf; rdlen-- > 0; p++)
            printf(" 0x%x", *p);
            printf("\n");
            
        } else if (rdlen < 0) {
            printf("Error from read: %d: %s\n", rdlen, strerror(errno));
        }
        convert_buf_dec(buf);

        /* repeat read to get full message */
    } while (1);
}