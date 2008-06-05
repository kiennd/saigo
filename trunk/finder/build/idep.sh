#!/bin/bash -x

PREFIX="../include/"
HEADER_EXT="hpp"

if [[ "$1" == "-p" ]] ; then
    PREFIX="$2"
    shift 2
fi

if [[ "$1" == "-e" ]] ; then
    case $2 in
        "c") HEADER_EXT="h";;
        "cpp") HEADER_EXT="hpp";;
    esac
    shift 2
fi

egrep -ho "^ #include\ *<(.+)>" $@ | sort | uniq |
sed -e "s/.*<\(.*\.${HEADER_EXT}\)>/\1/" |
egrep -v "include" |
sed -e "s,\b\(.*\)\b,${PREFIX}\1,"

