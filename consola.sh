#!/bin/bash
clear
cd src
(make -k prueba && cd .. && time ./obj/prueba t1.jpg resultado 32 32 200 200 ) || cd ..
