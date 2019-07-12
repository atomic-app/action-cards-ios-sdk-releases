//
// AACSession.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AACSessionDelegate.h"

/**
 Completion handler called when a request for the card count in a stream container is fulfilled.
 
 @param cardCount The count of the cards in the stream container, or `nil` if the request failed.
 */
typedef void(^AACSessionCardCountCompletionHandler)(NSNumber * __nullable cardCount);

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
 Asks the SDK for a count of all cards in the stream container with the given ID.
 
 @param streamContainerId (Required) The stream container ID to return the card count for.
 @param sessionDelegate (Required) A delegate that supplies a user authentication token when requested
 by the SDK.
 @param completionHandler (Required) A completion handler called when the request for the card
 count is fulfilled.
 */
+ (void)requestCardCountForStreamContainerWithId:(NSString* __nonnull)streamContainerId
                                 sessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate
                               completionHandler:(AACSessionCardCountCompletionHandler __nonnull)completionHandler;

@end
