//
// AACSDKEvent.h
// AtomicSDK
// Copyright © 2023 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN

/**
 The type of observable SDK events. SDK events cover many parts of Atomic SDK activities.
 */
typedef NS_ENUM(NSUInteger, AACSDKEventType) {
    /// A card feed has been updated. It occurs when a card(s) has been removed or added to the feed, or the card(s) in the feed has been updated.
    AACSDKEventTypeCardFeedUpdated = 0,
    
    /// The user dismisses a card.
    AACSDKEventTypeCardDismissed,
    
    /// The user snoozes a card.
    AACSDKEventTypeCardSnoozed,
    
    /// The user submits a card.
    AACSDKEventTypeCardCompleted,
    
    /// A card is shown in a container.
    AACSDKEventTypeCardDisplayed,
    
    /// The user taps on the “This is useful” option in the card overflow menu.
    AACSDKEventTypeCardVotedUp,
    
    /// The user taps the “Submit” button on the card feedback screen, which is brought up by tapping on the “This isn't useful” option in the card overflow menu.
    AACSDKEventTypeCardVotedDown,
    
    /// A card containing runtime variables has one or more runtime variables resolved.
    AACSDKEventTypeRuntimeVarsUpdated,
    
    /// A stream container is first loaded or returned to.
    AACSDKEventTypeStreamDisplayed,
    
    /// The user opens a URL on a link button, opens a URL after submitting a card, or taps on a link or submit button with a custom action payload.
    AACSDKEventTypeUserRedirected,
    
    /// The snooze date/time selection UI is displayed.
    AACSDKEventTypeSnoozeOptionsDisplayed,
    
    /// The user taps the “Cancel” button in the snooze UI.
    AACSDKEventTypeSnoozeOptionsCanceled,
    
    /// The user opens a subview of a card.
    AACSDKEventTypeCardSubviewDisplayed,
    
    /// The user leaves the subview, either by navigating back or submitting the card.
    AACSDKEventTypeCardSubviewExited,
    
    /// The user hits the play button of a video.
    AACSDKEventTypeVideoPlayed,
    
    /// A video finishes playing.
    AACSDKEventTypeVideoCompleted,
    
    /// An instance of the SDK is initialized, or the JWT is refreshed.
    AACSDKEventTypeSdkInitialized,
    
    /// An API request to our client API fails in the SDK. This event is also triggered when the WebSockets failed to function and fall back to HTTP polling.
    AACSDKEventTypeRequestFailed,
    
    /// A push notification on the user's device is received by the SDK.
    /// 
    /// This event is only occurred when you call the SDK's track method. Read more in the documentation of `AACSDKEventNotificationReceived`.
    AACSDKEventTypeNotificationReceived,
    
    /// An unknown event is observed.
    AACSDKEventTypeUnknown
};

/**
 The mode of how a stream container displays cards.
 */
typedef NS_ENUM(NSUInteger, AACSDKEventStreamMode) {
    /// The stream container displays the cards vertically.
    AACSDKEventStreamModeVertical = 0,
    
    /// The stream container displays the cards horizontally.
    AACSDKEventStreamModeHorizontal,
    
    /// The stream container displays a single card only.
    AACSDKEventStreamModeSingle
};

/**
 The states that the card to be in when the event happened.
 */
typedef NS_CLOSED_ENUM(NSUInteger, AACSDKEventCardViewState) {
    /// The user was on the cards main (default) view when the event happened.
    ///
    /// The default view of a card is the card content a user sees in their stream container.
    AACSDKEventCardViewStateDefaultView,
    
    /// The user was on a subview when the event happened.
    AACSDKEventCardViewStateSubview
};

/**
 Feedback reasons that the user can choose from. Presented to the user after they taps on the “This is not useful” option in the card overflow menu.
 */
typedef NS_ENUM(NSUInteger, AACSDKEventVoteDownReason) {
    /// The user feels that the card is not relevant to them.
    AACSDKEventVoteDownReasonNotRelevant = 0,
    
    /// The user feels that they see this card too often.
    AACSDKEventVoteDownReasonTooOften,
    
    /// The user is providing free-form feedback.
    AACSDKEventVoteDownReasonOther
};

