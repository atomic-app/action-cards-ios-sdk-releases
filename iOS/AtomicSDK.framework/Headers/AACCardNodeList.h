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

/// Whether this node is the first node of a card.
///
/// This property can be used to make the first list item have more top and trailing
/// spacing to make room for the action button.
///
/// This property is set during the parsing the card layout.
@property (nonatomic) BOOL isFirstNodeOfCard;

@end
