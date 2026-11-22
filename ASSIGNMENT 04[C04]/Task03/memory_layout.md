# Memory Layout
The union size is the size of its largest member rounded for alignment. The tagged structure contains the enum tag plus union storage and possible padding. Verify with `sizeof` on the target compiler; sizes are implementation-dependent.
