//
// AACEdgeInsets.h
// ActionCardsSDK
// Copyright © 2023 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 Represents an edge insets used by a theme. Converting a string value
 to the built-in UIEdgeInsets object.
 */
@interface AACEdgeInsets: NSObject

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly) UIEdgeInsets edgeInsets;

@end
