//
// AACMeasurement.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 Represents a point-based measurement used by the SDK, converting it from a string
 to a `CGFloat` that can be used by the UI.
 */
@interface AACMeasurement: NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 Returns the `CGFloat` representation of this measurement.
 */
- (CGFloat)pointValue;

@end
