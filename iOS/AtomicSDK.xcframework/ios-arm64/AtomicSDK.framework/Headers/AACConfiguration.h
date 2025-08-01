//
// AACConfiguration.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <AtomicSDK/AACStreamContainerActionDelegate.h>
#import <AtomicSDK/AACStreamContainerHeaderDelegate.h>
#import <AtomicSDK/AACCardEventDelegate.h>
#import <AtomicSDK/AACFeatureFlags.h>
#import <AtomicSDK/AACRuntimeVariableDelegate.h>

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
     This style has the same effect as `AACConfigurationPresentationStyleWithActionButton`
     in horizontal container mode.
     */
    AACConfigurationPresentationStyleWithContextualButton
};

/**
 The interface style (light or dark) to apply to the stream container.
 */
typedef NS_ENUM(NSUInteger, AACConfigurationInterfaceStyle) {
    /**
     The stream container will use the current system setting to determine whether the stream container should be light or dark.
     This setting only applies to devices running iOS 13+ - it will fall back to AACConfigurationInterfaceStyleLight on older system versions.
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
    /**
     The title to display at the top of the card list.
     Defaults to `Cards`.
     */
    AACCustomStringCardListTitle,
    /**
     The title to display for the card snooze functionality.
     Defaults to `Remind me`.
     */
    AACCustomStringCardSnoozeTitle,
    /**
     The message displayed over the card list, when the user has never received a card before.
     Defaults to `Cards will appear here when there’s something to action.`.
     */
    AACCustomStringAwaitingFirstCard,
    /**
     The message displayed when the user has received at least one card before, and there are no cards to show.
     Defaults to `All caught up`.
     */
    AACCustomStringAllCardsCompleted,
    /**
     The title to display for the action a user taps when they flag a card as useful.
     Defaults to `This is useful`.
     */
    AACCustomStringVotingUseful,
    /**
    The title to display for the action a user taps when they flag a card as not useful.
    Defaults to `This isn't useful`.
    */
    AACCustomStringVotingNotUseful,
    /**
     The title displayed at the top of the screen, allowing users to provide feedback on why they found a card useful or not.
     Defaults to `Send feedback`.
     */
    AACCustomStringVotingFeedbackTitle,
    /**
     Message to display below the last card in the card list, if there is at least 1 card present.
     Has no effect in single card view, or if `cardListFooterMessageEnabled` is set to `NO`.
     Defaults to an empty string.
     */
    AACCustomStringCardListFooterMessage,
    /**
     Message to display on the first load screen and card list when there is no internet connection.
     Defaults to `No internet connection`.
     */
    AACCustomStringNoInternetConnectionMessage,
    /**
     Message to display on the first load screen and card list when data fails to load.
     Defaults to `Couldn't load data`.
     */
    AACCustomStringDataLoadFailedMessage,
    /**
     The title for the button on the first load screen and card list, allowing the user to retry the request.
     Defaults to `Try again`.
     */
    AACCustomStringTryAgainTitle,
    /**
     Customised toast message for when the user dismisses a card - defaults to "Card dismissed".
     */
    AACCustomStringToastCardDismissedMessage,
    /**
     Customised toast message for when the user completes a card - defaults to "Card completed".
     */
    AACCustomStringToastCardCompletedMessage,
    /**
     Customised toast messages for when the user snoozes a card - defaults to "Snoozed until X" where X is the time the user dismissed the card until.
     */
    AACCustomStringToastCardSnoozeMessage,
    /**
     Customised toast message for when the user sends feedback (votes) for a card - defaults to "Feedback received".
     */
    AACCustomStringToastCardFeedbackMessage,
    /**
     The message displayed on the upload processing overlay during file upload. Defaults to "Sending, please wait...".
     */
    AACCustomStringProcessingStateMessage,
    /**
     The text displayed on the cancel button in the upload overlay during file upload. Defaults to "Cancel process".
     */
    AACCustomStringProcessingStateCancelButtonTitle,
    /**
     Customised toast message shown when file(s) fail to upload during card submission. Defaults to "Couldn't upload file(s)".
     */
    AACCustomStringToastFileUploadFailedMessage,
    /**
     Customised toast message shown when requesting camera access from the user. Defaults to "Access to your camera is required to take photos. Please enable camera access in your device settings".
     */
    AACCustomStringRequestCameraAccessMessage,
    /**
     The title for the button in the toast message prompting for camera access, which navigates to the Settings app. Defaults to `Settings`.
     */
    AACCustomStringRequestCameraAccessSettingsTitle,
    /**
     The call-to-action text displayed at the bottom of a thumbnail image element. Defaults to “View”.
     */
    AACCustomStringThumbnailImageActionLinkTitle,
    /**
     The call-to-action text displayed at the bottom of a thumbnail video element. Defaults to "Watch".
     */
    AACCustomStringThumbnailVideoActionLinkTitle
};

