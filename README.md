# TLDList
A coursework for Systems Programming (H)

## Description
Given a start date, an end date, and one or more log files, the program is to determine the percentage of access from each TLD
during that period, outputting the final percentages on standard output.

### Issues
Date works, but there are null pointer checks missing in duplicate and compare;
Tldlist.c is not working. It crashes with segmentation fault. Valgrind reports memory leaks. The implementation looks largely
workable but clearly has some issues (hence the segfault). There are various null pointer checks missing (e.g. in iter_next or
iter_create).