/**
 The way that the user gets redirected.
 */
typedef NS_ENUM(NSUInteger, AACSDKEventRedirectLinkMethod) {
    /// The user is redirected by a URL.
    AACSDKEventRedirectLinkMethodUrl = 0,
    
    /// The user is redirected by a custom action payload on a submit button.
    AACSDKEventRedirectLinkMethodPayload
};

/**
 The types of card components from which a user can be redirected.
 */
typedef NS_ENUM(NSUInteger, AACSDKEventRedirectDetailType) {
    /// The user is redirected from an image.
    AACSDKEventRedirectDetailTypeImage = 0,
    
    /// The user is redirected from a link button.
    AACSDKEventRedirectDetailTypeLinkButton,
    
    /// The user is redirected from a submit button.
    AACSDKEventRedirectDetailTypeSubmitButton,
    
    /// The user is redirected from a hyperlink in markdown text.
    AACSDKEventRedirectDetailTypeTextLink
};

/**
 Protocol that some events conform to. Events conforming to this protocol can happen on either the top-level or a subview of a card.
 */
@protocol AACSDKEventHasViewState <NSObject>

/**
 The view state of this event.
 */
@property (nonatomic, readonly) AACSDKEventCardViewState cardViewState;

/**
 The unique ID of a subview, which can be accessed on the subview page in the Workbench.
 Or `nil` if the view state is `AACSDKEventCardViewStateDefaultView`.
 */
@property (nonatomic, readonly, nullable) NSString *subviewId;

/**
 The level of a subview, currently only the value `1` is available.
 Or `0` if the view state is `AACSDKEventCardViewStateDefaultView`.
 */
@property (nonatomic, readonly) NSUInteger subviewLevel;

/**
 The title of a subview, which can be accessed on the subview page in the Workbench.
 Or `nil` if the view state is `AACSDKEventCardViewStateDefaultView`.
 */
@property (nonatomic, readonly, nullable) NSString *subviewTitle;

@end

/**
 Represents an SDK event. An SDK event symbolises an identifiable SDK activity such as card feed changes or user interactions with cards.

 This acts as the base class for all SDK events. For specific properties related to particular events, refer to the relevant subclass of `AACSDKEvent`.
 */
@interface AACSDKEvent: NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 The type of this event.
 */
@property (nonatomic, readonly) AACSDKEventType eventType;

/**
 The predefined name associated with this event.
 */
@property (nonatomic, readonly) NSString *eventName;

/**
 A unique identifier for this event.
 */
@property (nonatomic, readonly) NSString *eventId;

/**
 The exact timestamp when this event was triggered.
 */
@property (nonatomic, readonly) NSDate *timeStamp;

/**
 Returns the raw data of this event, presented in dictionary format.
 */
- (NSDictionary *)getRawContents;

@end

/**
 Represents an event pertaining to an authenticated action. Almost all SDK events represent an authenticated action.
 
 Direct usage of this class is not advised. Instead, use other specific event classes.
 */
@interface AACSDKEventAuthEVT : AACSDKEvent

/**
 The user ID identified by the authentication token provided by the session delegate that is registered when initiating the SDK.
 */
@property (nonatomic, readonly) NSString *endUserId;

@end

/**
 Represents an event pertaining to an Atomic stream container.
 
 Direct usage of this class is not advised. Instead, use other specific event classes.
 */
@interface AACSDKEventSTEVT : AACSDKEventAuthEVT

/**
 The ID of the stream container that the event pertains to.
 */
@property (nonatomic, readonly) NSString *streamContainerId;

@end

/**
 Represents an event pertaining to an Atomic card.
 
 Direct usage of this class is not advised. Instead, use other specific event classes.
 */
@interface AACSDKEventCREVT : AACSDKEventSTEVT

/**
 The ID of the card that the event pertains to.
 */
@property (nonatomic, readonly) NSString *cardInstanceId;

@end

/**
 Represents an event in which the user dismisses a card.
 */
@interface AACSDKEventCardDismissed : AACSDKEventCREVT
@end

/**
 Represents an event in which the user snoozes a card.
 */
