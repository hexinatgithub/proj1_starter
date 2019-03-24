FROM ubuntu

RUN apt-get update && \
    apt-get install -y valgrind gcc make && \
    apt-get install -y libcunit1 libcunit1-doc libcunit1-dev