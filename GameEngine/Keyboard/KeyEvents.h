#pragma once

#ifndef KEY_EVENTS_H
#define KEY_EVENETS_H

#include "..\Utility\SharedIncludes.h"

void handleKeyEvents();

void keyEvent_CallBack(GLFWwindow * window, int key, int scancode, int action, int mods);
#endif /* KEY_EVENTS_H */