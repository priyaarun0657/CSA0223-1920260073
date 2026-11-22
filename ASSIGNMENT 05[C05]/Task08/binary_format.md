# Binary format
Records use a C struct for demonstration. A production file should serialize fields explicitly to avoid ABI padding and endianness differences. Text is readable and usually larger; binary is compact and fast for fixed records.
