//
// AACCardLayout.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AtomicSDK/AACCardNode.h>
#import <AtomicSDK/AACDeserializable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A card layout is identified by its `name` and contains a collection of nodes, which are
 rendered to the screen for a user. A card can have multiple layouts.
 */
@interface AACCardLayout: NSObject<AACDeserializable>

/**
 The title describing this layout.
 */
@property (nonatomic, copy, readonly) NSString* title;

@property (nonatomic, strong, readonly) NSArray<AACCardNode*>* nodes;

/// The instance ID of the card that this layout is linked to.
@property (nonatomic, copy) NSString *cardInstanceId;

@end

NS_ASSUME_NONNULL_END
