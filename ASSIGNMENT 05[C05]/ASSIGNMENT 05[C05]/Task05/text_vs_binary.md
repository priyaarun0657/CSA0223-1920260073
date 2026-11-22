# Storage choice
Donor details are text records written with fprintf for readability and portability. Fixed-size stock records are binary with fwrite for compact storage and direct record seeking. Binary layout can depend on compiler, padding and endianness.
