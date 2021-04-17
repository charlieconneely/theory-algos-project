# All executables.
LABDIR=LabExercises
EXECS=sha512 $(LABDIR)/bitoperations $(LABDIR)/emptyexec $(LABDIR)/getoptPractice $(LABDIR)/sha256 $(LABDIR)/shaFunctions $(LABDIR)/preproc

# Recreate sha512 executable
sha512: sha512.c
	cc -o sha512 sha512.c

# Testing
test: tests.sh
	./tests.sh

# Remove all executables
clean:
	rm -f $(EXECS)
