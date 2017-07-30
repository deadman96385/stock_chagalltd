#!/bin/bash

export CROSS_COMPILE=/opt/toolchains/arm-eabi-4.6/bin/arm-eabi-
export ARCH=arm

make chagalllte_00_defconfig
make -j64