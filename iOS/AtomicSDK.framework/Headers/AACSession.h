//
// AACSession.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACSessionDelegate.h>
#import <AtomicSDK/AACPushNotification.h>
#import <AtomicSDK/AACEventPayload.h>
#import <AtomicSDK/AACEventResponse.h>
#import <AtomicSDK/AACRequestDelegate.h>
#import <AtomicSDK/AACUserMetrics.h>
#import <AtomicSDK/AACEmbeddedFont.h>
#import <AtomicSDK/AACCustomEvent.h>
#import <AtomicSDK/AACUserSettings.h>
#import <AtomicSDK/AACCardFilter.h>
#import <AtomicSDK/AACSDKEvent.h>
#import <AtomicSDK/AACCardInstance.h>
#import <AtomicSDK/AACStreamContainerObserverConfiguration.h>
#import <AtomicSDK/AACSessionCardAction.h>
#import <AtomicSDK/AACAppearanceCollection.h>

/**
 Handler called whenever a card action returns a result.
 If an error occurred, the error parameter is populated with details, otherwise the error object is nil.
 */
typedef void(^AACSessionOnCardActionHandler)(NSError* __nullable error);

/**
 Handler called whenever the card feed in the observed stream container changes.
 
 @param cards The list of current cards in the observed stream container, or `nil` if the cards are not available.
 */
typedef void(^AACSessionStreamContainerChangedHandler)(NSArray<AACCardInstance*> * __nullable cards);

/**
 Handler called whenever the card count changes.
 
 @param cardCount The count of the cards in the stream container, or `nil` if the count is not available.
 */
typedef void(^AACSessionCardCountChangedHandler)(NSNumber * __nullable cardCount);

/**
 Handler called when the request to track a push notification being received completes.
 If an error occurred, the error parameter is populated with details, otherwise the error object is nil.
 */
typedef void(^AACSessionPushNotificationReceivedHandler)(NSError* __nullable error);

/**
 Handler called when the request to register for Atomic push notifications completes.
 If an error occurred, the error parameter is populated with details, otherwise the error parameter is nil.
 */
typedef void(^AACSessionPushNotificationRegistrationHandler)(NSError* __nullable error);

/**
 Handler called when the request to deregister for Atomic push notifications completes.
 If an error occurred, the error parameter is populated with details, otherwise the error parameter is nil.
 */
typedef void(^AACSessionPushNotificationDeregisterHandler)(NSError* __nullable error);

/**
 Handler called when the request to trigger an event on the Atomic Platform completes.
 If the request succeeds, the response parameter is populated with details of the event that was processed.
 If an error occurred, the error parameter is populated with details of the error that occurred.
 */
typedef void(^AACSessionSendEventHandler)(AACEventResponse* __nullable response, NSError* __nullable error);

/**
 Handler called when the request for user metrics completes.
 If the request succeeds, the `response` parameter is non-nil and the `error` parameter is nil.
 If the request fails, the `response` parameter is nil and the `error` parameter is non-nil.
 */
typedef void(^AACSessionUserMetricsHandler)(AACUserMetrics* __nullable response, NSError* __nullable error);

/**
 Handler called when an SDK event is triggered.
 
 Use `eventType` or `[sdkEvent isKindOfClass]` to determine the real type of the event.
 */
typedef void(^AACSessionSDKEventsHandler)(AACSDKEvent* __nonnull sdkEvent);

/**
 Handler called when the request to log the user out within the SDK completes.
 If the request failed, a non-nil error object is returned, with an error in the `AACSessionLogoutErrorDomain` error domain.
 Possible error codes are found in the `AACSessionLogoutErrorCode` enumeration.
 */
typedef void(^AACSessionLogoutCompletionHandler)(NSError* __nullable error);

/**
 Handler called when the request to send a custom event completes.
 If the request failed, a non-nil error object is returned, with an error in the `AACSessionSendCustomEventErrorDomain` error domain.
 Possible error codes are found in the `AACSessionSendCustomEventErrorCode` enumeration.
 */
typedef void(^AACSessionSendCustomEventCompletionHandler)(NSError* __nullable error);

