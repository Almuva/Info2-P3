#!/bin/bash
clear
cd src
(make -k prueba && cd .. && time ./obj/prueba t6.jpg resultado 300 1000 1000 ) || cd ..
