FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    openmpi-bin \
    libopenmpi-dev \
    vim \
    git

# Default workdir
WORKDIR /workspace
