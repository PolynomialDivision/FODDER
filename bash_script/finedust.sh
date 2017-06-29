#!/bin/bash

# forked from http://opengeiger.de/Feinstaub/FeinstaubDatenLogger.pdf
# changes: 	+ langauge
#			+ endian

WDIR=~
while true; do
	stty -F /dev/ttyUSB0 9600 raw

	# read from serial
	INPUT=$(dd bs=10 count=1 </dev/ttyUSB0 2>/dev/null | od -x -N10 |head -n 1|cut -f2-10 -d" ");

	
	FIRST4BYTES=$(echo $INPUT|cut -b1-4);
	if [ !"$FIRST4BYTES" = "aac0" ]; then
	  echo "incorrect sequence (may wrong endian?), exiting"
	  exit;
	fi

	PPM25LOW=$(echo $INPUT|cut -f2 -d " "|cut -b1-2);
	PPM25HIGH=$(echo $INPUT|cut -f2 -d " "|cut -b3-4);
	PPM10LOW=$(echo $INPUT|cut -f3 -d " "|cut -b1-2);
	PPM10HIGH=$(echo $INPUT|cut -f3 -d " "|cut -b3-4);

	# convert to decimal
	PPM25LOWDEC=$( echo $((0x$PPM25LOW)) );
	PPM25HIGHDEC=$( echo $((0x$PPM25HIGH)) );
	PPM10LOWDEC=$( echo $((0x$PPM10LOW)) );
	PPM10HIGHDEC=$( echo $((0x$PPM10HIGH)) );
	PPM25=$(echo "scale=1;((( $PPM25HIGHDEC * 256 ) + $PPM25LOWDEC ) / 10 )"|bc -l );
	PPM10=$(echo "scale=1;((( $PPM10HIGHDEC * 256 ) + $PPM10LOWDEC ) / 10 )"|bc -l );
	
	echo "Fine dust PPM25: $PPM25"
	echo "Fine dust PPM10: $PPM10"
	echo " "
done