/**
 Handler called when the request to update a user setting completes.
 If the request failed, a non-nil error object is returned, with an error in the `AACSessionUpdateUserErrorDomain` error domain.
 Possible error codes are found in the `AACSessionUpdateUserErrorCode` enumeration.
 */
typedef void(^AACSessionUpdateUserCompletionHandler)(NSError* __nullable error);

/**
 Notification posted when the number of cards in a stream container changes.
 
 - The notification's `object` corresponds to the stream container ID, as an NSString.
 - Use the `AACSessionCardCountUserInfoKey` key to retrieve the number of visible cards, from the notification's `userInfo` dictionary.
 - Use the `AACSessionTotalCardCountUserInfoKey` key to retrieve the total number of cards, from the notification's `userInfo` dictionary.
 */
extern NSString* __nonnull const AACSessionCardCountDidChange;

/**
 The key for an NSNumber object containing the number of cards visible in the stream container
 with the given ID.
 
 In a single card view, this value is either 1 or 0.
 */
extern NSString* __nonnull const AACSessionCardCountUserInfoKey;

/**
 The key for an NSNumber object containing the total number of cards in the stream container
 with the given ID. This can be used in single card view to determine how many cards
 in total are present in a stream, rather than how many are visible to the user.
 
 In a stream container, this value is the same as `AACSessionCardCountUserInfoKey`.
 */
extern NSString* __nonnull const AACSessionTotalCardCountUserInfoKey;

/**
 Error domain for errors arising from a failure to fetch the user metrics.
 */
extern NSString* __nonnull const AACSessionUserMetricsErrorDomain;

/**
 Error domain for errors arising from a failure to perform card actions, such as dismissing, snoozing or submitting.
 */
extern NSString* __nonnull const AACSessionCardActionsErrorDomain;

/**
 Error code associated with the card actions error domain.
 The underlying error is supplied in the `NSUnderlyingErrorKey` in the error's `userInfo` dictionary.
 */
typedef NS_ERROR_ENUM(AACSessionCardActionsErrorDomain, AACSessionCardActionsErrorCode) {
    /**
     Failed to perform card actions because the user's device was offline.
     */
    AACSessionCardActionsErrorCodeNetworkError,
    /**
     Failed to perform card actions because an internal data error has happened.
     */
    AACSessionCardActionsErrorCodeDataError
};

/**
 Error code associated with the user metrics fetching error domain.
 The underlying error is supplied in the `NSUnderlyingErrorKey` in the error's `userInfo` dictionary. 
 */
typedef NS_ERROR_ENUM(AACSessionUserMetricsErrorDomain, AACSessionUserMetricsErrorCode) {
    /**
     Failed to fetch the user metrics because the user's device was offline.
     */
    AACSessionUserMetricsErrorCodeNetworkError,
    /**
     Failed to fetch the user metrics because an internal data error has happened.
     */
    AACSessionUserMetricsErrorCodeDataError
};

/**
 Error domain for errors arising from an unsuccessful attempt to register or deregister for push
 notifications.
 */
extern NSString* __nonnull const AACSessionPushRegistrationErrorDomain;

/**
 Error codes associated with the push notification registration error domain.
 The underlying error is supplied in the `NSUnderlyingErrorKey` in the error's `userInfo` dictionary.
 */
typedef NS_ERROR_ENUM(AACSessionPushRegistrationErrorDomain, AACSessionPushRegistrationErrorCode) {
    /**
     The push notification registration request failed because the user's device was offline.
     */
    AACSessionPushRegistrationErrorCodeNetworkError,
    /**
     The push notification registration request failed because an invalid registration request was supplied.
     */
    AACSessionPushRegistrationErrorDomainDataError
};

/**
 Error domain for errors arising an unsuccessful attempt to track the push notifications delivery.
 */
extern NSString* __nonnull const AACSessionPushTrackingErrorDomain;

/**
 Error codes associated with the push notification delivery tracking error domain.
 */
typedef NS_ERROR_ENUM(AACSessionPushTrackingErrorDomain, AACSessionPushTrackingErrorCode) {
    /**
     The provided push notification payload does not represent an Atomic push notification.
     */
    AACSessionPushTrackingErrorCodeInvalidPayload = 1,
    /**
     The event, tracking push notification delivery, could not be sent to the Atomic Platform.
     */
    AACSessionPushTrackingErrorCodeFailedToSend
};

