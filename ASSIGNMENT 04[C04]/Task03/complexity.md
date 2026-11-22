# Complexity
Reading a tagged packet: O(1). Storage per packet: tag plus union and padding. Separate arrays can reduce unused payload space in some workloads but complicate indexing. A void-pointer design requires dynamic allocation and explicit type management.
