#!/bin/bash

# 
# This file executes from the build directory by the Eclipse "Pre Build" step
#

python ../_can_dbc/dbc_parse.py -i ../../snf.dbc -s GEO > ../_can_dbc/generated_can.h