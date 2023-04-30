/* hello.cpp */
#include <iostream>

#include <objc/objc.h>
#include <objc/objc-runtime.h>
#include <CoreFoundation/CoreFoundation.h>

extern "C" id NSMakeRect(double x, double y, double w, double h);

extern "C" int NSRunAlertPanel(CFStringRef strTitle, CFStringRef strMsg,
                               CFStringRef strButton1, CFStringRef strButton2, 
                               CFStringRef strButton3, ...);

int main(void) {

    // Objective-C code references
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

    // cast objc_msgSend function
    id (*objc_msgSend_ptr) (id,SEL,...) = (id(*)(id,SEL,...))&objc_msgSend;

    // get NSAutoreleasePool reference
    id pool = (id)objc_getClass("NSAutoreleasePool");
    if (!pool)
    {
        std::cerr << "Unable to get NSAutoreleasePool referece!";
        return -1;
    }
    // call alloc from NSAutoreleasePool
    pool = objc_msgSend_ptr(pool, sel_registerName("alloc"));
    if (!pool)
    {
        std::cerr << "Unable to alloc NSAutoreleasePool object!";
        return -1;
    }
    // call init from NSAutoreleasePool
    pool = objc_msgSend_ptr(pool, sel_registerName("init"));

    // get NSApplication reference
    id app = objc_msgSend_ptr((id)objc_getClass("NSApplication"),
                              sel_registerName("sharedApplication"));
    if (!app)
    {
        std::cerr << "Unable to create NSApplication!";
        objc_msgSend_ptr(pool, sel_registerName("release"));
        return -1;
    }

    // get NSWindow reference
    id window = (id)objc_getClass("NSWindow");
    if (!window)
    {
        std::cerr << "Unable to get NSWindow reference!";
        objc_msgSend_ptr(pool, sel_registerName("release"));
        return -1;
    }
    window = objc_msgSend_ptr(window, sel_registerName("alloc"));
    if (!window)
    {
        std::cerr << "Unable to alloc NSWindow object";
        objc_msgSend_ptr(pool, sel_registerName("release"));
        return -1;
    }
    window = objc_msgSend_ptr(window, sel_registerName("init"));
    
    // id windowRect = NSMakeRect((double)0, (double)0, (double)640, (double)480);
    // objc_msgSend_ptr(window, sel_registerName("setFrame"), windowRect, true);

    // objc_msgSend_ptr(window, sel_registerName("setTitle"), "New Application");
    objc_msgSend_ptr(window, sel_registerName("center"));

    NSRunAlertPanel(CFSTR("Testing"),
                    CFSTR("This is a simple test to display NSAlertPanel."),
                    CFSTR("OK"), NULL, NULL);

    objc_msgSend_ptr(app, sel_registerName("run"));
    

    objc_msgSend_ptr(pool, sel_registerName("release"));
    
    return 0;
}