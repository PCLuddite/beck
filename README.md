# Beck's Depression Inventory

Simple C program to take Beck's Depression Inventory to measure your level of depression. This is designed to be highly portable ANSI-C code (with `#ifdef`s for platform specific features).

"beck.txt" contains 20 prompts from the depression inventory, which naturally needs to be in the same directory as the executable. Each question is on its own line with each item delimeted by a pipe character ("|"). The only limits to the number of prompts and the items for their prompts are the size of an integer on that platform and a hardcoded 1024 characters per line excluding trailing whitespace (this can be expanded in the code by simply changing the buffer size at declaration). This program can be used for custom inventories if the new file conforms to these guidelines and retains the filename "beck.txt".
