#include <stdio.h>
#include "include/scstring.h"

int main(void) {
    SCS *name = SCS_from("Daniel Alonso");
    if (SCS_endswith(name, "Alonso") == 0) printf("YES\n");
    if (SCS_startswith(name, "Daniel") != 0) printf("YES\n");
    if (SCS_endswith(name, "AlonsO") == 0) printf("YES\n");

    printf("%s\n", name->data);
    SCS_free(name);
}