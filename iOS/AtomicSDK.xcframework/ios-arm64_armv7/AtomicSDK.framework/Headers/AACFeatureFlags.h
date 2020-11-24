//
// AACFeatureFlags.h
// AtomicSDK
// Copyright © 2020 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Represents features that can be turned on or off in the Atomic SDK.
 */
@interface AACFeatureFlags: NSObject <NSCopying>

/**
 Whether the `runtime-vars-updated` analytics event should be sent when runtime variables
 are resolved. Defaults to `YES`.
 
 If your runtime variables implementation includes sensitive data, you can set this
 feature flag to `NO` to prevent such analytics events from being sent.
 */
@property (nonatomic) BOOL runtimeVariableAnalytics;

@end
