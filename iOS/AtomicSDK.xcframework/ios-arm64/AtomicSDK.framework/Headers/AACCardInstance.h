//
// AACCardInstance.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AtomicSDK/AACCardRuntimeVariable.h>
#import <AtomicSDK/AACCardLayout.h>
#import <AtomicSDK/AACCardDetail.h>
#import <AtomicSDK/AACCardActionFlags.h>
#import <AtomicSDK/AACCardMetadata.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents an individual card displayed to the end user.
 */
@interface AACCardInstance: NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 The name of the event, as defined in the Atomic Workbench, that caused this card
 to be created.
 */
@property (nonatomic, readonly) NSString *eventName;

/**
 The lifecycle ID sent with the event that created this card.
 */
@property (nonatomic, readonly) NSString *lifecycleId;

/**
 All runtime variables in use by this card.
 */
@property (nonatomic, readonly) NSArray<AACCardRuntimeVariable*>* runtimeVariables;

/**
 The priority of the card, the value of which can be any number from 1 - 10, with 1 being the highest priority,
 and 10 being the lowest priority. Cards with higher priority appear higher in the card feed.
 
 For example a card with priority 3 will be ordered above a card with priority 4.
 
 If no priority is supplied, the default priority is 5.
 */
@property (nonatomic, readonly) NSInteger priority;

/**
 The last active time of the card.
 */
@property (nonatomic, readonly) NSDate* lastCardActiveTime;

/**
 Assigns the given `value` to the variable with the given `name`.
 If the variable with the given name does not exist on this card, this method does nothing for that variable.
 
 @param name The name of the variable.
 @param value The resolved, string value for that variable.
 */
- (void)resolveRuntimeVariableWithName:(NSString *)name
                                 value:(NSString *)value;

/**
 The default layout that should be used when rendering this card.
 
 @return The default layout for the card.
 */
@property (nonatomic, readonly) AACCardLayout *defaultLayout;

/**
 Returns a set of sub-layout names for this card instance, which can be used with the `layoutWithName` method.
 */
- (NSSet<NSString*>*)subLayoutNames;

/**
 Returns the layout matching the given `name`, or `nil` if no such layout
 exists for this card.
 */
- (AACCardLayout* __nullable)layoutWithName:(NSString *)name;

/**
 Returns an array of the buttons on the layout matching the given subview ID. Pass `nil` to the ID for the top-level layout.
 
 An empty array is returned if there are no buttons on the specified layout.
 
 @param subviewId The ID of the subview to retrieve the buttons for, or `nil` for the top-level layout.
 */
- (NSArray<AACCardBaseButton*>*)buttonsWithSubviewId:(NSString *__nullable)subviewId;

/**
 Information pertaining to the card's creation.
 */
@property (nonatomic, readonly) AACCardDetail *detail;

/**
 Information pertaining to the card's creation.
 */
@property (nonatomic, readonly) AACCardActionFlags *actionFlags;

/**
 Additional information relating to the card instance.
 */
@property (nonatomic, readonly) AACCardMetadata *metadata;

/**
 Whether the card has runtime variables.
 */
@property (nonatomic, readonly) BOOL hasRuntimeVariables;

@end

NS_ASSUME_NONNULL_END
