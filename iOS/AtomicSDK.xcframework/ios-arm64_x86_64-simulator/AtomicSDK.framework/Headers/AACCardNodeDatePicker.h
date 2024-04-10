//
// AACCardNodeDatePicker.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

/**
 Possible formats for rendering a date picker.
 */
typedef NS_ENUM(NSUInteger, AACCardNodeDatePickerFormat) {
    /// The date picker renders with the label on the left and value on the right.
    AACCardNodeDatePickerFormatInline,
    /// The date picker renders with the label on top and value on the bottom.
    AACCardNodeDatePickerFormatStacked
};

/**
 Possible formats displayed by the date picker (either date or time).
 
 Date pickers rendered in card subviews only support dates at this stage, but internally in the SDK
 (such as the snooze screen), we use this same component but customise the ability to
 select date or time.
 */
typedef NS_ENUM(NSUInteger, AACCardNodeDatePickerMode) {
    /// Allow the user to select a date (day, month and year).
    AACCardNodeDatePickerModeDate,
    /// Allow the user to select a time (hour, minute, AM/PM). Only used internally by the SDK.
    AACCardNodeDatePickerModeTime
};

/**
 A node that renders a date picker component.
 */
@interface AACCardNodeDatePicker : AACCardNodeSubmittable

/// The label to display on the left of the date picker.
@property (nonatomic, copy, nonnull) NSString* label;

/// The minimum date that can be selected in the date picker.
@property (nonatomic, strong, nullable) NSDate *minimumValue;

/// The default date selected in the date picker, or `nil` if there is no default.
@property (nonatomic, strong, nullable) NSDate *defaultValue;

/// The maximum date that can be selected in the date picker.
@property (nonatomic, strong, nullable) NSDate *maximumValue;

/// Optional URL to a thumbnail image to display to the left of the date picker's label.
@property (nonatomic, strong, nullable) NSURL *thumbnailUrl;

/// The placeholder text to display when there is no `defaultValue` and no value has been selected.
@property (nonatomic, copy, nonnull) NSString *placeholder;

/// The format for rendering the date picker.
@property (nonatomic) AACCardNodeDatePickerFormat format;

#pragma mark - Internal SDK properties

/**
 Used internally by the SDK only. For date pickers rendered on subviews,
 defaults to date selection only.
 */
@property (nonatomic) AACCardNodeDatePickerMode mode;

/**
 Used internally by the SDK only. Sets the minute interval used for
 time selection; must be evenly divisible into 60.
 */
@property (nonatomic) NSTimeInterval minuteInterval;

@end
