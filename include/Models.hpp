#ifndef MODELS_HPP
#define MODELS_HPP

#include <string>

struct Patient {
    int id;
    std::string name;
    std::string condition;
};

struct Supply {
    std::string type;
    int quantity;
    std::string batch;
};

struct EmergencyCase {
    std::string patientName;
    std::string emergencyType;
    int priority; // larger -> more critical
};

struct Ambulance {
    int id;
    std::string plate;
    std::string driver;
};

#endif // MODELS_HPP
