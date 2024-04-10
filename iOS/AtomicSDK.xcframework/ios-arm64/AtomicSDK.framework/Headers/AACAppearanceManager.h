//
// AACAppearanceManager.h
// AtomicSDK
// Copyright © 2020 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACAppearanceCollection.h>

NS_ASSUME_NONNULL_BEGIN

/// The type of theme to return.
typedef NS_ENUM(NSUInteger, AACAppearanceContext) {
    /// Return the theme for the card list.
    AACAppearanceContextFeed,
    /// Return the theme for subviews.
    AACAppearanceContextSubview
};

/// Appearance styles supported by the SDK.
typedef NS_ENUM(NSUInteger, AACAppearanceStyle) {
    /// Light appearance.
    AACAppearanceStyleLight,
    /// Dark appearance.
    AACAppearanceStyleDark
};

/**
 Appearance modes supported by the SDK.
 */
typedef NS_ENUM(NSUInteger, AACAppearanceMode) {
    /// Use the system setting to determine appearance (iOS 13+; defaults to light on older versions).
    AACAppearanceModeAutomatic,
    /// Always render the stream container with a light appearance.
    AACAppearanceModeAlwaysLight,
    /// Always render the stream container with a dark appearance.
    AACAppearanceModeAlwaysDark
};

/**
 Manages the appearance of one or more views within the SDK, returning the appropriate theme for the chosen appearance
 style.
 */
@interface AACAppearanceManager: NSObject

/**
 Creates a new appearance manager from the given appearance collection, representing a set of appearances (currently
 light or dark).
 The context defines the type of theme that is returned - either card feed or subview.
 The mode defines whether the chosen appearance should be derived from the current system value (light or dark), or forced to always
 be light or dark.
 
 @param appearanceCollection The appearance collection this manager oversees.
 @param context The type of theme to return when requested.
 @param mode The mode to use when choosing the current theme.
 */
- (instancetype)initWithAppearanceCollection:(AACAppearanceCollection*)appearanceCollection
                                               context:(AACAppearanceContext)context
                                                  mode:(AACAppearanceMode)mode;

/**
 Updates the appearance style used by the appearance manager (light or dark).
 
 @param style The appearance style to use within the manager.
 */
- (void)setAppearanceStyle:(AACAppearanceStyle)style;

/**
 Notifies the appearance manager that the user's preferred content size category changed.
 This results in font sizes for themes to be recalculated to reflect the new content size category,
 provided that scaling is enabled for the typography style.
 */
- (void)contentSizeCategoryDidChange:(UIContentSizeCategory)category;

/**
 The current theme, derived from the context and current appearance style.
 */
@property (nonatomic, strong, readonly) AACTheme *theme;

/**
 The current appearance style (light or dark).
 */
@property (nonatomic, readonly) AACAppearanceStyle currentAppearanceStyle;

@end

NS_ASSUME_NONNULL_END
