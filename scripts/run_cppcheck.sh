#!/usr/bin/env bash

SCRIPTS_DIRECTORY=${BASH_SOURCE%/*}
LIB_DIRECTORY=${SCRIPTS_DIRECTORY}/../src/


cppcheck ${LIB_DIRECTORY} --enable=all
