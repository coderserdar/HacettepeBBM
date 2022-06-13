# TaskB.sh
# compressor task, using tar utility

#!/bin/bash

TARPATH="/root/Desktop"
TARDIRS="/root/Desktop/Desk /root/yeni"

for directory in $TARDIRS
	do	
		if [ -d "$directory" ]
		then	
			tar cfv $TARPATH"/"`basename $directory`".tar" "$directory"

		fi
	done
