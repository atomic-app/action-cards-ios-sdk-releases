//
// AtomicSDK.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for Atomic SDK.
FOUNDATION_EXPORT double AtomicSDKVersionNumber;

//! Project version string for Atomic SDK.
FOUNDATION_EXPORT const unsigned char AtomicSDKVersionString[];

#if __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_9_0
#error The Atomic SDK supports iOS 9.0 and above.
#endif

#import <AtomicSDK/AACSessionDelegate.h>
#import <AtomicSDK/AACConfiguration.h>
#import <AtomicSDK/AACSingleCardConfiguration.h>
#import <AtomicSDK/AACStreamContainerViewController.h>
#import <AtomicSDK/AACSession.h>
#import <AtomicSDK/AACStreamContainerActionDelegate.h>
#import <AtomicSDK/AACPushNotification.h>
#import <AtomicSDK/AACCardCustomAction.h>

#import <AtomicSDK/AACCardInstance.h>
#import <AtomicSDK/AACCardRuntimeVariable.h>
#import <AtomicSDK/AACSingleCardView.h>
