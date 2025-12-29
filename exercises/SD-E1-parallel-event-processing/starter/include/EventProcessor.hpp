#pragma once

#include "Event.hpp"
#include <vector>

namespace csc2026 {

class EventProcessor {
public:
    EventProcessor() = default;

    void reset();

    void processEvent(const Event& event);
    void processEvents(const std::vector<Event>& events);

    int totalTracks() const { return m_totalTracks; }
    double totalEnergy() const { return m_totalEnergy; }

    static std::vector<Event> generateSampleEvents(size_t nEvents);

private:
    int m_totalTracks{0};
    double m_totalEnergy{0.0};
};

} // namespace csc2026

