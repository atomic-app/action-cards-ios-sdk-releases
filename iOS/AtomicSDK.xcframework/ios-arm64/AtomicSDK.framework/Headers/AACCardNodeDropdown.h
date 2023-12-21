//
// AACCardNodeDropdown.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

/**
 Possible formats for rendering a dropdown.
 */
typedef NS_ENUM(NSUInteger, AACCardNodeDropdownFormat) {
    /// The dropdown renders with the label on the left and value on the right.
    AACCardNodeDropdownFormatInline,
    /// The dropdown renders with the label on top and value on the bottom.
    AACCardNodeDropdownFormatStacked
};

/**
 A value that is displayed in the dropdown.
 */
@interface AACCardNodeDropdownValue: NSObject

/// The value to send in the response payload.
@property (nonatomic, strong, nonnull) id value;

/// The title to display to the user to represent this option.
@property (nonatomic, copy, nonnull) NSString *title;

@end

/**
 A node that renders a dropdown component.
 */
@interface AACCardNodeDropdown: AACCardNodeSubmittable

/// The label to display in the dropdown, describing what the dropdown represents.
@property (nonatomic, copy, nonnull) NSString* label;

/// The default value to select in the dropdown, or `nil` if there is no default value.
@property (nonatomic, strong, nullable) id defaultValue;

/// An optional thumbnail image to display to the left of the dropdown.
@property (nonatomic, strong, nullable) NSURL *thumbnailUrl;

/// The placeholder text to display when a user has not selected a value from the dropdown and there is no default value.
@property (nonatomic, copy, nullable) NSString *placeholder;

/// The format to render the dropdown in (either inline or stacked).
@property (nonatomic) AACCardNodeDropdownFormat format;

/// The values to render in the dropdown.
@property (nonatomic, strong, nonnull) NSArray<AACCardNodeDropdownValue*>* values;

@end
