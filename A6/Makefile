CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wextra -MMD \

MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = config.o printer.o bank.o parent.o watCard.o watCardOffice.o groupoff.o truck.o bottlingplant.o student.o vendingmachine.o nameserver.o main.o
EXEC = soda

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

#############################################################

.PHONY : all clean
.ONESHELL :

all : ${EXEC}					# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d ${OBJECTS} ${EXEC} VoteImpl