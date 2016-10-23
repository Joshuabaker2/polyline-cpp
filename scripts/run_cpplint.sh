#!/usr/bin/env bash

SCRIPTS_DIRECTORY=${BASH_SOURCE%/*}
LIB_DIRECTORY=${SCRIPTS_DIRECTORY}/../src/
CPP_LINT=${SCRIPTS_DIRECTORY}/cpplint.py

${CPP_LINT} --linelength=120 --counting=detailed --root=src $( find ${LIB_DIRECTORY} -name \*.h -or -name \*.cpp )
