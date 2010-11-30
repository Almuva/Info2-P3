#!/bin/bash
clear
cd src
(make -k prueba && cd .. && time ./obj/prueba lemon.png pear.png resultado 32) || cd ..
