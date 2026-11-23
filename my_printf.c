#include <unistd.h>
// #include <stdio.h>
#include <stdarg.h>
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

int handle_specifier(char spec, va_list args){
    if(spec == 'c'){
        return my_putchar(va_arg(args,int));
    }
    if(spec == 's'){
        return my_putstr(va_arg(args, char *));
    }
    if(spec == '%')
        return my_putchar('%');
    return my_putchar('%') + my_putchar(spec);

}   

int my_printf(char * restrict format, ...){
    if(!format)
        return -1;

    va_list args;
    int total_print=0;

    va_start(args, format);
    for(int i=0; format[i] != '\0'; i++)
    {
        if(format[i] == '%' && format[i+1]!= '\0'){
           total_print+= handle_specifier(format[i+1], args);
           i++;
        }
        else{
            total_print += my_putchar(format[i]);
        }
    }
    va_end(args);
    return total_print;
}