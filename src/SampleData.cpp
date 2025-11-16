#include "SampleData.hpp"
#include <iostream>

void SampleData::populate(PatientQueue& pq, SupplyStack& ss, EmergencyPriorityQueue& eq, AmbulanceCircularQueue& aq) {
    // Patients
    pq.admitPatient({1001, "Alice Smith", "Fever"});
    pq.admitPatient({1002, "Bob Johnson", "Broken Arm"});
    pq.admitPatient({1003, "Charlie Lee", "Cough"});

    // Supplies
    ss.addSupply({"Bandage", 50, "BATCH-A1"});
    ss.addSupply({"Paracetamol", 200, "BATCH-P2"});
    ss.addSupply({"Saline", 30, "BATCH-S3"});

    // Emergencies
    eq.logEmergency({"Donna Ray", "Heart Attack", 10});
    eq.logEmergency({"Eli Wong", "High Fever", 4});
    eq.logEmergency({"Fiona Yap", "Car Accident", 9});

    // Ambulances
    aq.registerAmbulance({1, "AB-1001", "Driver A"});
    aq.registerAmbulance({2, "AB-1002", "Driver B"});
    aq.registerAmbulance({3, "AB-1003", "Driver C"});

    std::cout << "Sample data populated.\n";
}
