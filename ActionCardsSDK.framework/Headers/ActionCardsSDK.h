//
// ActionCardsSDK.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for ActionCardsSDK.
FOUNDATION_EXPORT double ActionCardsSDKVersionNumber;

//! Project version string for ActionCardsSDK.
FOUNDATION_EXPORT const unsigned char ActionCardsSDKVersionString[];

#if __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_9_0
#error The Action Cards SDK supports iOS 9.0 and above.
#endif

#import <ActionCardsSDK/AACSessionDelegate.h>
#import <ActionCardsSDK/AACHomeViewController.h>
#import <ActionCardsSDK/AACLogger.h>
