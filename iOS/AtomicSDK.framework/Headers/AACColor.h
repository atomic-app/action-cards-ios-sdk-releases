//
// AACColor.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 Represents a colour used by a theme.
 Colours have two components - the colour itself and the opacity.
 */
@interface AACColor: NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 The UIColor representation of this colour.
 */
- (UIColor*)colorValue;

/**
 The UIColor representation of this colour, rendered against a
 white background, so that the transparency does not show through to
 lower layers.
 */
- (UIColor*)solidColorValue;

/**
 The opacity of this colour.
 */
@property (nonatomic, readonly) CGFloat opacity;

@end