/**
 The voting options enabled across all cards in the stream container.
 */
typedef NS_OPTIONS(NSUInteger, AACCardVotingOption) {
    /// The user is not presented with any voting options.
    AACCardVotingOptionNone = 1 << 0,
    /// The user can vote that the card was useful.
    AACCardVotingOptionUseful = 1 << 1,
    /// The user can vote that the card was not useful, and provide optional feedback.
    AACCardVotingOptionNotUseful = 1 << 2,
};

/**
 UI elements that can be enabled on a stream container.
 */
typedef NS_OPTIONS(NSUInteger, AACUIElement) {
    /// Value indicating that none of the listed UI elements should be shown.
    AACUIElementNone = 0,
    /// Value indicating that toast messages should shown at the bottom of the screen.
    ///
    /// This setting is independent of the camera usage toast setting `AACUIElementRequestCameraUsage`.
    AACUIElementCardListToast = 1 << 0,
    /// Value indicating that the footer message should be shown beneath the last card in the list.
    AACUIElementCardListFooterMessage = 1 << 1,
    /// Value indicating that the header should be shown at the top of the card list.
    AACUIElementCardListHeader = 1 << 2,
    /// Value indicating that the SDK should display a toast message requesting camera access when camera permission has been explicitly denied.
    ///
    /// This setting is independent of the toast message setting `AACUIElementCardListToast`.
    AACUIElementRequestCameraUsage = 1 << 3,
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
 Optional action delegate that responds to actions triggered by the stream container.
 */
@property (nonatomic, weak, nullable) id<AACStreamContainerActionDelegate> actionDelegate;

/**
 Optional runtime variable delegate that resolves runtime variable for the cards.
 */
@property (nonatomic, weak, nullable) id<AACRuntimeVariableDelegate> runtimeVariableDelegate;

/**
 Optional delegate that responds to card events in the stream container.
 */
@property (nonatomic, weak, nullable) id<AACCardEventDelegate> cardEventDelegate;

/**
 Optional delegate that provides a custom header.
 */
@property (nonatomic, weak, nullable) id<AACStreamContainerHeaderDelegate> customHeaderDelegate;

/**
 The background colour of the view displayed when the SDK theme is loaded for the first time.
 */
@property (nonatomic, strong, nullable) UIColor *launchBackgroundColor;

/**
 The colour to use for the loading indicator when the SDK theme is loaded for the first time.
 */
@property (nonatomic, strong, nullable) UIColor *launchLoadingIndicatorColor;

/**
 The text colour of the button displayed if the first load of the SDK theme fails
 (providing the option to retry the request).
 
 If the `presentationStyle` property is set to a value that shows a button in the top left of the stream container,
 this colour will also be used for that button's text on the first time theme loading screen.
 */
@property (nonatomic, strong, nullable) UIColor *launchButtonColor;

/**
 The text colour to use for the message displayed if the first load of the SDK theme fails.
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
 Bitmask of user interface elements that should be enabled in the stream container.
 The default value enables toast messages, the card list header and the camera usage request toast.
 For single card view the header setting does not take effect.
 */
@property (nonatomic) AACUIElement enabledUiElements;

/**
 The maximum amount of time allocated when resolving variables in the `-cardSessionDidRequestRuntimeVariables:completionHandler:`
 method on `AACRuntimeVariableDelegate`. If the tasks inside of the delegate method take longer than this timeout, or the completionHandler is
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
 The voting options displayed for all cards in the stream container.
 Defaults to `AACCardVotingOptionNone`.
 */
@property (nonatomic) AACCardVotingOption cardVotingOptions;

/**
 Assigns the given value to the custom string defined by the given key.
 `value` must be non-nil.
 */
- (void)setValue:(NSString* __nonnull)value forCustomString:(AACCustomString)key;

/**
 Features that can be toggled on or off in the stream container.
 */
@property (nonatomic, readonly, nonnull) AACFeatureFlags *features;

/**
 Specifies the maximum width for each card displayed within the stream container. Cards will be centre-aligned.

 Defaults to `0`, indicating that the card's width will automatically adjust to match the width of the stream container.

 Constraints:

 - Setting a value less than `200` for this property is not recommended, as it may lead to layout constraint warnings. This occurs when cards cannot accommodate their content within the constrained width.

 - Negative values assigned to this property are automatically reset to `0`.
 
 - In vertical stream containers, the stream container disregards this property if its value exceeds the container's current width.
 
 - In horizontal stream containers, this property functions identically to the `cardWidth` property, and it must be > 0.
 */

 @property (nonatomic) CGFloat cardMaxWidth;

@end
