#!/usr/bin/awk -f

#
# Reverse Lines of Files: first line became last
#

BEGIN {
  n = 1
}

{
  array[n] = $0
  n++
}

END {
  for (i=n-1; i>0; i--)
    print array[i]
}


