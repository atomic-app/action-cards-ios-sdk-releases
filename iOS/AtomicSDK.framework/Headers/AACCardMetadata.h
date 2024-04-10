//
// AACCardMetadata.h
// AtomicSDK
// Copyright © 2020 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACDeserializable.h>

/**
 Display options for the icon in the top right of a card.
 */
typedef NS_ENUM(NSUInteger, AACCardMenuOption) {
    /// Display a button that opens an overflow menu for the card.
    AACCardMenuOptionOverflow,
    /// Display a button that dismisses the card, and optionally prompts for feedback.
    AACCardMenuOptionDismiss
};

/**
 Additional metadata relating to a card instance.
 */
@interface AACCardMetadata: NSObject <AACDeserializable>

/**
 The display option for the icon in the top right of a card.
 */
@property (nonatomic) AACCardMenuOption menuOption;

/**
 The priority of the card. The default value is 5.
 */
@property (nonatomic, strong, nonnull) NSNumber *priority;

/**
 The last active time of the card.
 */
@property (nonatomic, strong, nullable) NSDate *lastCardActiveTime;

/**
 The last updated time of this card.
 */
@property (nonatomic, strong, nonnull) NSDate *updatedTime;

@end
