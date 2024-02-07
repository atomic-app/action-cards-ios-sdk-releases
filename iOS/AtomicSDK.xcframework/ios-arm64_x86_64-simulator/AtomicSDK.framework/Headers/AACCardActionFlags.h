//
// AACCardActionFlags.h
// AtomicSDK
// Copyright © 2022 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACDeserializable.h>

/**
 An object encapsulating the action flags of a particular card, including
 the flags indicating the displaying of dismissing, snoozing and voting menus.
 */
@interface AACCardActionFlags: NSObject<AACDeserializable>

@property (nonatomic, readonly) BOOL snoozeSwipeDisabled;
@property (nonatomic, readonly) BOOL snoozeOverflowDisabled;
@property (nonatomic, readonly) BOOL dismissSwipeDisabled;
@property (nonatomic, readonly) BOOL dismissOverflowDisabled;
@property (nonatomic, readonly) BOOL voteUpOverflowDisabled;
@property (nonatomic, readonly) BOOL voteDownOverflowDisabled;

@end
