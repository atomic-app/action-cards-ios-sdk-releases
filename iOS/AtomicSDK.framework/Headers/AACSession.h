//
// AACSession.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AACSessionDelegate.h"
#import "AACPushNotification.h"

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
 Handler called when the request to deregister for Atomic push notifications completes.
 If an error occurred, the error parameter is populated with details, otherwise the error parameter is nil.
 */
typedef void(^AACSessionPushNotificationDeregisterHandler)(NSError* __nullable error);

/**
 Notification posted when the number of cards in a stream container changes.
 
 - The notification's `object` corresponds to the stream container ID, as an NSString.
 - Use the `AACSessionCardCountUserInfoKey` key to retrieve the card count from the notification's `userInfo` dictionary.
 */
extern NSString* __nonnull const AACSessionCardCountDidChange;

/**
 The key for an NSNumber object containing the number of cards now in the stream container
 with the given ID.
 */
extern NSString* __nonnull const AACSessionCardCountUserInfoKey;

/**
 A singleton that spans the SDK's lifecycle, and oversees all instances of stream
 containers throughout the SDK.
 
 Sets global state such as whether logging is enabled, and supports the purging of locally cached
 data when required.
 */
@interface AACSession: NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 Initialises the Atomic SDK with the provided environment ID and API key.
 You must call this before attempting to use any Atomic SDK functionality.
 
 @param environmentId The environment ID, available in the Atomic Workbench.
 @param apiKey The API key, configured in the Atomic Workbench for this environment.
 */
+ (void)initialiseWithEnvironmentId:(NSString* __nonnull)environmentId
                             apiKey:(NSString* __nonnull)apiKey;

/**
 Sets whether debug logging should be enabled within the SDK. This can be useful in debug
 builds when integrating the SDK. Defaults to `NO`. Turning this on or off takes immediate effect.
 
 @param enabled Whether logging should be enabled within the SDK.
 */
+ (void)setLoggingEnabled:(BOOL)enabled;

/**
 Purges all cached card data stored by the SDK. Call this method when a user logs out of your app
 or the active user changes.
 */
+ (void)logout;

/**
 Asks the SDK to observe the card count for the given stream container, calling the `handler` every time
 the count changes.
 
 @param streamContainerId (Required) The stream container ID to observe the card count for.
 @param interval (Required) How frequently the card count should be updated. Must be at least 1 second,
 otherwise defaults to 1 second.
 @param sessionDelegate (Required) A delegate that supplies a user authentication token when requested
 by the SDK.
 @param handler (Required) Handler called whenever the card count changes. If the handler returns `nil`, the
 card count is not available for this stream container (the user may not have access or the internet connection
 may be unavailable).
 
 @return An opaque token that can be used to stop observing card count, by calling `+stopObservingCardCount:` with that token.
 */
+ (id<NSObject> __nonnull)observeCardCountForStreamContainerWithIdentifier:(NSString* __nonnull)streamContainerId
                                                                  interval:(NSTimeInterval)interval
                                                           sessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate
                                                                   handler:(AACSessionCardCountChangedHandler __nonnull)handler;

/**
 Asks the SDK to stop observing card count for the given token, which was returned from a call to
 `+observeCardCountForStreamContainerWithIdentifier:interval:sessionDelegate:handler:`. If the token does not
 correspond to a card count observer, this method does nothing.
 
 @param token The opaque token returned when registering to observe card count.
 */
+ (void)stopObservingCardCount:(id<NSObject> __nonnull)token;

/**
 Asks the SDK to register the given device token against the currently logged in user. The logged in user
 is specified by the authentication token provided by the session delegate.
 
 @param deviceToken (Required) A device token supplied from `application:didRegisterForRemoteNotificationsWithDeviceToken:`
 in your app delegate.
 @param sessionDelegate (Required) A delegate that supplies a user authentication token when requested by the SDK.
 */
+ (void)registerDeviceForNotifications:(NSData* __nonnull)deviceToken
                   withSessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate;

