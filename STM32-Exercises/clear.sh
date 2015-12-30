#!/bin/bash

find . -name *.o -exec rm {} \;
find . -name *.d -exec rm {} \;
find . -name *.elf -exec rm {} \;
