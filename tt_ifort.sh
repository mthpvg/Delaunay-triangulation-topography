#!/bin/bash

ifort -free -c toolbox.f90

ifort -free -c topogen.f90

ifort -free -c m_delaunay_1p1.f90

ifort -free -c m_lighter_1p1.f90

ifort -free -c m_isoligne_1p1.f90


rm *.mod

make
