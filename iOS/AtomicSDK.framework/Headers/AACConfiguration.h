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
     THe stream container should display an action (overflow) button in its
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
 Supports configuration of customisable elements within the SDK.
 */
@interface AACConfiguration: NSObject

/**
 The presentation style for the stream container.
 */
@property (nonatomic) AACConfigurationPresentationStyle presentationStyle;

/**
 The title to display at the top of the card list.
 If not specified, defaults to `Cards`.
 */
@property (nonatomic, copy) NSString *cardListTitle;

/**
 Optional action delegate that responds to actions triggered by the stream container.
 */
@property (nonatomic, weak) id<AACStreamContainerActionDelegate> actionDelegate;

/**
 The background colour of the view displayed when the SDK is first presented.
 */
@property (nonatomic, strong) UIColor *launchBackgroundColor;

/**
 The colour of the icon displayed when the SDK is first presented.
 */
@property (nonatomic, strong) UIColor *launchIconColor;

/**
 The tint colour of the buttons displayed if the first load of the SDK fails
 (providing the option to retry the first load request).
 */
@property (nonatomic, strong) UIColor *launchButtonColor;

/**
 The text colour to use for the view displayed when the SDK is first presented.
 */
@property (nonatomic, strong) UIColor *launchTextColor;

/**
 How often, in seconds, the list of cards in a stream container should be updated without user intervention.
 Must be greater than or equal to 1 second.
 
 If not specified, defaults to 15 seconds.
 */
@property (nonatomic) NSTimeInterval cardListRefreshInterval;

@end
