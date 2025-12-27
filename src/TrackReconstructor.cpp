// CSC Latin America 2026 - Track Reconstructor implementation
#include "TrackReconstructor.hpp"
#include <cmath>
#include <algorithm>

namespace csc2026 {

double Track::chi2() const {
    if (hits.size() < 2) return 0.0;
    // Simplified chi2 calculation
    double sum = 0.0;
    for (size_t i = 1; i < hits.size(); ++i) {
        double dx = hits[i].x - hits[i-1].x;
        double dy = hits[i].y - hits[i-1].y;
        sum += dx * dx + dy * dy;
    }
    return sum / (hits.size() - 1);
}

TrackReconstructor::TrackReconstructor(int maxHits)
    : m_maxHits(maxHits) {
    m_hits.reserve(maxHits);
}

TrackReconstructor::~TrackReconstructor() = default;

void TrackReconstructor::addHit(const Hit& hit) {
    if (static_cast<int>(m_hits.size()) < m_maxHits) {
        m_hits.push_back(hit);
    }
}

void TrackReconstructor::processHits() {
    // Sort hits by z coordinate
    std::sort(m_hits.begin(), m_hits.end(),
        [](const Hit& a, const Hit& b) { return a.z < b.z; });
}

std::vector<Track> TrackReconstructor::reconstruct() {
    processHits();
    
    std::vector<Track> tracks;
    if (m_hits.empty()) return tracks;
    
    // Simple track finding: group consecutive hits
    Track currentTrack;
    for (const auto& hit : m_hits) {
        currentTrack.hits.push_back(hit);
        
        // Start new track every 5 hits (simplified)
        if (currentTrack.hits.size() >= 5) {
            // Calculate track parameters
            const auto& first = currentTrack.hits.front();
            const auto& last = currentTrack.hits.back();
            double dx = last.x - first.x;
            double dy = last.y - first.y;
            double dz = last.z - first.z;
            
            currentTrack.pt = std::sqrt(dx * dx + dy * dy);
            currentTrack.phi = std::atan2(dy, dx);
            currentTrack.eta = 0.5 * std::log((dz + currentTrack.pt) / 
                                               (dz - currentTrack.pt + 1e-10));
            
            tracks.push_back(std::move(currentTrack));
            currentTrack = Track{};
        }
    }
    
    // Don't forget remaining hits
    if (!currentTrack.hits.empty() && currentTrack.hits.size() >= 3) {
        tracks.push_back(std::move(currentTrack));
    }
    
    return tracks;
}

void TrackReconstructor::clear() {
    m_hits.clear();
}

} // namespace csc2026
