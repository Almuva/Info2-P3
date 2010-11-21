#!/bin/bash
clear
cd src
(make -k prueba && cd .. && time ./obj/prueba bob.jpg basura  -5 -5 ) || cd ..
