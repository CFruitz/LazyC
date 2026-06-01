#include "scstring.h"
#include "scio.h"
#include <stdio.h>
#include <unistd.h>


void scio_putchar(char c) {
    write(1, &c, 1);
}

void scio_puts(char *s) {
    while (*s != '\0') {
        scio_putchar(*s++);
    }
}

char scio_getchar(void) {
    char c;
    read(0, &c, 1);
    return c;
}

void scio_gets(char *dst, int max) {
    int i = 0;
    int c;
    while (i <= max && (c = scio_getchar()) != '\n') {
       *(dst + i++) = c; 
    }
    *(dst + i) = '\0';
}

//======================

int scio_scan_scs(SCS *s) {
    SCS_clear(s);
    char c;
    while ((c = scio_getchar()) != '\n') {
        SCS_push_char(s, c);
    }
    return 0;
}


