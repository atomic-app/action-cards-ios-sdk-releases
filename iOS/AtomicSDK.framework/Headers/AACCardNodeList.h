//
// AACCardNodeList.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

/**
 An enumeration of possible styles for lists.
 */
typedef NS_ENUM(NSUInteger, AACCardNodeListStyle) {
    /// The list is ordered (i.e. with numbered bullets).
    AACCardNodeListStyleOrdered,
    /// The list is unordered (i.e. with solid bullets).
    AACCardNodeListStyleUnordered,
    /// The list's items are separated by commas.
    AACCardNodeListStyleComma
};

/**
 A list node is a wrapper node for a collection of list items.
 */
@interface AACCardNodeList: AACCardNode

/**
 The style of list to render - either ordered or unordered.
 */
@property (nonatomic) AACCardNodeListStyle style;

@end
