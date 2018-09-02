FROM ubuntu:18.04

MAINTAINER Robin Degen version: 1.0

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get install -y tzdata && ln -fs /usr/share/zoneinfo/Europe/Amsterdam /etc/localtime && dpkg-reconfigure --frontend noninteractive tzdata

RUN apt-get install -y git clang cmake mono-devel git xorg-dev libglu1-mesa-dev

ENV CC clang
ENV CXX clang++

COPY . /aeon-engine
COPY .git /aeon-engine/.git

RUN cd /aeon-engine && ./bootstrap.sh
RUN cd /aeon-engine/build && make -j2
RUN cd /aeon-engine/build && ctest
