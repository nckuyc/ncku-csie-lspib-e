#!/bin/bash

# The description of this script is:
# Accepts the following arguments: the first argument is a full path to a file (including filename) on the filesystem,
# referred to below as writefile;
# the second argument is a text string which will be written within this file, referred to below as writestr
#
# Exits with value 1 error and print statements if any of the arguments above were not specified.
#
# Creates a new file with name and path writefile with content writestr, overwriting any existing file
# and creating the path if it doesn’t exist. 
# Exits with value 1 and error print statement if the file could not be created.

writefile=$1
writestr=$2

if [ $# -ne 2 ] && [ -z "$writefile" ] || [ -z "$writestr" ]; then
	echo "Invalid arguments. The script requires two non-empty arguments: writefile and writestr"
	exit 1
fi

dirpath=$(dirname "$writefile")		# "echo >" fails if no parent directory present
mkdir -p "$dirpath"

echo $writestr >| $writefile 		# ">>" appends, ">" overwrites, "|>" bypasses overwrite protection (noclobber)

if [ $? -ne 0 ]; then
	echo "File couldn't be created at ${writefile}"
fi
