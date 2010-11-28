#!/bin/bash
clear
cd src
(make -k prueba && cd .. && time ./obj/prueba t1.jpg resultado 20 200 200 ) || cd ..
