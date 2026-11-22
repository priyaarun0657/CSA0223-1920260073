# Pointer safety
Returning a pointer to an array element is safe while the array remains alive. Returning the address of a local variable is invalid because its lifetime ends when the function returns. An index is often safer across reallocations; an element pointer may become invalid if the allocation moves.
