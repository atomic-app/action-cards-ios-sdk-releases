//
// AACSessionCardAction.h
// AtomicSDK
// Copyright © 2023 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Supported card actions in the SDK.
 */
typedef NS_ENUM(NSUInteger, AACSessionCardActionTypes) {
    /// Represent the action of dismissing a card.
    AACSessionCardActionTypesDismiss,
    /// Represent the action of snoozing a card.
    AACSessionCardActionTypesSnooze,
    /// Represent the action of submitting a card.
    AACSessionCardActionTypesSubmit
};

/**
 Represents a card action, encapsulating the action type and relevant identifiers.
 Card actions include dismissing, snoozing or submitting a card.
 
 Note: You MUST provide a snooze date when snoozing a card, and the date must be in the future.
 */
@interface AACSessionCardAction : NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/// Create a dismiss action to a card.
/// - Parameters:
///   - containerId: The stream container that the card belongs to.
///   - cardId: The instance ID of the card. Can be fetched through `card.detail.cardId`.
- (instancetype)initDismissActionWithContainerId:(NSString *)containerId cardId:(NSString *)cardId;

/// Create a snooze action to a card.
/// - Parameters:
///   - containerId: The stream container that the card belongs to.
///   - cardId: The instance ID of the card. Can be fetched through `card.detail.cardId`.
///   - snoozeInterval: The interval in seconds for which the card should be snoozed. The interval cannot be negative.
- (instancetype)initSnoozeActionWithContainerId:(NSString *)containerId cardId:(NSString *)cardId snoozeInterval:(NSTimeInterval)snoozeInterval;

/// Create a submit action to a card.
/// - Parameters:
///   - containerId: The stream container that the card belongs to.
///   - cardId: The instance ID of the card. Can be fetched through `card.detail.cardId`.
///   - submitButtonName: The button name of the submit button used to trigger this action. You must specify the name otherwise an error will be returned.
///   - submitValues: The response key-value pairs attached to the submit action. The key must be a string type. The value type must be string, number or boolean.
- (instancetype)initSubmitActionWithContainerId:(NSString *)containerId
                                         cardId:(NSString *)cardId
                               submitButtonName:(NSString *)submitButtonName
                                   submitValues:(NSDictionary<NSString*, id> *__nullable)submitValues;

/// The container identifier associated with the card action.
@property (nonatomic, readonly) NSString *containerId;

/// The card identifier associated with the card action.
@property (nonatomic, readonly) NSString *cardId;

/// The type of action being performed on the card.
@property (nonatomic, readonly) AACSessionCardActionTypes actionType;

/// The duration in seconds until the card is snoozed.
/// This property has no effects to other card actions.
@property (nonatomic, readonly) NSTimeInterval snoozeInterval;

/// Optional response values attached to the submit action.
@property (nonatomic, readonly, nullable) NSDictionary<NSString*, id>* submitValues;

/// The name of the submit button used to submit the card.
/// It can be retrieved from `AACCardNodeSubmitButton.buttonName`.
///
/// This property has no effects to other card actions.
@property (nonatomic, readonly, nullable) NSString *submitButtonName;

@end

NS_ASSUME_NONNULL_END
