//
// AACSessionDelegate.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AACCardInstance.h"

/**
 A block used to hand an authentication token back to the SDK when requested - either
 because there is no current token or that token has expired.

 @param authToken An authentication token (JWT) resolved by your application - must be
 non-nil.
 */
typedef void(^AACSessionAuthenticationTokenHandler)(NSString* __nonnull authToken);

/**
 A completion handler provided to the integrator when resolving runtime variables.
 Once you have resolved all runtime variables, this completion handler must be called with the array of resolved cards.
 
 @param resolvedCards The cards provided to the delegate, but with all variables resolved. If a variable is not
 resolved, that variable uses its default value as defined in the Atomic Workbench.
 */
typedef void(^AACSessionRuntimeVariablesHandler)(NSArray<AACCardInstance*>* __nonnull resolvedCards);

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
- (void)cardSessionDidRequestAuthenticationTokenWithHandler:(AACSessionAuthenticationTokenHandler __nonnull)handler;

@optional

/**
 An optional delegate method that can be implemented when one or more cards include runtime variables.
 If the card includes runtime variables to be resolved, the SDK will call this method to ask that you resolve them.
 If this method is not implemented, or you do not resolve a given variable, the default values for that variable
 will be used (as defined in the Atomic Workbench).
 
 Variables are resolved on each card by calling `resolveRuntimeVariableWithName:value:`.
 
 @param cardsToResolve An array of cards containing runtime variables that need to be resolved.
 @param completionHandler A completion handler to call, with a resolved array of cards, when variable resolution is complete.
 */
- (void)cardSessionDidRequestRuntimeVariables:(NSArray<AACCardInstance*>* __nonnull)cardsToResolve
                            completionHandler:(AACSessionRuntimeVariablesHandler __nonnull)completionHandler;

@end
