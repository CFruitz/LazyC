#pragma once

#include <stdio.h>
#include "scstring.h"

void scio_putchar(char c);
void scio_puts(char *s);
char scio_getchar(void);
void scio_gets(char *dst, int max);
int scio_scan_scs(SCS *s);
