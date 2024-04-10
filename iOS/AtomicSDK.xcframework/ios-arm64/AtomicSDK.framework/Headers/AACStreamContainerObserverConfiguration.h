//
// AACStreamContainerObserverConfiguration.h
// AtomicSDK
// Copyright © 2023 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <AtomicSDK/AACRuntimeVariableDelegate.h>
#import <AtomicSDK/AACCardFilter.h>

/**
 Supports configuration of stream container behaviors.
 */
@interface AACStreamContainerObserverConfiguration: NSObject <NSCopying>

/**
 The frequency at which updates are checked when WebSockets service is not available.
 Defaults to 15 seconds if unspecified.
 Must be at least 1 second. If less than 1 second is specified, it defaults to 1 second.
 */
@property (nonatomic) NSTimeInterval cardListRefreshInterval;

/**
 Optional filters applied when fetching cards of the stream container, or `nil` to observe without filters.
 Filters are obtained from static methods on `AACCardListFilter`.
 */
@property (nonatomic, strong, nullable) NSArray<AACCardFilter*> *filters;

/**
 Optional runtime variable delegate that resolves runtime variable for the cards.
 */
@property (nonatomic, weak, nullable) id<AACRuntimeVariableDelegate> runtimeVariableDelegate;

/**
 The maximum amount of time allocated when resolving variables in the `-cardSessionDidRequestRuntimeVariables:completionHandler:`
 method on `AACRuntimeVariableDelegate`. If the tasks inside of the delegate method take longer than this timeout, or the completionHandler is
 not called in this time, default values will be used for all runtime variables.
 
 Defaults to 5 seconds, and cannot be negative.
 */
@property (nonatomic) NSTimeInterval runtimeVariableResolutionTimeout;

/**
 Whether the `runtime-vars-updated` analytics event, which includes resolved values of each
 runtime variable, should be sent when runtime variables are resolved. 
 
 Defaults to `NO`. When setting this flag to `YES`, ensure that the resolved values of your runtime variables
 do not include any sensitive information that should not appear in analytics.
 */
@property (nonatomic) BOOL sendRuntimeVariableAnalytics;

@end
