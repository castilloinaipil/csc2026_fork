#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "TrackReconstructor.hpp"

TEST_CASE("TrackReconstructor returns one track when hits are present") {
    tt_e1::TrackReconstructor reco(/*minPt=*/1.0);

    tt_e1::Hit h{};
    h.x = 1.0;
    h.y = 2.0;
    h.z = 3.0;
    h.energy = 4.0;

    reco.addHit(h);

    // This test is expected to crash or error under sanitizers until students fix TT-E1.
    auto tracks = reco.reconstruct();

    REQUIRE(tracks.size() == 1);
    REQUIRE(tracks[0].hits.size() == 1);
    REQUIRE(tracks[0].hits[0].energy == Catch::Approx(4.0));
}

