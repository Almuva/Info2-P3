#!/bin/bash
clear
cd src
(make -k prueba && cd .. && time ./obj/prueba t3.jpg resultado 100 500 500 ) || cd ..

