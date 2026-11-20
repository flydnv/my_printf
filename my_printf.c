#include <unistd.h>
#include <stdio.h>
int my_putchar(char c){
    return write(1, &c, 1);
}
int my_putstr(char *c){
    if(!c){
        return write(1,"(null)", 6);
    }
    int len =0;
    while(c[len])
        len += my_putchar(c[len]);
    return len;
}

int main(void)
{
    int len1 = my_putstr("Salam Qwasar!\n");
    int len2 = my_putstr(NULL);

    my_putchar('\n');
    printf("Yazilan simvol sayi: %d ve %d\n", len1, len2);
    return (0);
}