/**
 Domain for errors resulting from a failure to complete the user logout process within the SDK.
 */
extern NSString* __nonnull const AACSessionLogoutErrorDomain;

/**
 Error codes linked to the `AACSessionLogoutErrorDomain` error domain.
 */
typedef NS_ERROR_ENUM(AACSessionLogoutErrorDomain, AACSessionLogoutErrorCode) {
    /**
     The logout operation failed to send any pending analytics events to the Atomic Platform due to a network error.
     */
    AACSessionLogoutErrorCodeNetworkError,
    /**
     The logout operation failed to send any pending analytics events to the Atomic Platform due to a data error.
     */
    AACSessionLogoutErrorCodeDataError,
    /**
     The logout operation is aborted. See the `userInfo` property in the error for more details.
     */
    AACSessionLogoutErrorCodeAborted
};

/**
 Error domain for errors arising from an unsuccessful attempt to trigger an event on the platform.
 */
extern NSString* __nonnull const AACSessionSendEventErrorDomain;

/**
 Error codes associated with the event triggering error domain.
 The underlying error is supplied in the `NSUnderlyingErrorKey` in the error's `userInfo` dictionary.
 */
typedef NS_ERROR_ENUM(AACSessionSendEventErrorDomain, AACSessionSendEventErrorCode) {
    /**
     The event triggering request failed because the user's device was offline.
     */
    AACSessionSendEventErrorCodeNetworkError,
    /**
     The event triggering request failed because an invalid event payload was supplied.
     */
    AACSessionSendEventErrorCodeDataError
};

/**
 Error domain for errors arising from an unsuccessful attempt to send a custom event to the platform.
 */
extern NSString* __nonnull const AACSessionSendCustomEventErrorDomain;

/**
 Error codes associated with the custom event error domain.
 The underlying error is supplied with `NSUnderlyingErrorKey` in the error's `userInfo` dictionary.
 */
typedef NS_ERROR_ENUM(AACSessionSendCustomEventErrorDomain, AACSessionSendCustomEventErrorCode) {
    /**
     The SDK failed to send the custom event due to a network error.
     */
    AACSessionSendCustomEventErrorCodeNetworkError,
    /**
     The SDK failed to send the custom event due to a data error.
     */
    AACSessionSendCustomEventErrorCodeDataError
};

/**
 Error domain for errors arising from an unsuccessful attempt to update user information on the platform.
 */
extern NSString* __nonnull const AACSessionUpdateUserErrorDomain;

/**
 Error codes associated with the user update error domain.
 The underlying error is supplied with `NSUnderlyingErrorKey` in the error's `userInfo` dictionary.
 */
typedef NS_ERROR_ENUM(AACSessionUpdateUserErrorDomain, AACSessionUpdateUserErrorCode) {
    /**
     The SDK failed to update user due to a network error.
     */
    AACSessionUpdateUserErrorCodeNetworkError,
    /**
     The SDK failed to update user due to a data error.
     */
    AACSessionUpdateUserErrorCodeDataError
};

/**
 A singleton that spans the SDK's lifecycle, and oversees all instances of stream
 containers throughout the SDK.
 
 Sets global state such as whether logging is enabled, and supports the purging of locally cached
 data when required.
 */
@interface AACSession: NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 Registers the specified local fonts with the SDK. The fonts are defined in the theme created in the Atomic Workbench
 and integrated locally with the app.
 @param embeddedFonts The font list to be registered.
 */
+ (void)registerEmbeddedFonts:(NSArray<AACEmbeddedFont *>* __nonnull)embeddedFonts;

/**
 Configures the Atomic SDK to use the provided base URL when making API requests.
 Alternatively, you can set your API base URL in your app's `Info.plist` file, under the key
 `AACRequestBaseURL`.
 
 @param baseUrl The base URL to use, found in the Atomic Workbench.
 */
+ (void)setApiBaseUrl:(NSURL* __nonnull)baseUrl;

