#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include "soh/Network/Anchor/JsonConversions.hpp"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>

extern "C" {
#include "macros.h"
#include "variables.h"
extern PlayState* gPlayState;
}

/**
 * ENEMY_LIST
 * 
 * Communicating enemy information back and forth takes a lot of network bandwidth
 * For best results, the room owner (host) should be self-hosting the server on their local network
 * 
 */

void Anchor::SendPacket_EnemyList() {
    //looks different if being sent by host or non-host
    if (!IsSaveLoaded()) {
        return;
    }
    uint8_t currentPlayerCount = 0;
    for (auto& [clientId, client] : clients) {
        if (client.sceneNum == gPlayState->sceneNum && client.online && client.isSaveLoaded && !client.self) {
            currentPlayerCount++;
        }
    }
    if (currentPlayerCount == 0) {
        //alone in this scene, no need to sync enemies
        return;
    }

    nlohmann::json payload;
    payload["type"] = ENEMY_LIST;
    payload["quiet"] = true;
    if (ownClientId != roomState.ownerClientId) payload["targetClientId"] = roomState.ownerClientId;
    
    SendJsonToRemote(payload);
}

void Anchor::HandlePacket_EnemyList(nlohmann::json payload) {
    return;
}

#endif // ENABLE_REMOTE_CONTROL