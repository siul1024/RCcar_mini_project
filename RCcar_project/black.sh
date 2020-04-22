#!/bin/sh



	echo `raspivid -o video$1_$2.h264 -vf -t 10000`