/**
 Asks the SDK to deregister the current device for Atomic push notifications, within the current app.
 
 @param completionHandler (Optional) Completion handler called when the deregistration request completes.
 If an error occurred, the handler is passed a non-nil error object.
 */
+ (void)deregisterDeviceForNotificationsWithCompletionHandler:(AACSessionPushNotificationDeregisterHandler __nullable)completionHandler;

/**
 Asks the SDK to register the currently logged in user for push notifications on the stream container IDs in the provided
 array.
 
 Push notifications will not be delivered to a user unless they have registered for push notifications first (using the above
 method). However, the registration of device token and registration of stream container IDs can occur in either order.
 
 @param streamContainerIds (Required) The stream container IDs to register the current user against for push notifications.
 Pass an empty array to unregister this device from notifications (e.g. when the user performs a complete logout from your app).
 @param sessionDelegate (Required) A delegate that supplies a user authentication token when requested by the SDK.
 */
+ (void)registerStreamContainersForPushNotifications:(NSArray<NSString*>* __nonnull)streamContainerIds
                                     sessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate;

/**
 Determines whether the given push notification payload is for a push notification sent by the Atomic Platform. The push
 notification payload is provided in the following system delegate methods:
 
 - application:didFinishLaunchingWithOptions: (the push payload is contained in UIApplicationLaunchOptionsRemoteNotificationKey);
 - application:didReceiveRemoteNotification: (iOS < 10);
 - userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler: (iOS 10+).
 
 If the push payload is for an Atomic push notification, this method returns an instance of `AACPushNotification` populated with
 details of the notification. Otherwise, it returns nil.
 */
+ (AACPushNotification* __nullable)notificationFromPushPayload:(NSDictionary* __nonnull)payload;

/**
 Tracks that a push notification, with the given payload, was received by this device.
 If the payload does not represent an Atomic push notification, this method has no effect.
 This method dispatches an analytics event back to Atomic to indicate that the user's device received the notification.
 It is the responsibiity of the integrator to ensure that this method is called at the correct location to ensure accurate tracking.
 
 @param payload The push notification payload to inspect.
 @param sessionDelegate A session delegate that provides a JWT containing the user's ID.
 @param completionHandler A completion handler called when the analytics request is complete. If the request
 fails, an NSError object is provided.
 */
+ (void)trackPushNotificationReceived:(NSDictionary* __nonnull)payload
                  withSessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate
                    completionHandler:(AACSessionPushNotificationReceivedHandler __nonnull)completionHandler;

#pragma mark - Deprecated methods

/**
 Initialises the Atomic SDK with the provided site ID and API key.
 You must call this before attempting to use any Atomic SDK functionality.
 */
+ (void)initialiseWithSiteId:(NSString* __nonnull)siteId
                      apiKey:(NSString* __nonnull)apiKey DEPRECATED_MSG_ATTRIBUTE("Use +initialiseWithEnvironmentId:apiKey: instead.");

/**
 Asks the SDK to observe the card count for the given stream container, calling the `handler` every time
 the count changes.
 */
+ (id<NSObject> __nonnull)observeCardCountForStreamContainerWithId:(NSNumber* __nonnull)streamContainerId
                                                          interval:(NSTimeInterval)interval
                                                   sessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate
                                                           handler:(AACSessionCardCountChangedHandler __nonnull)handler DEPRECATED_MSG_ATTRIBUTE("Use +observeCardCountForStreamContainerWithIdentifier:interval:sessionDelegate:handler: instead.");

/**
 Asks the SDK to register the currently logged in user for push notifications on the stream container IDs in the provided
 array.
 */
+ (void)registerStreamContainersForNotifications:(NSArray<NSNumber*>* __nonnull)streamContainerIds
                             withSessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate DEPRECATED_MSG_ATTRIBUTE("Use +registerStreamContainersForPushNotifications:sessionDelegate: instead");

@end
