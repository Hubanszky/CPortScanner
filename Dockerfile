FROM gcc:5.8

COPY ./port_scanner.c  .

RUN gcc -o port_scanner ./port_scanner.c