#include "q3printer.h"

Printer::Printer( unsigned int voters ) : voters(voters) {
    hasBeenWrittenTo = new int[voters](false);

}

