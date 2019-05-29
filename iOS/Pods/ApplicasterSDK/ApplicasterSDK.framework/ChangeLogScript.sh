#!/bin/bash
# pass release notes file in the arguments

releaseNoteFilename="$1"
changeLogsFilename="ChangeLogs.md"
breakLineMark="---"

if [ -z $releaseNoteFilename ]
then
echo "Error (1) - No release notes argument supplied"
exit 1
elif [ ! -f $releaseNoteFilename ]
then
echo "Error (2) - Can't find release notes file"
exit 2
else
echo "Creating change log from release notes file"

echo '' > $changeLogsFilename
while read -r line
do
	if [[ $line == $breakLineMark* ]]
		then
		break
	fi

	echo "$line" >> $changeLogsFilename
	
done < "$releaseNoteFilename"

fi