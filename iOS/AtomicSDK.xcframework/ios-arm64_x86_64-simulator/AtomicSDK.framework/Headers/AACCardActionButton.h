//
// AACCardActionButton.h
// AtomicSDK
// Copyright © 2022 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACCardNode.h>

/**
 A base class for all action button nodes, reserved for future usage.
 */
@interface AACCardActionButton: AACCardBaseButton

@end


/**
 A button used to dismiss a card.
 */
@interface AACCardNodeDismissButton: AACCardActionButton

@end

/**
 A button used to vote a card up.
 */
@interface AACCardNodeVoteUpButton: AACCardActionButton

@end

/**
 A button used to vote a card down.
 */
@interface AACCardNodeVoteDownButton: AACCardNodeButton

@end
