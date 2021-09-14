//
// AACEmbeddedFont.h
// AtomicSDK
// Copyright © 2021 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 Font weights supported by the SDK.
 */
typedef NS_ENUM(NSUInteger, AACFontWeight) {
    /// Regular font weight.
    AACFontWeightRegular,
    /// Bold font weight.
    AACFontWeightBold
};

/**
 Font styles supported by the SDK.
 */
typedef NS_ENUM(NSUInteger, AACFontStyle) {
    /// Normal font style (no styling applied).
    AACFontStyleNormal,
    /// Italic font style.
    AACFontStyleItalic
};

/**
 Represents an embedded font, which is integrated into the project bundle. When an embedded
 font is specified, this local font will be used instead of downloading a font file from a remote URL, 
 as specified in your stream container theme. The font family name, weight and style must match 
 exactly for an embedded font to be used.
 Steps to use an embedded font:
 1. Set up the font in a theme within the Atomic Workbench;
 2. Add the font file to the project - make sure you also include it in your app target.
 3. Call [AACSession registerEmbeddedFonts:] after the application is launched, passing an array of embedded
 fonts you wish to use.
 */
@interface AACEmbeddedFont: NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 Creates the embedded font instance with font properties.
 
 @param familyName The family name of the embedded font, as defined in your stream container's theme in the Atomic Workbench.
 @param postscriptName The postscript name of the embedded font, which can be retrieved through [UIFont fontNamesForFamilyName:].
 @param weight The weight of the font family; either `bold` or `regular`.
 @param style The style of the font family; either `italic` or `normal`.
 */
- (instancetype __nonnull)initWithFamilyName:(NSString* __nonnull)familyName
                    postscriptName:(NSString* __nonnull)postscriptName
                            weight:(AACFontWeight)weight
                             style:(AACFontStyle)style;

/**
 The family name of the embedded font, as defined in your stream container's theme in the Atomic Workbench.
 */
@property (nonatomic, readonly, nonnull) NSString *familyName;

/**
 The postscript name of the embedded font, which can be retrieved through
 [UIFont fontNamesForFamilyName:].
 */
@property (nonatomic, readonly, nonnull) NSString *postscriptName;

/**
 The weight of the font family; either `bold` or `regular`.
 */
@property (nonatomic, readonly) AACFontWeight weight;

/**
 The style of the font family; either `italic` or `normal`.
 */
@property (nonatomic, readonly) AACFontStyle style;

@end
