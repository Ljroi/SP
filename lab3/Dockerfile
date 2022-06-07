FROM debian

RUN apt update
RUN apt install -y gcc
COPY ./c_file.c ./
RUN gcc ./c_file.c -o c_prog

CMD ./c_prog
