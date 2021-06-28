# OS
This is a practice ground for building an os from scratch. Mainly following reference 1's tutorial.
Reference 1's tutorial has 24 chapters, and chapter 1-17 are based on reference 2.
Through out the tutorial here are some small bugs I noticed.

(1) chapter 4: boot_sect_stack.asm -> line 36: data is random not because it is poped, but never initialized.

(2) chapter 11: gcc -> if you run into problem compiling "../gcc-x.x.x/configure*", try "" and recompile (unable to regenerate the error right now, if you run into this problem google it, one additional command is needed)

reference:
### 1. https://github.com/cfenollosa/os-tutorial
### 2. https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

