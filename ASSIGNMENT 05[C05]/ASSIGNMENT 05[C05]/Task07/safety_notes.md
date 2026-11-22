# Adversarial inputs
Unbounded scanf("%s") can overflow fixed buffers. fgets limits the read and preserves safety; validate truncation. Missing files should be checked and reported with perror. Use `-fsanitize=address` to test memory safety. getline dynamically grows a heap buffer; caller frees it.
