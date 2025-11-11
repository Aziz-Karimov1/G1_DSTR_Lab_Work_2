#ifndef MODELS_HPP
#define MODELS_HPP

#include <string>

// Simple, POD-like records shared by modules.

struct Patient {
    int id{};
    std::string name;
    std::string conditionType; // e.g., "flu", "fracture"
};

struct SupplyItem {
    std::string type;   // e.g., "mask", "bandage"
    int quantity{};     // units in this batch
    std::string batch;  // batch code or date
};

struct EmergencyCase {
    std::string patientName;
    std::string emergencyType; // e.g., "cardiac", "trauma"
    // Priority convention: 1 = most critical (min-heap).
    int priority{};
};

struct Ambulance {
    int code{};             // e.g., 101
    std::string driverName; // optional
};

#endif // MODELS_HPP
