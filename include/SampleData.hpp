#ifndef SAMPLEDATA_HPP
#define SAMPLEDATA_HPP

#include "PatientQueue.hpp"
#include "SupplyStack.hpp"
#include "EmergencyPriorityQueue.hpp"
#include "AmbulanceCircularQueue.hpp"

class SampleData {
public:
    static void populate(PatientQueue& pq, SupplyStack& ss, EmergencyPriorityQueue& eq, AmbulanceCircularQueue& aq);
};

#endif // SAMPLEDATA_HPP
