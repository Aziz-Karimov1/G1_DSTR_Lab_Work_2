#ifndef CSVIO_HPP
#define CSVIO_HPP

#include <string>
#include "PatientQueue.hpp"
#include "SupplyStack.hpp"
#include "EmergencyPriorityQueue.hpp"
#include "AmbulanceCircularQueue.hpp"

// Simple CSV reader that loads rows and calls the provided managers.
// CSV lines are split by commas; trimming minimal.
// Each load function expects CSV with columns matching the models.

class CsvIO {
public:
    // returns true if file existed and was processed
    static bool loadPatientsCSV(const std::string& path, PatientQueue& pq);
    static bool loadSuppliesCSV(const std::string& path, SupplyStack& ss);
    static bool loadEmergenciesCSV(const std::string& path, EmergencyPriorityQueue& eq);
    static bool loadAmbulancesCSV(const std::string& path, AmbulanceCircularQueue& aq);
};

#endif // CSVIO_HPP
