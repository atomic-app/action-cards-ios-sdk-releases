//
// AACCardNodeTextInput.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

/**
 A text input node provides a text input UI for the user.
 */
@interface AACCardNodeTextInput: AACCardNodeSubmittable

/// The text to display before editing begins.
@property (nonatomic, copy, nullable) NSString* placeholder;

/// The default value to display in the input.
@property (nonatomic, copy, nullable) NSString* defaultValue;

/// The number of lines the text input supports.
@property (nonatomic, strong, nullable) NSNumber *numberOfLines;

/// An optional image to display to the left of the text input.
@property (nonatomic, strong, nullable) NSURL* thumbnailUrl;

/**
 The total number of characters the user is permitted to enter.
 This is only used internally by the SDK currently.
 */
@property (nonatomic, copy, nullable) NSNumber *maximumLength;

@end
