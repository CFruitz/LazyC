#include <stdio.h>
#include "include/scstring.h"

int main(void) {
    SCS *name = SCS_from("AKU KAMU KAMU AKU AKU AKU KAMU KAMU AKU AKU KAMU");
    SCS_replace_all(name, "AKU", "(OK)", 3);
    printf("%s\n", name->data);
    SCS_free(name);
}