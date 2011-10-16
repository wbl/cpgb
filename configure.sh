#This is a simple program, so we just need to copy a Makefile with some 
#variable settings.

cat build/compiler > build/Makefile
cat Makefile.in >> build/Makefile