# generates template files, calls two c programs (Proc1, Proc2)

#!/bin/bash

i=1

for filename in  `./Proc1` # call first c program for each user
	do
		# generate template file with user name
		touch $filename
		echo -e "Date : DATE\nUser Name: UNAME, User Id: UID\nGroup Name: GNAME\nLast Login Time: LTIME\nUsed Disk Space: DSPACE" > $filename
		
		# add date into the template
		d=`date`				
		cat $filename | sed 's/DATE/'"$d"'/' > $filename
		
		
		# generate temp file		
		touch "temp"
		fl="temp"
		echo `last`>$fl
				
		# read file line by line
		exec 0<$fl
		while read line
		do 
			
		un=`echo $line | awk '{print $1}'`
			if [ $un = $filename ]
			then
				# place last login time into the template file
				lt=`echo $line | awk '{print $10}'`
				cat $filename | sed 's/LTIME/'"$lt"'/' >$filename	
			fi				
		done
		
		rm -f $fl

		for value in `./Proc2 $filename` # call C function with argument
		do
			

			if [ $i -eq 1 ] # if value is user name
			then
				# add user name into the template file	
				cat $filename | sed 's/UNAME/'"$value"'/' > $filename				 	
			elif [ $i -eq 2 ] # if value is user id
			then
				# add user id into the template file
				cat $filename | sed 's/UID/'"$value"'/' > $filename			
			elif [ $i -eq 3 ] # if value is group id
			then
				# find grup name by using group id
				FILE="/etc/group"
				exec 0<$FILE	
				while read line
				do 
					
					gid=`echo $line | awk -F: '{print $3}'`
					if [ $gid -eq $value ]
					then
						# add group name into the template file
						gname=`echo $line | awk -F: '{print $1}'` 
						cat $filename | sed 's/GNAME/'"$gname"'/' >$filename			  		
					fi				
				done
			elif [ $i -eq 4 ] # if value is home directory
			then
				ds=`du -sh $value | awk '{print $1}'` # take disk space used by home directory
				cat $filename | sed 's/DSPACE/'"$ds"'/' >|$filename # change the value in the template file
			
			fi

			i=`expr $i \+ 1` # increase i
					
		done

	done
