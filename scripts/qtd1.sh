#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE QtD1 with CMAKE
##---------------------------------------------------------------------------##

# Custom system paths
EXTRA_ARGS=$@
QTD1_SRC=../src
QTD1_INSTALL=../

# Run cmake
cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX=$QTD1_INSTALL \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D QTD1_ENABLE_TESTING:BOOL=OFF \
    -D QTD1_ENABLE_DEV_DOCS:BOOL=OFF \
    $EXTRA_ARGS \
    $QTD1_SRC 
