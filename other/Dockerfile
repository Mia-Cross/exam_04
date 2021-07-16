FROM alpine:latest

COPY microshell_v1 .

RUN apk add g++ make gcc && make

CMD ./microshell /usr/bin/echo " please work normally | please... ; i beg you"  \
    && tail -F /dev/null
# CMD gcc -Wall -Wextra -Werror *.c && tail -F /dev/null