/**
 Supported network protocol types in the SDK.
 */
typedef NS_ENUM(NSUInteger, AACApiProtocol) {
    /// Represent the WebSockets protocol
    AACApiProtocolWebSockets,
    /// Represent the HTTP protocol
    AACApiProtocolHttp
};

/**
 Set up the network protocol used by the SDK to acquire cards. Calling it takes immediate effect.
 
 @param protocol The protocol that is going to be used by the SDK.
 */
+ (void)setApiProtocol:(AACApiProtocol)protocol;

/**
 Set up a session delegate used by the SDK to acquire an authentication token.
 The token is requested once by the SDK, and provided that the token is valid and contains a user ID, the
 token is retained in memory by the SDK until it is due to expire - at which point, a new token is requested.
 
 The SDK keeps a strong reference to the delegate until your app exits.
 
 @param sessionDelegate A delegate that supplies a user authentication token when requested by the SDK.
 */
+ (void)setSessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate;

/**
 Initialises the Atomic SDK with the provided environment ID and the API key.
 You must call this before attempting to use any Atomic SDK functionality.
 
 @param environmentId The environment ID, available in the Atomic Workbench.
 @param apiKey The API key, configured in the Atomic Workbench for this environment.
 */
+ (void)initialiseWithEnvironmentId:(NSString *__nonnull)environmentId
                             apiKey:(NSString *__nonnull)apiKey;

/**
 Sets the debug logging level within the SDK. This can be useful in debug
 builds when integrating the SDK. Defaults to `0`, which means no logs. Setting this takes immediate effect.
 
 @param level The logging message level that controls the details of logging information.
 Must be one of the following values: 0, 1, 2, 3.
 */
+ (void)enableDebugMode:(NSInteger)level;

/**
 Login to the Atomic SDK with credentials. It's the equivalent of calling `initialiseWithEnvironmentId:apiKey:`, `setSessionDelegate:` and
 `setApiBaseUrl` in sequence.
 
 @param environmentId (Required) The environment ID, available in the Atomic Workbench.
 @param apiKey (Required) The API key, configured in the Atomic Workbench for this environment.
 @param sessionDelegate (Required) A delegate that supplies a user authentication token when requested by the SDK.
 @param baseUrl (Optional) The base URL to use when making API requests, found in the Atomic Workbench.
 Alternatively, you can set your API base URL in your app's `Info.plist` file, under the key `AACRequestBaseURL`.
 */
+ (void)loginWithEnvironmentId:(NSString *__nonnull)environmentId
                        apiKey:(NSString *__nonnull)apiKey
               sessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate
                    apiBaseUrl:(NSURL* __nullable)baseUrl;

/**
 Purges all cached card data stored by the SDK, disable all SDK activities and sends any pending analytics events to the Atomic Platform.
 Call this method when a user logs out of your app or when the active user changes.
 
 - By default, push notifications will NOT be de-registered for the current user. To de-register push notifications, call `+[AACSession logoutWithNotificationsDeregistered:completionHandler:]` with the `deregisterNotifications` parameter set to `YES`.
 
 - This method invalidates existing stream containers, single card views, and card count observers but does not deallocate them in order to prevent visual flickering. For a complete log-out, you must handle deallocation yourself.
 
 - After logging out, you must log in to the SDK (by calling either `+[AACSession loginWithEnvironmentId:...]` or the appropriate initialisation methods) to proceed with another user. Otherwise, the Atomic SDK will raise exceptions.
 
 @param completionHandler (Optional) A completion handler invoked with a nil error object if any pending
 analytics events were successfully sent, or a non-nil error object if the sending of pending analytics failed.
 If the `error` object is non-nil, the error domain will be `AACSessionLogoutErrorDomain` -
 look for a specific error code in the `AACSessionLogoutErrorCode` enumeration to determine the
 cause of the error. `NSUnderlyingErrorKey` will also be populated in the error's `userInfo` dictionary.
 */
+ (void)logout:(AACSessionLogoutCompletionHandler __nullable)completionHandler;

