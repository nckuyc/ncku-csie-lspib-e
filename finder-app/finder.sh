#!/bin/sh

# The requirements for this script are:

# 1. Accepts the following runtime arguments:
# the first argument is a path to a directory on the filesystem, referred to below as filesdir;
# the second argument is a text string which will be searched within these files, referred to below as searchstr.
#
# 2. Exits with return value 1 error and print statements if any of the parameters above were not specified.
#
# 3. Exits with return value 1 error and print statements if filesdir does not represent a directory on the filesystem.
#
# 4. Prints a message "The number of files are X and the number of matching lines are Y"
# where X is the number of files in the directory and all subdirectories
# and Y is the number of matching lines found in respective files,
# where a matching line refers to a line which contains searchstr (and may also contain additional content).

filesdir=$1
searchstr=$2

if [ $# -ne 2 ]; then
	echo "Not enough arguments passed! You need two arguments: filesdir and searchstr"
	exit 1
elif [ -z "$filesdir" ] || [ -z "$searchstr" ]; then
	echo "The two arguments cannot be empty!"
	exit 1
elif ! [ -d "$filesdir" ]; then
	echo "The provided directory ${filesdir} is not a valid!"
	exit 1
fi

X=$(find -L "$filesdir" -type f | wc -l)
Y=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $X and the number of matching lines are $Y"
	
