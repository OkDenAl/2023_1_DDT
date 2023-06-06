FROM ubuntu:latest

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update -y
RUN apt install -y gcc
RUN apt install -y libpqxx-dev 
RUN apt install -y clang-tidy
RUN apt-get install -y wget
RUN apt install -y g++
RUN apt install -y cmake

RUN wget https://github.com/jtv/libpqxx/archive/refs/tags/7.7.5.tar.gz
RUN tar -zxvf 7.7.5.tar.gz
WORKDIR libpqxx-7.7.5
RUN ./configure CXXFLAGS=-std=c++17 --disable-dependency-tracking
RUN make
RUN make install

RUN apt install -y python3-pip
RUN apt install -y cppcheck
RUN apt-get update
RUN apt install -y nlohmann-json3-dev
RUN apt install -y git
RUN apt-get update
RUN apt install -y default-jre
RUN apt -y install curl

RUN pwd
WORKDIR /usr/local/lib
RUN curl -O https://www.antlr.org/download/antlr-4.12.0-complete.jar

RUN apt install -y xvfb
RUN pip install gcovr
RUN pip install cpplint
 
 
RUN git clone https://github.com/google/googletest.git -b release-1.11.0 
WORKDIR googletest/build 
RUN cmake .. -DBUILD_GMOCK=ON 
RUN make 
RUN make install

RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz
RUN tar xvf boost_1_82_0.tar.gz
WORKDIR boost_1_82_0
RUN ./bootstrap.sh --prefix=/usr/
RUN ./b2 install

RUN apt install -y clang-format

WORKDIR /project 
 
COPY . .

EXPOSE 8080