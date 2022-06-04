FROM debian

RUN apt update
RUN apt install -y gcc
RUN apt install -y gcc-multilib

COPY ./c_file.c .
COPY ./asm_file.s .

RUN gcc -m32 -no-pie ./asm_file.s -o ./asm_prog
RUN gcc ./c_file.c -o ./c_prog