@interface AACSDKEventCardSnoozed : AACSDKEventCREVT

/**
 The duration of the snooze period. Inspect each component of NSDateComponents to determine the actual length of the snooze time.
 */
@property (nonatomic, readonly) NSDateComponents *snoozePeriod;

/**
 The date and time at which the card is unsnoozed.
 */
@property (nonatomic, readonly) NSDate *unsnoozeDate;

@end

/**
 Represents an event in which the user submits a card.
 */
@interface AACSDKEventCardCompleted : AACSDKEventCREVT

/**
 The values submitted through this action. These encompass all user input contents from the input elements presented on the view at the time of submission.
 */
@property (nonatomic, readonly) NSDictionary *submittedValues;

@end

/**
 Represents an event in which a card feed has been updated.
 */
@interface AACSDKEventCardFeedUpdated : AACSDKEventSTEVT

/**
 Represents the card count of the stream container where the update happens.
 - If this event occurs within a card count observer, it will be equal to the card count returned by that observer.
 - If this event occurs within an instantiated stream container, it will be equal to the number of visible cards in that container.
 */
@property (nonatomic, readonly) NSUInteger cardCount;

@end

/**
 Represents an event in which a card is displayed in a container.
 
 This event monitors the following situations:
 - User scrolling (tracked once scrolling settles).
 - Initial load of the card list.
 - Arrival of new cards that is visible.
 
 This event does not undergo de-duplication.
 */
@interface AACSDKEventCardDisplayed : AACSDKEventCREVT
@end

/**
 Represents an event in which the user taps on the “This is useful” option in the card overflow menu.
 */
@interface AACSDKEventCardVotedUp : AACSDKEventCREVT
@end

/**
 Represents an event in which the user taps the “Submit” button on the card feedback screen, which is brought up by tapping on the “This isn't useful” option in the card overflow menu.
 */
@interface AACSDKEventCardVotedDown : AACSDKEventCREVT

/**
 The reason that the user chooses on the card feedback screen.
 */
@property (nonatomic, readonly) AACSDKEventVoteDownReason reason;

/**
 The free-form feedback provided by the user. Or `nil` if `reason` is not `AACSDKEventVoteDownReasonOther`.
 */
@property (nonatomic, readonly, nullable) NSString *otherMessage;

@end

/**
 Represents an event in which on a card containing runtime variables has one or more runtime variables resolved.
 
 This event occurs on a per-card basis.
 */
@interface AACSDKEventRuntimeVarsUpdated : AACSDKEventCREVT

/**
 The values used for all runtime variables. If a variable is not resolved by the host app for a card, its default value is reported here.
 */
@property (nonatomic, readonly) NSDictionary *resolvedVariables;

@end

/**
 Represents an event in which a stream container is first loaded or returned to.
 */
@interface AACSDKEventStreamDisplayed : AACSDKEventSTEVT

/**
 The total number of cards available in the stream container.
 */
@property (nonatomic, readonly) NSUInteger streamLength;

/**
 The total number of cards rendered by the stream container; e.g. for single card view this is 1.
 */
@property (nonatomic, readonly) NSUInteger streamLengthVisible;

/**
 The display mode of the stream container.
 */
@property (nonatomic, readonly) AACSDKEventStreamMode streamMode;

@end

/**
 Represents an event in which the user is redirected by a URL or a custom payload.
 
 The event occurs when
 - The user taps an image that is set to open a URL or has a custom action payload.
 - The user opens a URL on a link button or after submitting a card.
 - The user taps on a link or submit button with a custom action payload.
 - The user taps on a hyperlink in markdown text.
 
 This event can occur on either the top-level or subview of a card.
 */
@interface AACSDKEventUserRedirected : AACSDKEventCREVT <AACSDKEventHasViewState>

/**
 The method of the redirection.
 */
@property (nonatomic, readonly) AACSDKEventRedirectLinkMethod redirectMethod;

/**
 The URL that the user was redirected to, if a URL redirection was used.
 
 This will be `nil` if the redirection did not involve a URL (for example, if it was a custom action payload).
 */
@property (nonatomic, readonly, nullable) NSURL* redirectUrl;