/**
 Purges all cached card data stored by the SDK, disable all SDK activities and sends any pending analytics events to the Atomic Platform, with notifications deregistered or not.
 Call this method when a user logs out of your app or when the active user changes.
 
 - This method invalidates existing stream containers, single card views, and card count observers but does not deallocate them in order to prevent visual flickering. For a complete log-out, you must handle deallocation yourself.
 
 - After logging out, you must log in to the SDK (by calling either `+[AACSession loginWithEnvironmentId:...]` or the appropriate initialisation methods) to proceed with another user. Otherwise, the Atomic SDK will raise exceptions.
 
 @param deregisterNotifications Whether push notifications, for the current user, should also be deregistered.
 @param completionHandler (Optional) A completion handler invoked with a nil error object if any pending
 analytics events were successfully sent, or a non-nil error object if the sending of pending analytics failed.
 If the `error` object is non-nil, the error domain will be `AACSessionLogoutErrorDomain` -
 look for a specific error code in the `AACSessionLogoutErrorCode` enumeration to determine the
 cause of the error. `NSUnderlyingErrorKey` will also be populated in the error's `userInfo` dictionary.
 */
+ (void)logoutWithNotificationsDeregistered:(BOOL)deregisterNotifications
                          completionHandler:(AACSessionLogoutCompletionHandler __nullable)completionHandler;

/**
 Asks the SDK to observe the card count for the given stream container, calling the `handler` every time
 the count changes.
 
 Calling this method is the same as calling the filterable version of card count observer with a `nil` filter.
 
 @param streamContainerId (Required) The stream container ID to observe the card count for.
 @param interval (Required) How frequently the card count should be updated when the WebSockets service is not available.
 Must be at least 1 second, otherwise defaults to 1 second.
 @param handler (Required) Handler called whenever the card count changes. If the handler returns `nil`, the
 card count is not available for this stream container (the user may not have access or the internet connection
 may be unavailable).
 
 @return An opaque token that can be used to stop observing card count, by calling `+stopObservingCardCount:` with that token.
 */
+ (id<NSObject> __nonnull)observeCardCountForStreamContainerWithIdentifier:(NSString* __nonnull)streamContainerId
                                                                  interval:(NSTimeInterval)interval
                                                                   handler:(AACSessionCardCountChangedHandler __nonnull)handler;

/**
 Asks the SDK to observe the card count for the given stream container with filter(s) applied to cards, calling the `handler` every time
 the count changes.
 
 @param streamContainerId (Required) The stream container ID to observe the card count for.
 @param interval (Required) How frequently the card count should be updated when the WebSockets service is not available.
 Must be at least 1 second, otherwise defaults to 1 second.
 @param filters (Optional) An array of filters to apply or `nil` to clear the active filter.
 Filters are retrieved from static methods on `AACCardListFilter`.
 @param handler (Required) Handler called whenever the card count changes. If the handler returns `nil`, the
 card count is not available for this stream container (the user may not have access or the internet connection
 may be unavailable).
 
 @return An opaque token that can be used to stop observing card count, by calling `+stopObservingCardCount:` with that token.
 */
+ (id<NSObject> __nonnull)observeCardCountForStreamContainerWithIdentifier:(NSString* __nonnull)streamContainerId
                                                                  interval:(NSTimeInterval)interval
                                                                   filters:(NSArray<AACCardFilter*>* __nullable)filters
                                                                   handler:(AACSessionCardCountChangedHandler __nonnull)handler;

/**
 Asks the SDK to stop observing card count for the given token, which was returned from a call to
 `+observeCardCountForStreamContainerWithIdentifier:interval:handler:`. If the token does not
 correspond to a card count observer, this method does nothing.
 
 @param token The opaque token returned when registering to observe card count.
 */
+ (void)stopObservingCardCount:(id<NSObject> __nonnull)token;

/**
 Asks the SDK to return the number of cards for the given stream container, calling the `handler` when the card
 count has been determined.
 
 @param streamContainerId (Required) The stream container ID to retrieve the card count for.
 @param handler (Required) Handler called when the card count has been determined. If the handler returns `nil`, the
 card count is not available for this stream container (the user may not have access or the internet connection
 may be unavailable).
 */
