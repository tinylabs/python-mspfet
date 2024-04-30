#include <nanobind/nanobind.h>

// Include headers
#include "MSP430.h"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(mspfet, m) {
    m.def("MSP430_Initialize", &MSP430_Initialize);
    m.def("MSP430_Close", &MSP430_Close);
}
