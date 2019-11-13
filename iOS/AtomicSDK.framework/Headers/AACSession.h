//
// AACSession.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AACSessionDelegate.h"

/**
 Handler called whenever the card count changes.
 
 @param cardCount The count of the cards in the stream container, or `nil` if the count is not available.
 */
typedef void(^AACSessionCardCountChangedHandler)(NSNumber * __nullable cardCount);

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
+ (id<NSObject> __nonnull)observeCardCountForStreamContainerWithId:(NSNumber* __nonnull)streamContainerId
                                                          interval:(NSTimeInterval)interval
                                                   sessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate
                                                           handler:(AACSessionCardCountChangedHandler __nonnull)handler;

/**
 Asks the SDK to stop observing card count for the given token, which was returned from a call to
 `+observeCardCountForStreamContainerWithId:interval:sessionDelegate:handler:`. If the token does not
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
 Asks the SDK to register the currently logged in user for push notifications on the stream container IDs in the provided
 array.
 
 Push notifications will not be delivered to a user unless they have registered for push notifications first (using the above
 method). However, the registration of device token and registration of stream container IDs can occur in either order.
 
 @param streamContainerIds (Required) The stream container IDs to register the current user against for push notifications.
 Pass an empty array to unregister this device from notifications (e.g. when the user performs a complete logout from your app).
 @param sessionDelegate (Required) A delegate that supplies a user authentication token when requested by the SDK.
 */
+ (void)registerStreamContainersForNotifications:(NSArray<NSNumber*>* __nonnull)streamContainerIds
                             withSessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate;

@end
