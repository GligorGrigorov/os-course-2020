#!/bin/bash

TIME=$(date +%T)
if [ $# -eq 1 ]; then
	mkdir "${TIME}.dir"
	cp $(find $1 -type f -mmin -45) "${TIME}.dir"
fi
