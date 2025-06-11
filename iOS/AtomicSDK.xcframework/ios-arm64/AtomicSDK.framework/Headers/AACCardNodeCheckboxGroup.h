//
// AACCardNodeCheckboxGroup.h
// ActionCardsSDK
// Copyright © 2024 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A card node that renders a selection of checkboxes. Checkbox items are stored in the `children` property.
 
 Note: Use the `itemCount` property to reference the number of checkbox items in this group. Do not assume all `children` are checkbox items.
 */
@interface AACCardNodeCheckboxGroup : AACCardNodeSubmittable

/**
 The default value of a checkbox group. The key corresponds to the `key` property of a checkbox item. The value is a BOOL indicating whether the checkbox has been activated.
 */
@property (nonatomic) NSMutableDictionary<NSString*, NSNumber*> *defaultValue;

/**
 The number of checkbox items in this group.
 */
@property (nonatomic) NSUInteger itemCount;

@end

NS_ASSUME_NONNULL_END
