# Memory errors
Leak: losing the pointer before free; avoid by retaining ownership and freeing at exit. Dangling pointer: using pointer after free/realloc; reset or reacquire. Double free: freeing the same allocation twice; centralize cleanup and set pointer NULL.
