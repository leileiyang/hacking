#!/bin/bash

if [[ $1 && $2 ]]; then
  sed -i "s/[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}/$1/;s/TCP=[0-9]*/TCP=$2/" omotion.nml
  echo "Change ip and port"
elif [ $1 ]; then
  sed -i "s/[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}/$1/" omotion.nml
  echo "Just change ip"
fi
