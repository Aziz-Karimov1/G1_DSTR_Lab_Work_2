#include "AmbulanceCircularQueue.hpp"

AmbulanceCircularQueue::AmbulanceCircularQueue(int cap): capacity(cap), head(0), tail(0), count(0) {
    arr = new Ambulance[capacity];
}

AmbulanceCircularQueue::~AmbulanceCircularQueue() {
    delete[] arr;
}

bool AmbulanceCircularQueue::registerAmbulance(const Ambulance& a) {
    if (isFull()) return false;
    arr[tail] = a;
    tail = (tail + 1) % capacity;
    ++count;
    std::cout << "Registered ambulance ID " << a.id << " | Plate: " << a.plate << " | Driver: " << a.driver << "\n";
    return true;
}

bool AmbulanceCircularQueue::rotateShift() {
    if (count <= 1) return false; // nothing to rotate meaningfully
    // rotation: move head item to tail position
    Ambulance temp = arr[head];
    int i = head;
    // shift all elements forward by one (circularly)
    while (i != tail) {
        int next = (i + 1) % capacity;
        if (next == tail) break;
        arr[i] = arr[next];
        i = next;
    }
    arr[(tail - 1 + capacity) % capacity] = temp; // put original head at previous tail pos
    head = 0;
    tail = (head + count) % capacity;
    std::cout << "Rotated ambulance shift.\n";
    return true;
}

void AmbulanceCircularQueue::displaySchedule() const {
    if (isEmpty()) {
        std::cout << "[No ambulances registered]\n";
        return;
    }
    std::cout << "Ambulance schedule (rotation order):\n";
    int idx = head;
    for (int i=0;i<count;i++) {
        const Ambulance& a = arr[idx];
        std::cout << "  ID: " << a.id << " | Plate: " << a.plate << " | Driver: " << a.driver << "\n";
        idx = (idx + 1) % capacity;
    }
}

bool AmbulanceCircularQueue::isEmpty() const { return count == 0; }
bool AmbulanceCircularQueue::isFull() const { return count == capacity; }
int AmbulanceCircularQueue::size() const { return count; }
