//
// AACCardNodeStepper.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

/**
 A card node that renders as a numeric input, with buttons on either side
 to increment or decrement the value displayed.
 */
@interface AACCardNodeStepper: AACCardNodeSubmittable

/// The label to display to the left of the stepper.
@property (nonatomic, copy, nonnull) NSString* label;

/// An optional image to display to the left of the stepper's label.
@property (nonatomic, strong, nullable) NSURL* thumbnailUrl;

/// The minimum value the stepper supports.
@property (nonatomic, copy, nonnull) NSNumber *minimumValue;

/// The maximum value the stepper supports.
@property (nonatomic, copy, nonnull) NSNumber *maximumValue;

/// The amount by which the stepper increments or decrements its value when stepped.
@property (nonatomic, copy, nonnull) NSNumber *stepValue;

/// The default value to display in the stepper.
@property (nonatomic, copy, nonnull) NSNumber *defaultValue;

@end
