#include "TrackReconstructor.hpp"
#include <iostream>

int main() {
    std::cout << "CSC 2026 - Analysis demo\n";

    csc2026::TrackReconstructor reco(/*minPt=*/1.0);

    for (int i = 0; i < 10; ++i) {
        csc2026::Hit h{};
        h.x = 0.1 * i;
        h.y = 0.2 * i;
        h.z = 0.3 * i;
        h.energy = 1.0;
        reco.addHit(h);
    }

    auto tracks = reco.reconstruct();
    std::cout << "Tracks: " << tracks.size() << "\n";
    if (!tracks.empty()) {
        std::cout << "Track pt: " << tracks[0].pt << "\n";
    }

    return 0;
}

