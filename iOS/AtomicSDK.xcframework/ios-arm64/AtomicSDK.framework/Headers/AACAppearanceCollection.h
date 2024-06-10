//
// AACAppearanceCollection.h
// AtomicSDK
// Copyright © 2020 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACAppearance.h>

/**
 Represents a collection of different appearances used by the SDK (i.e. light and dark).
 */
@interface AACAppearanceCollection: NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 The default appearance to use when applying theming in the SDK (also used for light mode).
 */
@property (nonatomic, strong, readonly, nonnull) AACAppearance *defaultAppearance;

/**
 The appearance to use when the SDK is configured to run in dark mode.
 */
@property (nonatomic, strong, readonly, nullable) AACAppearance *darkAppearance;

@end
