#!/bin/bash
ftp -n<<!
open 120.24.81.15
user pwftp extremevision
passive mode
lcd /root/videos
put $1
close
bye
!
