#!/bin/bash
# =============================================================================
# Copyright (c) 2011-2013 Bolero MURAKAMI
# https://github.com/bolero-MURAKAMI/Sprout
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# =============================================================================
#
# requires: Netpbm (http://netpbm.sourceforge.net/)
#
src="../../example/darkroom/two_spheres.hpp"
stagedir="darkroom"
width=16
height=16
tile_width=16
tile_height=16
declare -a user_macros
user_macros=()
declare -a include_paths
include_paths=()
force=0

args=`getopt -o s:S:w:h:W:H:D:I:f -l source:,stagedir:,width:,height:,tile-width:,tile-height:,define:,include:,force -- "$@"`
if [ "$?" -ne 0 ]; then
	echo >&2 -e ": \e[31musage: $0 [-s|--source=file] [-S|--stagedir=path] [-w|--width=value] [-h|--height=value] [-W|--tile-width=value] [-H|--tile-height=value] [-D|--define=identifier]* [-I|--include=path]* [-f|-force]\e[m"
	exit 1
fi
eval set -- ${args}
while [ -n "$1" ]; do
	case $1 in
		-s|--source) src=$2; shift 2;;
		-S|--stagedir) stagedir=$2; shift 2;;
		-w|--width) width=$2; shift 2;;
		-h|--height) height=$2; shift 2;;
		-W|--tile-width) tile_width=$2; shift 2;;
		-H|--tile-height) tile_height=$2; shift 2;;
		-D|--define) user_macros=(${user_macros[@]} "$2"); shift 2;;
		-I|--include) include_paths=(${include_paths[@]} "$2"); shift 2;;
		-f|--force) force=1; shift;;
		--) shift; break;;
		*) echo >&2 -e ": \e[31munknown option($1) used.\e[m"; exit 1;;
	esac
done

echo ": settings"
echo ":   source = \"${src}\""
echo ":   stagedir = \"${stagedir}\""
echo ":   width = ${width}"
echo ":   height = ${height}"
echo ":   tile-width = ${tile_width}"
echo ":   tile-height = ${tile_height}"
if [ ${#user_macros[*]} -gt 0 ]; then
	echo ":   user-macros = (${user_macros[*]})"
fi
if [ ${#include_paths[*]} -gt 0 ]; then
	echo ":   include-paths = (${include_paths[*]})"
fi
echo ":   force = ${force}"

if [ ! -f "${src}" -a ! -f "$(cd $(dirname $0); pwd)/${src}" ]; then
	echo >&2 -e ": \e[31msource(${src}) not exists.\e[m"
	exit 1
fi

if [ -d "${stagedir}" ]; then
	if [ ${force} -eq 0 ]; then
		echo >&2 -e ": \e[31mstagedir(${stagedir}) already exists.\e[m"
		exit 1
	else
		rm -f -r ${stagedir}/*
	fi
else
	mkdir -p ${stagedir}
fi

for user_macro in ${user_macros}; do
	define_options="${define_options} -D${user_macro}"
done

for include_path in ${include_paths}; do
	include_options="${include_options} -I${include_path}"
done

echo ": start."
start=${SECONDS}

for ((y=0; y<height; y+=tile_height)); do
	echo ": rendering(${y}/${height})..."
	y_start=${SECONDS}

	for ((x=0; x<width; x+=tile_width)); do
		mkdir -p ${stagedir}/${y}/
		binname=${stagedir}/${y}/${x}.out
		g++ -o ${binname} -std=c++11 \
			${define_options} ${include_options} \
			-DDARKROOM_SOURCE="\"${src}\"" \
			-DDARKROOM_TOTAL_WIDTH=${width} \
			-DDARKROOM_TOTAL_HEIGHT=${height} \
			-DDARKROOM_TILE_WIDTH=${tile_width} \
			-DDARKROOM_TILE_HEIGHT=${tile_height} \
			-DDARKROOM_OFFSET_X=${x} \
			-DDARKROOM_OFFSET_Y=${y} \
			$(cd $(dirname $0); pwd)/darkcult.cpp && ${binname} > ${stagedir}/${y}/${x}.ppm
	done
	pushd ${stagedir}/${y}/ > /dev/null
#	convert +append $(ls *.ppm | sort -n) ../${y}.ppm
	pnmcat -lr $(ls *.ppm | sort -n) > ../${y}.ppm
	popd > /dev/null

	let "y_elapsed=${SECONDS}-${y_start}"
	echo ":   elapsed = ${y_elapsed}s"
done
pushd ${stagedir} > /dev/null
#convert -append $(ls *.ppm | sort -n) out.ppm
pnmcat -tb $(ls *.ppm | sort -n) > out.ppm
popd > /dev/null

let "elapsed=${SECONDS}-${start}"
echo ": elapsed(total) = ${elapsed}s"
echo ": finished."
