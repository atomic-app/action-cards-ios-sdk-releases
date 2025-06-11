//
// AACTypography.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The transform style used by a typography style.
 */
typedef NS_ENUM(NSUInteger, AACTypographyTransform) {
    /// There are no transforms applied.
    AACTypographyTransformNone,
    /// The characters are converted to upper case.
    AACTypographyTransformUppercase
};

/**
 Allows consumers of typography styles to pass additional options
 when generating an attributed string from that style.
 
 This effectively acts as a wrapper for `NSAttributedString` to make
 passing of additional options easier.
 
 See also: -[AACTypography attributedStringForString:options:]
 */
@interface AACTypographyRenderingOptions: NSObject

@property (nonatomic, readonly) NSString *key;

/**
 The text alignment to use (defaults to `NSTextAlignmentLeft`).
 */
@property (nonatomic) NSTextAlignment textAlignment;

/**
 The indentation of the first line of the paragraph.
 */
@property (nonatomic) CGFloat firstLineHeadIndent;

/**
 The trailing indentation of the paragraph.
 */
@property (nonatomic) CGFloat tailIndent;

/**
 The text color to render the attributed string in.
 If `nil`, the text color is ignored.
 */
@property (nonatomic, strong) UIColor *textColor;

/**
 The line break mode to apply to the attributed string.
 Defaults to `NSLineBreakByWordWrapping`.
 */
@property (nonatomic) NSLineBreakMode lineBreakMode;

/**
 The maximum font size that can be used when rendering the attributed string.
 */
@property (nonatomic) CGFloat maximumFontSize;

/**
 Whether the baseline of the attributed string should be adjusted, such that the text on each line
 is centred vertically within the bounds of the line after the line height is applied.
 This functionality is currently opt-in. Defaults to `NO`.
 */
@property (nonatomic) BOOL verticalCenteringEnabled;

@end

/**
 Represents a typography style used by the SDK.
 Typography styles encapsulate a weight, style and font size.
 
 The weight and style are used to find a corresponding font from the list
 of font families exposed to the SDK in the `AACAppearance` object.
 */
@interface AACTypography: NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 A name used to identify this font's family.
 */
- (NSString*)fontFamilyName;

/**
 This typography style represented as a `UIFont` instance.
 */
- (UIFont*)fontValue;

/**
 The font size the typography style should be rendered in.
 */
- (CGFloat)fontSizeValue;

/**
 The line height to use for text rendered in the given typography style,
 in points.
 */
- (CGFloat)lineHeightValue;

/**
 The line height multiple defined in Atomic Workbench.
 */
- (CGFloat)lineHeightMultiple;

/**
 The transform style used before displaying the text.
 */
@property (nonatomic, readonly) AACTypographyTransform transform;

/**
 Applies attributes necessary to render the given string in the style dictated
 by this typography style.
 
 @param string The string to render.
 @param options Additional rendering options to apply to the returned attributed string.
 */
- (NSAttributedString*)attributedStringForString:(NSString*)string
                                         options:(AACTypographyRenderingOptions* __nullable)options;

/**
 Returns a dictionary of all attributes that must be applied to render this
 typography style.
 
 @param options Additional rendering options to apply when generating the attributes dictionary.
 */
- (NSDictionary*)attributesWithOptions:(AACTypographyRenderingOptions* __nullable)options;

@end

NS_ASSUME_NONNULL_END
