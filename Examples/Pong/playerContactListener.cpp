#include "playerContactListener.h"


void PlayerContactListener::BeginContact(b2Contact* contact) {
    printf("FINDME: CONTACT STARTED \n");
}
void PlayerContactListener::EndContact(b2Contact* contact) {
    printf("FINDME: CONTACT FINISHED \n");
}
