//
// AACCardNodeListItem.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>
#import <AtomicSDK/AACCardNodeList.h>

/**
 An individual list item (i.e. an item in a bulleted or numbered list).
 */
@interface AACCardNodeListItem: AACCardNode

/// The text to display for the list item.
@property (nonatomic, copy, nonnull) NSString* text;

/// If non-empty, matched against the known icon names from the Font Awesome Pro 5 font.
@property (nonatomic, copy, nullable) NSString* icon;

/// The icon before the entire list item. Only the first item has the real icon name, the
/// following items have an empty icon.
@property (nonatomic, copy, nullable) NSString* preIcon;

/// The style to render the list item in.
@property (nonatomic) AACCardNodeListStyle style;

/// The sequence number for this item in its parent list. Applies only if the `style` is `ordered`.
@property (nonatomic) NSUInteger sequenceNumber;

/// The placeholder used to calculate the width of the list indent. The number is `9` if the max sequence number is `9`. Otherwise it's
/// `99`, `999`, etc.
@property (nonatomic) NSUInteger sequencePlaceHolder;

/// Whether this item is the last item of a list. The last item should have more bottom spacing.
/// This property is set during parsing the card layout.
@property (nonatomic) BOOL isLastItem;

@end
