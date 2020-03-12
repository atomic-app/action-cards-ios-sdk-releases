//
// AACConfiguration.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
@import UIKit;

#import "AACStreamContainerActionDelegate.h"

/**
 Supported methods for presenting a stream container in the SDK.
 */
typedef NS_ENUM(NSUInteger, AACConfigurationPresentationStyle) {
    /**
     The stream container should not display a button in its top left.
     It is your responsibility to ensure that the stream container is presented
     in a way that allows the user to navigate away from it.
     */
    AACConfigurationPresentationStyleWithoutButton = 0,
    /**
     The stream container should display an action (overflow) button in its
     top left. When tapped, you will be notified via the action delegate, at which
     point you can perform your own custom action.
     */
    AACConfigurationPresentationStyleWithActionButton,
    /**
     The stream container is being presented with a button in its top left depending
     on context:
     - If presented inside of a navigation controller, a 'Back' button is presented.
     - If presented modally, a 'Close' button is presented.
     */
    AACConfigurationPresentationStyleWithContextualButton
};

/**
 The interface style (light or dark) to apply to the stream container.
 */
typedef NS_ENUM(NSUInteger, AACConfigurationInterfaceStyle) {
    /**
     The stream container will use the current system setting to determine whether the stream container should be light or dark.
     This setting only applies to devices running iOS 13 - it will fall back to AACConfigurationInterfaceStyleLight on older system versions.
     */
    AACConfigurationInterfaceStyleAutomatic,
    /**
     The stream container should always render with a light appearance.
     */
    AACConfigurationInterfaceStyleLight,
    /**
     The stream container should always render with a dark appearance.
     */
    AACConfigurationInterfaceStyleDark
};

/**
 Strings that can be customised in the SDK, by calling `-setValue:forCustomString:`.
 */
typedef NS_ENUM(NSUInteger, AACCustomString) {
    /// The title to display at the top of the card list. Defaults to `Cards`.
    AACCustomStringCardListTitle,
    /// The title to display for the card snooze functionality. Defaults to `Remind me`.
    AACCustomStringCardSnoozeTitle
};

/**
 Supports configuration of customisable elements within the SDK.
 */
@interface AACConfiguration: NSObject <NSCopying>

/**
 The presentation style for the stream container.
 */
@property (nonatomic) AACConfigurationPresentationStyle presentationStyle;

/**
 The title to display at the top of the card list.
 If not specified, defaults to `Cards`.
 
 Deprecated. Please use `-setValue:forCustomString:` instead.
 */
@property (nonatomic, copy, nonnull) NSString *cardListTitle __deprecated_msg("Use `-setValue:forCustomString:` instead.");

/**
 Optional action delegate that responds to actions triggered by the stream container.
 */
@property (nonatomic, weak, nullable) id<AACStreamContainerActionDelegate> actionDelegate;

/**
 The background colour of the view displayed when the SDK is first presented.
 */
@property (nonatomic, strong, nullable) UIColor *launchBackgroundColor;

/**
 The colour of the icon displayed when the SDK is first presented.
 */
@property (nonatomic, strong, nullable) UIColor *launchIconColor;

/**
 The tint colour of the buttons displayed if the first load of the SDK fails
 (providing the option to retry the first load request).
 */
@property (nonatomic, strong, nullable) UIColor *launchButtonColor;

/**
 The text colour to use for the view displayed when the SDK is first presented.
 */
@property (nonatomic, strong, nullable) UIColor *launchTextColor;

/**
 How often, in seconds, the list of cards in the stream container should be polled to fetch the latest data.
 Defaults to 15 seconds.
 
 - Set to `0` to disable polling for this stream container.
 - Set to `1` or more to set the polling interval in seconds.
 */
@property (nonatomic) NSTimeInterval cardListRefreshInterval;

/**
 The maximum amount of time allocated when resolving variables in the `-cardSessionDidRequestRuntimeVariables:completionHandler:`
 method on `AACSessionDelegate`. If the tasks inside of the delegate method take longer than this timeout, or the completionHandler is
 not called in this time, default values will be used for all runtime variables.
 
 Defaults to 5 seconds, and cannot be negative.
 */
@property (nonatomic) NSTimeInterval runtimeVariableResolutionTimeout;

/**
 The interface style (light or dark) to render the stream container in.
 Defaults to AACConfigurationInterfaceStyleAutomatic.
 */
@property (nonatomic) AACConfigurationInterfaceStyle interfaceStyle;

/**
 Assigns the given value to the custom string defined by the given key.
 `value` must be non-nil.
 */
- (void)setValue:(NSString* __nonnull)value forCustomString:(AACCustomString)key;

@end
