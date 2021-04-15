# Lab executables
LABDIR=LabExercises
EXECS=$(LABDIR)/bitoperations $(LABDIR)/emptyexec $(LABDIR)/getoptPractice $(LABDIR)/sha256 $(LABDIR)/shaFunctions

# Recreate sha512 executable
sha512: sha512.c
	cc -o sha512 sha512.c

# Remove all executables
clean:
	rm -f sha512 
	rm -f $(EXECS)