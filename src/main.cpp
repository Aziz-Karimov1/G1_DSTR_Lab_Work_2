#include <iostream>
#include <cstdlib>
#include "PatientQueue.hpp"
#include "SupplyStack.hpp"
#include "EmergencyPriorityQueue.hpp"
#include "AmbulanceCircularQueue.hpp"
#include "CsvIO.hpp"
#include "SampleData.hpp"
#include "Utils.hpp"

void showMainMenu() {
    std::cout << "\n=== Hospital Patient Care Management ===\n";
    std::cout << "1. Patient Admission Clerk\n";
    std::cout << "2. Medical Supply Manager\n";
    std::cout << "3. Emergency Department Officer\n";
    std::cout << "4. Ambulance Dispatcher\n";
    std::cout << "5. Load CSVs from data/ (if present)\n";
    std::cout << "6. Populate sample data\n";
    std::cout << "0. Exit\n";
    std::cout << "Select option: ";
}

void patientMenu(PatientQueue& pq) {
    while (true) {
        std::cout << "\n--- Patient Menu ---\n";
        std::cout << "1. Admit Patient\n";
        std::cout << "2. Discharge Patient (earliest)\n";
        std::cout << "3. View Patient Queue\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::string choice; std::getline(std::cin, choice);
        if (choice == "1") {
            Patient p;
            std::cout << "Enter ID: ";
            std::string sid; std::getline(std::cin, sid); p.id = atoi(sid.c_str());
            std::cout << "Enter name: "; p.name = readLineTrimmed();
            std::cout << "Enter condition: "; p.condition = readLineTrimmed();
            pq.admitPatient(p);
        } else if (choice == "2") {
            Patient out;
            if (!pq.dischargePatient(out)) std::cout << "No patients to discharge.\n";
        } else if (choice == "3") {
            pq.viewQueue();
        } else if (choice == "0") return;
        else std::cout << "Invalid.\n";
    }
}

void supplyMenu(SupplyStack& ss) {
    while (true) {
        std::cout << "\n--- Supply Menu ---\n";
        std::cout << "1. Add Supply Stock\n";
        std::cout << "2. Use Last Added Supply\n";
        std::cout << "3. View Current Supplies\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::string choice; std::getline(std::cin, choice);
        if (choice == "1") {
            Supply s;
            std::cout << "Enter type: "; s.type = readLineTrimmed();
            std::cout << "Enter quantity: "; std::string q; std::getline(std::cin,q); s.quantity = atoi(q.c_str());
            std::cout << "Enter batch: "; s.batch = readLineTrimmed();
            ss.addSupply(s);
        } else if (choice == "2") {
            Supply out;
            if (!ss.useLastAdded(out)) std::cout << "No supplies to use.\n";
        } else if (choice == "3") {
            ss.viewSupplies();
        } else if (choice == "0") return;
        else std::cout << "Invalid.\n";
    }
}

void emergencyMenu(EmergencyPriorityQueue& eq) {
    while (true) {
        std::cout << "\n--- Emergency Menu ---\n";
        std::cout << "1. Log Emergency Case\n";
        std::cout << "2. Process Most Critical Case\n";
        std::cout << "3. View Pending Emergency Cases\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::string choice; std::getline(std::cin, choice);
        if (choice == "1") {
            EmergencyCase e;
            std::cout << "Enter patient name: "; e.patientName = readLineTrimmed();
            std::cout << "Enter emergency type: "; e.emergencyType = readLineTrimmed();
            std::cout << "Enter priority (higher = more critical): "; std::string p; std::getline(std::cin,p); e.priority = atoi(p.c_str());
            eq.logEmergency(e);
        } else if (choice == "2") {
            EmergencyCase out;
            if (!eq.processMostCritical(out)) std::cout << "No emergency cases to process.\n";
        } else if (choice == "3") {
            eq.viewPending();
        } else if (choice == "0") return;
        else std::cout << "Invalid.\n";
    }
}

void ambulanceMenu(AmbulanceCircularQueue& aq) {
    while (true) {
        std::cout << "\n--- Ambulance Menu ---\n";
        std::cout << "1. Register Ambulance\n";
        std::cout << "2. Rotate Ambulance Shift\n";
        std::cout << "3. Display Ambulance Schedule\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::string choice; std::getline(std::cin, choice);
        if (choice == "1") {
            Ambulance a;
            std::cout << "Enter ID: "; std::string idS; std::getline(std::cin, idS); a.id = atoi(idS.c_str());
            std::cout << "Enter plate: "; a.plate = readLineTrimmed();
            std::cout << "Enter driver: "; a.driver = readLineTrimmed();
            if (!aq.registerAmbulance(a)) std::cout << "Ambulance list full. Increase capacity.\n";
        } else if (choice == "2") {
            if (!aq.rotateShift()) std::cout << "Not enough ambulances to rotate.\n";
        } else if (choice == "3") {
            aq.displaySchedule();
        } else if (choice == "0") return;
        else std::cout << "Invalid.\n";
    }
}

int main() {
    PatientQueue pq;
    SupplyStack ss;
    EmergencyPriorityQueue eq;
    AmbulanceCircularQueue aq(20); // capacity 20 ambulances

    while (true) {
        showMainMenu();
        std::string opt; std::getline(std::cin,opt);
        if (opt == "1") {
            patientMenu(pq);
        } else if (opt == "2") {
            supplyMenu(ss);
        } else if (opt == "3") {
            emergencyMenu(eq);
        } else if (opt == "4") {
            ambulanceMenu(aq);
        } else if (opt == "5") {
            bool any = false;
            if (CsvIO::loadPatientsCSV("data/patients.csv", pq)) any = true; else std::cout << "patients.csv not found or unreadable.\n";
            if (CsvIO::loadSuppliesCSV("data/supplies.csv", ss)) any = true; else std::cout << "supplies.csv not found or unreadable.\n";
            if (CsvIO::loadEmergenciesCSV("data/emergencies.csv", eq)) any = true; else std::cout << "emergencies.csv not found or unreadable.\n";
            if (CsvIO::loadAmbulancesCSV("data/ambulances.csv", aq)) any = true; else std::cout << "ambulances.csv not found or unreadable.\n";
            if (any) std::cout << "CSV loading attempted.\n";
        } else if (opt == "6") {
            SampleData::populate(pq, ss, eq, aq);
        } else if (opt == "0") {
            std::cout << "Exiting. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