+ (void)requestCardCountForStreamContainerWithIdentifier:(NSString* __nonnull)streamContainerId
                                                 handler:(AACSessionCardCountChangedHandler __nonnull)handler;

/**
 Asks the SDK to register the given device token against the currently logged in user. The logged in user
 is specified by the authentication token provided by the session delegate that is registered when initialising the SDK.
 
 @param deviceToken (Required) A device token supplied from `application:didRegisterForRemoteNotificationsWithDeviceToken:`
 in your app delegate.
 @param completionHandler (Optional) Completion handler called when the request completes. If `error` is nil,
 the request succeeded, otherwise the request failed.  If the `error` object is non-nil, the error domain will
 be `AACSessionPushRegistrationErrorDomain` - look for a specific error code in the `AACSessionPushRegistrationErrorCode`
 enumeration to determine the cause of the error. `NSUnderlyingErrorKey` will also be populated in the error's `userInfo` dictionary.
 */
+ (void)registerDeviceForNotifications:(NSData* __nonnull)deviceToken
                     completionHandler:(AACSessionPushNotificationRegistrationHandler __nullable)completionHandler;

/**
 Asks the SDK to deregister the current device for Atomic push notifications, within the current app.
 
 @param completionHandler (Optional) Completion handler called when the deregistration request completes.
 If an error occurred, the handler is passed a non-nil error object. If the `error` object is non-nil, the error domain will
 be `AACSessionPushRegistrationErrorDomain` - look for a specific error code in the `AACSessionPushRegistrationErrorCode`
 enumeration to determine the cause of the error. `NSUnderlyingErrorKey` will also be populated in the error's `userInfo` dictionary.
 */
+ (void)deregisterDeviceForNotificationsWithCompletionHandler:(AACSessionPushNotificationDeregisterHandler __nullable)completionHandler;

/**
 Asks the SDK to register the currently logged in user for push notifications on the stream container IDs in the provided
 array.
 
 Push notifications will not be delivered to a user unless they have also registered their device token (using the
 `registerDeviceForNotifications:completionHandler:`). The registration of device token and registration
 of stream container IDs can occur in either order.
 
 This method does not alter the user's `notificationsEnabled` preference in the Atomic Platform.
 
 @param streamContainerIds (Required) The stream container IDs to register the current user against for push notifications.
 Pass an empty array to unregister this device from notifications (e.g. when the user performs a complete logout from your app).
 @param completionHandler (Optional) Completion handler called when the request completes. If `error` is nil,
 the request succeeded, otherwise the request failed. If the `error` object is non-nil, the error domain will
 be `AACSessionPushRegistrationErrorDomain` - look for a specific error code in the `AACSessionPushRegistrationErrorCode`
 enumeration to determine the cause of the error. `NSUnderlyingErrorKey` will also be populated in the error's `userInfo` dictionary.
 */
+ (void)registerStreamContainersForPushNotifications:(NSArray<NSString*>* __nonnull)streamContainerIds
                                   completionHandler:(AACSessionPushNotificationRegistrationHandler __nullable)completionHandler;

/**
 Asks the SDK to register the currently logged in user for push notifications on the stream container IDs in the provided
 array with notifications enabled or disabled.
 
 Push notifications will not be delivered to a user unless they have registered their device token (using the
 `registerDeviceForNotifications:completionHandler:` method). The registration of device token and registration
 of stream container IDs can occur in either order.
 
 The `notificationsEnabled` parameter will set the user's preference in the Atomic Platform to true or false accordingly.
 
 @param streamContainerIds (Required) The stream container IDs to register the current user against for push notifications.
 Pass an empty array to unregister this device from notifications (e.g. when the user performs a complete logout from your app).
 @param notificationsEnabled (Required) Whether push notifications, for the current user, should be enabled or disabled.
 @param completionHandler (Optional) Completion handler called when the request completes. If `error` is nil,
 the request succeeded, otherwise the request failed. If the `error` object is non-nil, the error domain will
 be `AACSessionPushRegistrationErrorDomain` - look for a specific error code in the `AACSessionPushRegistrationErrorCode`
 enumeration to determine the cause of the error. `NSUnderlyingErrorKey` will also be populated in the error's `userInfo` dictionary.
 */
