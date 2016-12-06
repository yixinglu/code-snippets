#!/bin/bash

ADOBE_FONTS="/tmp/adobe-fonts"
INSTALL_DIR="~/.fonts"

mkdir -p $ADOBE_FONTS && cd $ADOBE_FONTS
wget https://github.com/adobe-fonts/source-code-pro/archive/2.030R-ro/1.050R-it.zip
unzip 1.050R-it.zip && cd 1.050R-it/
mkdir -p $INSTALL_DIR
cp OTF/*.otf $INSTALL_DIR
fc-cache -f -v
rm -rf $ADOBE_FONTS
