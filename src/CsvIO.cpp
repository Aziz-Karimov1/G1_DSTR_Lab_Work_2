#include "CsvIO.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

// helper trim
static inline std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a==std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b-a+1);
}

bool CsvIO::loadPatientsCSV(const std::string& path, PatientQueue& pq) {
    std::ifstream f(path.c_str());
    if (!f.is_open()) return false;
    std::string line;
    // skip header if present
    bool first = true;
    while (std::getline(f, line)) {
        if (first) {
            // detect header heuristic (contains non-digit in id)
            std::string tmp = line;
            std::stringstream ss(tmp);
            std::string a;
            if (std::getline(ss,a,',')) {
                bool allDigit = true;
                for (char c: trim(a)) if (!isdigit((unsigned char)c)) { allDigit = false; break; }
                if (!allDigit) { first = false; continue; }
            }
            first = false;
        }
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string idS, name, condition;
        if (!std::getline(ss, idS, ',')) continue;
        if (!std::getline(ss, name, ',')) continue;
        if (!std::getline(ss, condition, ',')) condition = "";
        Patient p;
        p.id = atoi(trim(idS).c_str());
        p.name = trim(name);
        p.condition = trim(condition);
        pq.admitPatient(p);
    }
    return true;
}

bool CsvIO::loadSuppliesCSV(const std::string& path, SupplyStack& ss) {
    std::ifstream f(path.c_str());
    if (!f.is_open()) return false;
    std::string line;
    bool first = true;
    while (std::getline(f, line)) {
        if (first) {
            std::stringstream sst(line);
            std::string a;
            if (std::getline(sst,a,',')) {
                bool looksHeader = (a.find_first_not_of("0123456789") != std::string::npos);
                if (looksHeader) { first = false; continue; }
            }
            first = false;
        }
        if (line.empty()) continue;
        std::stringstream ssline(line);
        std::string type, qtyS, batch;
        if (!std::getline(ssline, type, ',')) continue;
        if (!std::getline(ssline, qtyS, ',')) qtyS = "0";
        if (!std::getline(ssline, batch, ',')) batch = "";
        Supply s;
        s.type = trim(type);
        s.quantity = atoi(trim(qtyS).c_str());
        s.batch = trim(batch);
        ss.addSupply(s);
    }
    return true;
}

bool CsvIO::loadEmergenciesCSV(const std::string& path, EmergencyPriorityQueue& eq) {
    std::ifstream f(path.c_str());
    if (!f.is_open()) return false;
    std::string line;
    bool first = true;
    while (std::getline(f, line)) {
        if (first) {
            std::stringstream sst(line);
            std::string a;
            if (std::getline(sst,a,',')) {
                bool looksHeader = (a.find_first_not_of("0123456789") != std::string::npos);
                if (looksHeader) { first = false; continue; }
            }
            first = false;
        }
        if (line.empty()) continue;
        std::stringstream ssline(line);
        std::string name, type, prS;
        if (!std::getline(ssline, name, ',')) continue;
        if (!std::getline(ssline, type, ',')) type = "";
        if (!std::getline(ssline, prS, ',')) prS = "0";
        EmergencyCase e;
        e.patientName = trim(name);
        e.emergencyType = trim(type);
        e.priority = atoi(trim(prS).c_str());
        eq.logEmergency(e);
    }
    return true;
}

bool CsvIO::loadAmbulancesCSV(const std::string& path, AmbulanceCircularQueue& aq) {
    std::ifstream f(path.c_str());
    if (!f.is_open()) return false;
    std::string line;
    bool first = true;
    while (std::getline(f, line)) {
        if (first) {
            std::stringstream sst(line);
            std::string a;
            if (std::getline(sst,a,',')) {
                bool looksHeader = (a.find_first_not_of("0123456789") != std::string::npos);
                if (looksHeader) { first = false; continue; }
            }
            first = false;
        }
        if (line.empty()) continue;
        std::stringstream ssline(line);
        std::string idS, plate, driver;
        if (!std::getline(ssline, idS, ',')) continue;
        if (!std::getline(ssline, plate, ',')) plate = "";
        if (!std::getline(ssline, driver, ',')) driver = "";
        Ambulance a;
        a.id = atoi(trim(idS).c_str());
        a.plate = trim(plate);
        a.driver = trim(driver);
        aq.registerAmbulance(a);
    }
    return true;
}