+ (void)registerStreamContainersForPushNotifications:(NSArray<NSString*>* __nonnull)streamContainerIds
                                notificationsEnabled:(BOOL)notificationsEnabled
                                   completionHandler:(AACSessionPushNotificationRegistrationHandler __nullable)completionHandler;

/**
 Determines whether the given push notification payload is for a push notification sent by the Atomic Platform. The push
 notification payload is provided in the userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler:
 method on `UNUserNotificationCenterDelegate`.
 
 If the push payload is for an Atomic push notification, this method returns an instance of `AACPushNotification` populated with
 details of the notification. Otherwise, it returns nil.
 */
+ (AACPushNotification* __nullable)notificationFromPushPayload:(NSDictionary* __nonnull)payload;

/**
 Tracks that a push notification, with the given payload, was received by this device.
 If the payload does not represent an Atomic push notification, this method has no effect.
 This method dispatches an analytics event back to Atomic to indicate that the user's device received the notification.
 It is the responsibility of the integrator to ensure that this method is called at the correct location to ensure accurate tracking.
 
 @param payload The push notification payload to inspect.
 @param completionHandler A completion handler called when the analytics request is complete. If the request
 fails, an NSError object is provided.
 */
+ (void)trackPushNotificationReceived:(NSDictionary* __nonnull)payload
                    completionHandler:(AACSessionPushNotificationReceivedHandler __nonnull)completionHandler;

/**
 Triggers an event on the Atomic Platform, exclusively for the user identified by the authentication token provided by the
 session delegate that is registered when initiating the SDK.
 Events must opt-in to be triggered from the SDK. To opt-in, turn on the 'Enable client trigger' option in the Atomic Workbench
 for the event.
 
 @param eventPayload The event payload used to trigger the event.
 @param completionHandler A completion handler called when the event request completes. If the request fails, an
 NSError object is provided. If the request succeeds, details of the processed event are provided.
 */
+ (void)sendEvent:(AACEventPayload* __nonnull)eventPayload withCompletionHandler:(AACSessionSendEventHandler __nonnull)completionHandler DEPRECATED_MSG_ATTRIBUTE("The sendEvent method has been deprecated and will be removed in future releases.");

#pragma mark - Network request handling

/**
 Sets a delegate that determines whether a request at a given URL is either allowed to proceed,
 not allowed to proceed or allowed to proceed provided that it passes certificate validation.
 
 Validation is performed using a set of public key hashes that this delegate returns.
 
 To revert to the default behaviour in the SDK (that is, allow all requests to proceed), you can pass
 `nil` as the argument to this method.
 
 @param delegate A global delegate that determines whether requests across the SDK can proceed.
 */
+ (void)setRequestDelegate:(id<AACRequestDelegate> __nullable)delegate;

#pragma mark - User metrics

/**
 Requests user metrics for the currently logged in user, identified by the authentication token returned by the
 session delegate that is registered when initiating the SDK. User metrics include the total number of cards available
 to the user, the number of cards that haven't yet been seen by the user, and the number of available and unseen cards
 in a specific stream container. Use the returned `AACUserMetrics` object to obtain these values.
  
 @param completionHandler Completion handler called when the request for user metrics completes.
 */
+ (void)userMetricsWithCompletionHandler:(AACSessionUserMetricsHandler __nonnull)completionHandler;

/**
 Send out a custom event to the Atomic Platform, exclusively for the user identified by the authentication token provided by the
 session delegate that is registered when initiating the SDK.
 
 Custom events are handled in the Atomic Platform.
 
 @param customEvent The event object being sent.
 @param completionHandler (Optional) A completion handler invoked with a nil error object if the custom event was successfully sent,
 or a non-nil error object if the sending failed.
 If the `error` object is non-nil, the error domain will be `AACSessionSendCustomEventErrorDomain` -
 look for a specific error code in the `AACSessionSendCustomEventErrorCode` enumeration to determine the
 cause of the error. `NSUnderlyingErrorKey` will also be populated in the error's `userInfo` dictionary.
 */
