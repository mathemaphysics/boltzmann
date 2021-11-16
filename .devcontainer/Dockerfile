FROM ubuntu:focal

ARG DEVUSER devuser

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get -y update \
 && apt-get -y install --no-install-recommends build-essential \
 					       g++ \
					       gdb \
 					       cmake \
					       git \
					       openssh-client \
					       wget \
					       vim \
					       sudo \
						   libboost-all-dev \
						   libopencv-dev \
					       python3 \
					       python3-dev \
					       python3-pip \
					       python3-numpy

ENV DEVUSER=${DEVUSER}
RUN adduser --uid 1000 --disabled-password --gecos "" ${DEVUSER} \
    && echo "${DEVUSER} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${DEVUSER}
USER ${DEVUSER}
