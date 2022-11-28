#!/bin/bash

unxz -v linux-5.19.9.tar.xz
tar xvf linux-5.19.9.tar
cd linux-5.19.9

wget --no-check-certificate https://raw.githubusercontent.com/Sidanand55/assignment1os/main/config-rev-8

make mrproper
mv config-rev-9-gold .config

make -j2
