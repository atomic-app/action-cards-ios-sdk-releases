//
// AACCardNodeNumberInput.h
// AtomicSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

/**
 A number input node provides a number input UI for the user.
 */
@interface AACCardNodeNumberInput: AACCardNodeSubmittable

/// The placeholder text to display before editing begins.
@property (nonatomic, copy, nullable) NSString* placeholder;

/// The default value to display in the input.
@property (nonatomic, nullable) NSDecimalNumber* defaultValue;

/// An optional image to display to the left of the number input.
@property (nonatomic, strong, nullable) NSURL* thumbnailUrl;

@end
