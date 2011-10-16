#This is a simple program, so we just need to copy a Makefile with some 
#variable settings.
mkdir build/work
cat build/compiler > build/work/Makefile
cat Makefile.in >> build/work/Makefile