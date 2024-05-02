#include <nanobind/nanobind.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/bind_vector.h>
#include <nanobind/stl/bind_map.h>

#include <stdint.h>

// Include headers
#include "MSP430.h"
#include "MSP430_Debug.h"

namespace nb = nanobind;
using namespace nb::literals;

/*
class Error {
public:
    std::string Simple[2] = {
        "OK",         // NO_ERR
        "INITIALIZE", // INITIALIZE_ERR
    };

    std::string Verbose[2] = {
        "No error",
        "Could not initialize device interface"
    };
};
*/

const char *err_str[][2] =
{
    {"OK", "No error"},
    {"ERR_INITIALIZE", "Could not initialize device interface"},
    {"ERR_CLOSE", "Could not close device interface"},
    
};

class Status {
  public:
    int value;
    Status(int n) { value = n; }
    std::string toStr (void) {
        return err_str[value][0];
    };
    std::string verbose(void) {
        return err_str[value][1];
    };
    /*
    bool operator==(const Status& rhs) const {
        return value == rhs.value;
    };
    */
    bool operator==(std::string err) {
        return !err.compare(this->toStr());
    }
};

NB_MODULE(mspfet, m) {

    // STATUS_T MSP430_Initialize(const char* port, int32_t* version);
    m.def("MSP430_Initialize", [](const char *port) {
        int32_t version;
        int rv = MSP430_Initialize (port, &version);
        return std::make_tuple(new Status(rv), version);
    }, "port"_a = "TIUSB",
        "Initialize communication with MSPFET, returns (rv, version).\n"
        "If version == (-1,-3) MSP430_FET_FwUpdate should be called.");

    // STATUS_T MSP430_Close(int32_t vccOff);
    m.def("MSP430_Close", [](bool vccOff) { return new Status(MSP430_Close (vccOff)); },
          "vcc_off"_a = true,
          "Close connection with MSPFET. Optionally turn off VCC to device.");

    // Represent error enum as class
    nb::class_<Status>(m, "Status")
        .def(nb::init<int>())
        .def("__repr__", &Status::toStr)
        .def("verbose", &Status::verbose)
        .def("Error", &Status::Error)
        .def_ro("value", &Status::value)
        .def("__eq__", &Status::operator==);

    /*
    nb::class_<Error>(m, "Error")
        .def_ro("simple", &Error::Simple)
        .def_ro("verbose", &Error::Verbose);
    */  
    /*
    // Represention for comparison
    nb::enum_<ERROR_CODE_t>(m, "ERR")
        .value("NONE", NO_ERR)
        .value("INITIALIZE", INITIALIZE_ERR)
        .value("CLOSE", CLOSE_ERR)
        .value("PARAMETER", PARAMETER_ERR)
        .value("NO_DEVICE", NO_DEVICE_ERR);
    */
    
    // Bind device info union
    /*
    nb::class_<DEVICE_T>(m, "Device")
        .def_rw ("buffer", &DEVICE_T::buffer);
    */
}
