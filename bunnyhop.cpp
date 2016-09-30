//
//  bunnyhop.cpp
//
//  Created by Andre Kalisch on 24.09.16.
//  Copyright © 2016 Andre Kalisch. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

class Bunnyhop
{
public:
    void sendKey(CGKeyCode keyCode, int delay)
    {
        CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
        
        CGEventRef spaceKeyUp;
        CGEventRef spaceKeyDown;
        
        spaceKeyUp = CGEventCreateKeyboardEvent(source, keyCode, false);
        spaceKeyDown = CGEventCreateKeyboardEvent(source, keyCode, true);
        
        CGEventPost(kCGHIDEventTap, spaceKeyDown);
        usleep(delay);
        CGEventPost(kCGHIDEventTap, spaceKeyUp);
        
        CFRelease(spaceKeyUp);
        CFRelease(spaceKeyDown);
        CFRelease(source);
    }
    
    Boolean isPressed(unsigned short inKeyCode)
    {
        unsigned char keyMap[16];
        GetKeys((BigEndianUInt32*) &keyMap);
        return (0 != ((keyMap[ inKeyCode >> 3] >> (inKeyCode & 7)) & 1));
    }

    void jump()
    {
        int randomDelay = rand()%(1000 - 600 + 1) + 600;
        
        // You need to get the velocity of the player if you want
        Vector3 velo = localPlayer.vecVelocity; // comment this line if you don't want to check that the player is moving
        
        // If u press and hold Space, you are alive, you move and you are on the ground (standing or crouched) bunnyhop triggers
        if(
           velo.x != 0.0f && // comment this line if you don't want to check that the player is moving
           velo.y != 0.0f && // comment this line if you don't want to check that the player is moving
           isPressed(kVK_Space) &&
           (localPlayer.iFlags == 257 || localPlayer.iFlags == 263) &&
           localPlayer.iHealth >= 1
        )
        {
            sendKey(kVK_Space, randomDelay);
        }
    }
};