/**
 Any custom action payload that was used to redirect the user.
 
 This will be `nil` if the redirection did not involve a custom action payload (for example, if it was a URL redirection).
 */
@property (nonatomic, readonly, nullable) NSDictionary *redirectPayload;

/**
 The card component from which a user gets redirected.
 */
@property (nonatomic, readonly) AACSDKEventRedirectDetailType detail;

@end

/**
 Represents an event in which the snooze date/time selection UI is displayed.
 */
@interface AACSDKEventSnoozeOptionsDisplayed : AACSDKEventCREVT
@end

/**
 Represents an event in which the user taps the “Cancel” button in the snooze UI.
 */
@interface AACSDKEventSnoozeOptionsCanceled : AACSDKEventCREVT
@end


/**
 Represents an event pertaining only to a card subview.
 
 Direct usage of this class is not advised. Instead, use other specific event classes.
 */
@interface AACSDKEventCardSubEVT : AACSDKEventCREVT

/**
 The unique ID of a subview, which can be accessed on the subview page in the Workbench.
 */
@property (nonatomic, readonly) NSString *subviewId;

/**
 The level of a subview, currently the only available value is 1.
 */
@property (nonatomic, readonly) NSUInteger subviewLevel;

/**
 The title of a subview, which can be accessed on the subview page in the Workbench.
 */
@property (nonatomic, readonly) NSString *subviewTitle;

@end

/**
 Represents an event in which a subview of card is opened.
 */
@interface AACSDKEventCardSubviewDisplayed : AACSDKEventCardSubEVT
@end

/**
 Represents an event in which the user leaves the subview, either by navigating back or submitting the card.
 */
@interface AACSDKEventCardSubviewExited : AACSDKEventCardSubEVT
@end

/**
 Represents an event pertaining only to a video.
 
 Direct usage of this class is not advised. Instead, use other specific event classes.
 */
@interface AACSDKEventVideoEvent : AACSDKEventCREVT <AACSDKEventHasViewState>

/**
 The URL of this video.
 */
@property (nonatomic, readonly) NSURL* videoUrl;

@end

/**
 Represents an event in which the user hits the play button of a video.
 
 This event can occur on either the top-level or subview of a card.
 */
@interface AACSDKEventVideoPlayed : AACSDKEventVideoEvent
@end

/**
 Represents an event in which a video finishes playing.
 
 This event can occur on either the top-level or subview of a card.
 */
@interface AACSDKEventVideoCompleted : AACSDKEventVideoEvent
@end

/**
 Represents an event in which an instance of the SDK is initialized, or the JWT is refreshed.
 */
@interface AACSDKEventSDKInitialized : AACSDKEventAuthEVT
@end

/**
 Represents an event in which any API request to the Atomic client API fails within the SDK, or a failure in WebSocket causes a fallback to HTTP polling.
 */
@interface AACSDKEventRequestFailed : AACSDKEvent

/**
 The endpoint at which the request failure occurred.
 */
@property (nonatomic, readonly) NSString *failedEndpoint;

/**
 The status code returned by the failed endpoint. `0` when this event represents a fallback to HTTP.
 */
@property (nonatomic, readonly) NSInteger failedStatusCode;

/**
 The user ID associated with the request. `nil` if the request is unauthenticated.
 */
@property (nonatomic, readonly, nullable) NSString *endUserId;

/**
 The stream container ID associated with the request. `nil` if the request isn't related to a stream container.
 */
@property (nonatomic, readonly, nullable) NSString *streamContainerId;

/**
 The card instance ID associated with the request. `nil` if the request isn't related to a specific card.
 */
@property (nonatomic, readonly, nullable) NSString *cardInstanceId;

@end

/**
 Represents an event in which a push notification on the user's device is received by the SDK.
 
 This event is only triggered when you call the method `[AACSession trackPushNotificationReceived:completionHandler:]`. Read more about tracking push notifications in the [iOS SDK guide](https://documentation.atomic.io/sdks/ios#4-optional-track-when-push-notifications-are-received).
 */
@interface AACSDKEventNotificationReceived : AACSDKEventCREVT
@end

NS_ASSUME_NONNULL_END
