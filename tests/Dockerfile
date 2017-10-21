FROM ubuntu:16.04

RUN useradd -m zephiroth
USER zephiroth
WORKDIR /home/zephiroth

USER root
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
	doxygen \
    device-tree-compiler \
    dfu-util \
    git \
    gperf \
    ninja-build \
    python3-pip \
    python3-ply \
    python3-setuptools \
    file \
    xz-utils
    
    
USER zephiroth

# Install the specific version of CMake that Zephyr supports
ENV CMAKE_VERSION_FULL 3.8.2
ENV CMAKE_VERSION_SHORT 3.8

#ADD https://cmake.org/files/v$CMAKE_VERSION_SHORT/cmake-$CMAKE_VERSION_FULL-Linux-x86_64.sh
ADD cmake-$CMAKE_VERSION_FULL-Linux-x86_64.sh $HOME
RUN yes | sh cmake-$CMAKE_VERSION_FULL-Linux-x86_64.sh | cat
ENV PATH /home/zephiroth/cmake-$CMAKE_VERSION_FULL-Linux-x86_64/bin:$PATH

RUN git clone https://github.com/zephyrproject-rtos/zephyr.git

RUN pip3  install --user wheel
RUN pip3  install --user -r zephyr/scripts/requirements.txt

ENV SDK_VERSION 0.9.2-rc4
#ADD https://github.com/zephyrproject-rtos/meta-zephyr-sdk/releases/download/$SDK_VERSION/zephyr-sdk-$SDK_VERSION-setup.run $HOME
ADD zephyr-sdk-$SDK_VERSION-setup.run $HOME

USER root
RUN chown -R zephiroth:zephiroth zephyr-sdk-$SDK_VERSION-setup.run
USER zephiroth

RUN sh $HOME/zephyr-sdk-$SDK_VERSION-setup.run -- -d $HOME/zephyr-sdk

ENV ZEPHYR_GCC_VARIANT zephyr
ENV ZEPHYR_SDK_INSTALL_DIR=/home/zephiroth/zephyr-sdk

WORKDIR /home/zephiroth/zephyr

RUN git checkout cmake_migration
