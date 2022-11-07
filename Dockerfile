FROM ubuntu
ENV DEBIAN_FRONTEND noninteractive
WORKDIR Matrix
COPY . .
RUN apt -y update && \
    apt -y install python3 cppcheck clang-tidy make git lcov \
    gcovr python3-pip libgtest-dev build-essential gcc g++ gdb clang cmake valgrind && \
    pip3 install cpplint && \
    pip3 install --upgrade cmake && \
    apt clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*