+ (void)sendCustomEvent:(AACCustomEvent* __nonnull)customEvent completionHandler:(AACSessionSendCustomEventCompletionHandler __nullable)completionHandler;

/**
 Update the user profile and preferences on the Atomic Platform, exclusively for the user identified by the authentication token provided by the
 session delegate that is registered when initiating the SDK.
 
 @param userSettings The new user settings to update to.
 @param completionHandler (Optional) A completion handler invoked with a nil error object if the update succeeded,
 or a non-nil error object if the update failed.
 If the `error` object is non-nil, the error domain will be `AACSessionUpdateUserErrorDomain` -
 look for a specific error code in the `AACSessionUpdateUserErrorCode` enumeration to determine the
 cause of the error. `NSUnderlyingErrorKey` will also be populated in the error's `userInfo` dictionary. 
 */
+ (void)updateUser:(AACUserSettings* __nonnull)userSettings completionHandler:(AACSessionUpdateUserCompletionHandler __nullable)completionHandler;

/**
 Set the current version of your app. An app version is used with analytics to make it easy to track issues between app versions and general analytics around versions.
 
 If you do not call this method, the client app version defaults to `unknown`.
 
 Strings longer than 128 characters will be trimmed to that length.
 
 @param appVersion Any string representing the app version, such as "Version 14.2 (14C18)".
 */
+ (void)setClientAppVersion:(NSString* __nonnull)appVersion;

/**
 Asks the SDK to observe SDK events, calling the `completionHandler` every time an event occurs. To stop the observation, call this method with a `nil` completion handler.
 
 An SDK event symbolises an identifiable SDK activity such as card feed changes or user interactions with cards.
 
 @param completionHandler A completion handler called whenever an SDK event occurs. Pass `nil` to this parameter to stop the observation.
 */
+ (void)observeSDKEventsWithCompletionHandler:(AACSessionSDKEventsHandler __nullable)completionHandler;

/**
 A convenient method to stop observing SDK events. This method is the equivalent of calling `observeSDKEventsWithCompletionHandler:` with a `nil` parameter.
 */
+ (void)stopObservingSDKEvents;

/**
 Asks the SDK to monitor changes in a stream container, invoking the specified `handler` whenever there are updates.
 This method can be used to track changes of the card feed within the stream container.

 @param streamContainerId (Required) The identifier of the stream container to be observed.
 @param configuration (Required) A configuration object for defining behaviour of the stream container observer.
 @param completionHandler (Required) The callback handler that is invoked whenever there is a change in the stream container.
 The handler receives updated information, or `nil` if the data is not accessible (due to reasons like lack of user access or network issues).

 @return A non-null opaque token which can be used to cease monitoring changes by passing it to the `+stopObservingStreamContainer:` method.
 */
+ (id<NSObject> __nonnull)observeStreamContainerWithIdentifier:(NSString* __nonnull)streamContainerId
                                                 configuration:(AACStreamContainerObserverConfiguration* __nullable)configuration
                                             completionHandler:(AACSessionStreamContainerChangedHandler __nonnull)completionHandler NS_SWIFT_NAME(observeStreamContainer(identifier:configuration:handler:));

/**
 Requests the SDK to cease monitoring changes in the stream container associated with the given token.
 This method stops the updates that were being sent to the handler registered via `+observeStreamContainerWithIdentifier:configuration:completionHandler:`.
 If the provided token does not correspond to an active stream container observer, this method has no effect.

 @param token The non-null opaque token obtained from `+observeStreamContainerWithIdentifier:interval:filters:handler:`. This token identifies the specific monitoring process to be stopped.
 */
+ (void)stopObservingStreamContainer:(id<NSObject> __nonnull)token NS_SWIFT_NAME(stopObservingStreamContainer(token:));

/**
 Executes the specified card action and calls the completion handler upon completion.
 Card actions include dismissing, snoozing or submitting a card.
 
 @param action The object representing a card action.
 @param completionHandler A handler block to be executed when the action is completed. This handler is called with either an error if the action fails, or nil on success.
 */
+ (void)onCardAction:(AACSessionCardAction* __nonnull)action completionHandler:(AACSessionOnCardActionHandler __nonnull)completionHandler;

@end
