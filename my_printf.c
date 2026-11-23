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
int my_put_unsigned(unsigned int n)
{
    int count = 0;
    if(n>=10)
        count += my_put_unsigned(n/10);
    count += my_putchar((n%10) + '0');
    return count;
}
int my_put_signed(int n){
    int count = 0;
    long num =n;
    if(num < 0){
        count += my_putchar('-');
        num = -num;
    }
    count += my_put_unsigned(num);
    return(count);
}

int my_put_octal(unsigned int n)
{
    int count =0;
    if(n>=8){
        count += my_put_octal(n/8);
    }
    count += my_putchar((n%8)+ '0');
    return (count);
}

int my_put_hex(unsigned long n, char *hex){
    int count=0;
    if(n>=16){
        count += my_put_hex(n/16,hex);
    }
    count += my_putchar(hex[n%16]);
    return count;
}
int my_put_ptr(void *ptr)
{
    int count = 0;

    if (!ptr)
        return (my_putstr("(nil)"));
    count += my_putstr("0x");
    count += my_put_hex((unsigned long)ptr, "0123456789abcdef");
    return (count);
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
    if (spec == 'u')
        return (my_put_unsigned(va_arg(args, unsigned int)));
    if (spec == 'd')
        return (my_put_signed(va_arg(args, int)));
    if (spec == 'o')
        return (my_put_octal(va_arg(args, unsigned int)));
    if (spec == 'x')
        return (my_put_hex(va_arg(args, unsigned int), "0123456789ABCDEF"));
    if (spec == 'p')
        return (my_put_ptr(va_arg(args, void *)));
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