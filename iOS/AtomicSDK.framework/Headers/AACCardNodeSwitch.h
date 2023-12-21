//
// AACCardNodeSwitch.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

/**
 A node that renders a switch, which the user can toggle on or off.
 */
@interface AACCardNodeSwitch: AACCardNodeSubmittable

/// The label to display next to the switch.
@property (nonatomic, copy, nonnull) NSString *label;

/// An optional image to display to the left of the switch's label.
@property (nonatomic, strong, nullable) NSURL* thumbnailUrl;

/// The default value of the switch.
@property (nonatomic) BOOL defaultValue;

@end
