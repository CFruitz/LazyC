#include <stdio.h>
#include <ctype.h>
#include "include/scstring.h"
#include "include/scio.h"

int main(void) {
    SCS *name = SCS_new();
    scio_scan_scs(name);
    if (SCS_endswith(name, "Alonso") == 0) printf("YES\n");
    if (SCS_cmp_str(name, "Daniel Alonso") == 0) printf("YES\n");
    if (SCS_cmp(name, SCS_from("Daniel Alonso")) == 0) printf("YES\n");

    printf("%s\n", name->data);
    SCS_free(name);
}