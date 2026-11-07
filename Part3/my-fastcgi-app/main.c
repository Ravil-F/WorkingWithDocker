#include <fcgi_stdio.h>
#include <stlib.h>

int main(){
    while (FCGI_Accept() >= 0)
    {
        printf("Content-type: text/html\r\n"
                "Status: 200 OK\r\n"
                "\r\n"
                 "<html><body><h1>hello world</h1></body></html>");
    }
    
    return 0;
}