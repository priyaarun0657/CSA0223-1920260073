# Pseudocode
DIGITAL_ROOT(n): if n<10 return n; sum digits; return DIGITAL_ROOT(sum)
FAST_POWER(b,n): if n=0 return 1; h=FAST_POWER(b,floor(n/2)); if n odd return b*h*h else return h*h
