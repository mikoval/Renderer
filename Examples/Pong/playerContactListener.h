#pragma once
#include "core.h" 

  class PlayerContactListener : public b2ContactListener
  {
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
  };
