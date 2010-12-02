#!/bin/bash
clear
cd src
(make -k prueba && cd .. && time ./obj/prueba t3.jpg pear.png 10 500 500 ) || cd ..

