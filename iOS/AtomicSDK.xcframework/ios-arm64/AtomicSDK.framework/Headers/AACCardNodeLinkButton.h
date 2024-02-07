//
// AACCardNodeLinkButton.h
// ActionCardsSDKTests
// Copyright © 2020 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACCardNode.h>

/**
 A button used to navigate to another layout, open a URL or perform a custom action.
 */
@interface AACCardNodeLinkButton: AACCardNodeButton

/**
 The name of the layout to navigate to on tap.
 If this property is `nil`, the document at `url` will be presented instead.
 */
@property (nonatomic, copy, nullable) NSString* layoutName;

@end
