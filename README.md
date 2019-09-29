# Malloc
Implement replacements for the malloc/calloc, realloc and free system calls. Re-
fer to Lecture 11.
• Your functions should have the same calling conventions as the original
malloc, calloc, and realloc. Put them together in a static library (.a).
• One should be able to take a working program, link it to your library and
run it, and it should behave normally. If you find it easier to give your
functions different names, then we will do the required string replacements
before compiling.
• You should preferably include a debug() or info() or similarly-named func-
tion (not provided by the standard C library). A call to this function should
print information about the current state of the heap to stderr.
