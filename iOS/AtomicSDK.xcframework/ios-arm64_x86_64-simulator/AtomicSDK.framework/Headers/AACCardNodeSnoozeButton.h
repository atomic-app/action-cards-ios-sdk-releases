//
// AACCardNodeSnoozeButton.h
// AtomicSDK
// Copyright © 2022 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACCardActionButton.h>

/**
 A button used to snooze a card.
 */
@interface AACCardNodeSnoozeButton: AACCardActionButton

/**
 Represents the snooze date of a card when this button is tapped.
 If it is `nil`, a built-in UI will be brought up to select the snooze date.
 @param date The date used to combine with the snooze period to calculate a future date until which the card is snoozed.
 */
- (NSDate* __nullable)snoozeDateFromDate:(NSDate* __nonnull)date;

@end
