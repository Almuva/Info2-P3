#!/bin/bash
clear
cd src
(make -k prueba && cd .. && time ./obj/prueba t1.jpg resultado 32 400 400 ) || cd ..
