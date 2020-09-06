Linux system programming.

References 
==========
-> https://man7.org/training/spintro_ndc/man7.org_training_M7D-SPINTRO-NDC-TechTown.pdf


System calls
============

-> syscalls(2) manpage lists (nearly) all system calls

-> syscall instruction on x86_64. sysret
   syscall return value; on error, libc wrapper copies return value to errno.

-> Most system calls:
   	-> return -1 to indicate error
	-> place integer in global variable errno to indicate cause

=> return values should always be tested.
=> inspect errno only if result status indiacates failure.

=> errno; error numbers in errno are > 0
=> <errno.h>


-> install moreutils (for errno(1)), inotify-tools (for inotifywait)

   while inotifywait -q . ; do echo ; make; done

-> Run the program under valgrind
