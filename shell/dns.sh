#!/usr/bin/sh

salt="<some salt>"
t=`head -c 32 /dev/urandom | tr -dc 'a-zA-Z0-9'`
md5=`echo $salt$t | md5sum  | awk '{ print $1 }`
curl -d "t=$t&md5=$md5" -X POST http://localhost/dns.php
