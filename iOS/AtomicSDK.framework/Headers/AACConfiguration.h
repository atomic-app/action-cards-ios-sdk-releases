//
// AACConfiguration.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
@import UIKit;

/**
 Supported methods for presenting a stream container in the SDK.
 */
typedef NS_ENUM(NSUInteger, AACConfigurationPresentationStyle) {
    /**
     The stream container is being presented inside of another content view controller,
     or in a context that supplies another method of leaving the screen
     (e.g. a `UITabBarController`).
     */
    AACConfigurationPresentationStyleContent = 0,
    /**
     The stream container is being presented modally.
     This presentation style displays a 'Close' button in the top left of the
     screen to support dismissal.
     */
    AACConfigurationPresentationStyleModal
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

@end
