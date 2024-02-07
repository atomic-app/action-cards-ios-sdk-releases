//
// AACCardNodeListComma.h
// AtomicSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>
#import <AtomicSDK/AACCardNodeList.h>

/**
 A specialised list subclass that renders a comma separated list.
 
 Comma separated lists render as a single component, rather than a single component
 per list item.
 */
@interface AACCardNodeListComma: AACCardNodeList

/**
 The text to display for the list.
 */
@property (nonatomic, copy, readonly) NSString *listText;

@end
