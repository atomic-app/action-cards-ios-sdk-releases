//
// AACSession.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A singleton that spans the SDK's lifecycle, and oversees all instances of stream
 containers throughout the SDK.
 
 Sets global state such as whether logging is enabled, and supports the purging of locally cached
 data when required.
 */
@interface AACSession: NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 Sets whether debug logging should be enabled within the SDK. This can be useful in debug
 builds when integrating the SDK. Defaults to `NO`. Turning this on or off takes immediate effect.
 
 @param enabled Whether logging should be enabled within the SDK.
 */
+ (void)setLoggingEnabled:(BOOL)enabled;

/**
 Purges all cached card data stored by the SDK. Call this method when a user logs out of your app
 or the active user changes.
 */
+ (void)logout;

@end
