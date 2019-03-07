//
// AACSessionDelegate.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A block used to hand an authentication token back to the SDK when requested - either
 because there is no current token or that token has expired.

 @param authToken An authentication token (JWT) resolved by your application - must be
 non-nil.
 */
typedef void(^AACSessionAuthenticationTokenHandler)(NSString* __nonnull authToken);

/**
 An AACSessionDelegate supplies information to the SDK relating to the user's session.
 
 The method `cardSessionDidRequestAuthenticationTokenWithHandler:` must be implemented,
 and is used to supply an authentication token to the SDK. If you do not supply a valid
 authentication token, API requests within the SDK will fail.
 */
@protocol AACSessionDelegate <NSObject>

@required

/**
 Called when the card session has requested a authentication token to make an authenticated
 request. It is the responsibility of the implementer to ensure that the token hasn't expired,
 otherwise the API request using this token will fail.
 
 @param handler A block that you must call when an authentication token has been resolved. The sole argument
 to this block is expected to be an authentication token (JWT).
 */
- (void)cardSessionDidRequestAuthenticationTokenWithHandler:(AACSessionAuthenticationTokenHandler)handler;

@end
