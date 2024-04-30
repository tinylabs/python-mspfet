#include <nanobind/nanobind.h>

// Include headers
#include "MSP430.h"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(mspfet, m) {
    m.def("MSP430_Configure", &MSP430_Configure);
    m.def("MSP430_Initialize", &MSP430_Initialize);
}
