#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>
#include <chrono>

/**
 * SERVER_PING
 *
 * Send a message to yourself and count how long it takes to be recieved. This value is the ping.
 */

void Anchor::SendPacket_ServerPing() {

    using namespace std::chrono;

    nlohmann::json payload;
    payload["type"] = SERVER_PING;
    payload["targetClientId"] = ownClientId;
    uint64_t now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    payload["timeSent"] = now;
    
    SendJsonToRemote(payload);
}

void Anchor::HandlePacket_ServerPing(nlohmann::json payload) {
    using namespace std::chrono;
    uint64_t now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    ping = now - payload["timeSent"].get<uint64_t>();
}

#endif // ENABLE_REMOTE_CONTROL