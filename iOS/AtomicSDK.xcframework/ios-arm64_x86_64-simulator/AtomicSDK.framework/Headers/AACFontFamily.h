//
// AACFontFamily.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACEmbeddedFont.h>

/**
 Represents a font family available for theming in the SDK.
 If `path` is nil, the font family represents the system font.
 */
@interface AACFontFamily: NSObject

/**
 The name of the font family.
 */
@property (nonatomic, copy) NSString *name;

/**
 The path to download the font family from.
 If this property is `nil`, the font family represents the system font.
 */
@property (nonatomic, copy) NSURL *path;

/**
 The weight of the font family; Can be `bold` or `regular`, or numeric values
 from 100 to 900, and 950.
 */
@property (nonatomic) AACFontWeight weight;

/**
 The style of the font family; either `italic` or `normal`.
 */
@property (nonatomic) AACFontStyle style;

@end
