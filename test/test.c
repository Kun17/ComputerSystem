#include <stdio.h>
#include <stdint.h>

int
main(void){
    uint16_t var_u16 = 0x0001;
    int a[2] = {1, 2};
    printf("%d\n", a[var_u16]);
    return (0);
}