/* hello.cpp */
#include <iostream>

#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc.h>
#include <objc/objc-runtime.h>

int main(void) {
    // NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    // NSApplication* app = [[NSApplication alloc] init];
    // NSWindow* window = [[NSWindow alloc] 
    //     initWithContentRect: NSMakeRect(0, 0, 640, 480)
    //     styleMask: NSTitledWindowMask | NSMiniaturizableWindowMask
    //     backing: NSBackingStoreBuffered
    //     defer: NO];
    // [window setTitle: @"New Window"];
    // [window center];
    // [window makeKeyAndOrderFront:nil];
    // [app run];
    // [pool release];

    id pool = (id)objc_getClass("NSAutoreleasePool");
    if (!pool)
    {
        std::err << "Unable to get NSAutoreleasePool!\nAborting\n"
    }

    return 0;
}