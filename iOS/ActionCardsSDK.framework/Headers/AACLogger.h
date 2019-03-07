//
// AACLogger.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class handles logging of debug messages within the SDK.
 
 By default, debug messages are not printed to the console. To enable debug logging,
 call `[AACLogger setLoggingEnabled:YES]`.
 */
@interface AACLogger: NSObject

/**
 Sets whether debug logging should be enabled within the SDK. This can be useful in debug
 builds when integrating the SDK. Defaults to `NO`. Turning this on or off takes immediate effect.
 
 @param enabled Whether logging should be enabled within the SDK.
 */
+ (void)setLoggingEnabled:(BOOL)enabled;

@end
