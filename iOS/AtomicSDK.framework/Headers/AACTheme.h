//
// AACTheme.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACColor.h>
#import <AtomicSDK/AACTypography.h>
#import <AtomicSDK/AACMeasurement.h>
#import <AtomicSDK/AACCardNode.h>
#import <AtomicSDK/AACEdgeInsets.h>
#import <AtomicSDK/AACThemeShadow.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The button types of both top and subview level buttons.
 */
typedef NS_ENUM(NSInteger, AACThemeButtonLayout) {
    AACThemeButtonLayoutVertical,
    AACThemeButtonLayoutHorizontal,
};

/**
 The button types of both top and subview level buttons.
 */
typedef NS_ENUM(NSInteger, AACThemeButtonFits) {
    AACThemeButtonFitsContainer,
    AACThemeButtonFitsLabel,
};

/**
 The alignment types of theme elements, note some elements only have two alignments.
 */
typedef NS_ENUM(NSInteger, AACThemeAlignment) {
    AACThemeAlignmentLeft,
    AACThemeAlignmentRight,
    AACThemeAlignmentCenter
};

/**
 Represents a theme that is rendered in a part of the SDK.
 A theme encapsulates colours, text styles and measured values (such as the border radius
 on elements) to create a visual style.
 
 Themes can apply to different sections of the SDK; e.g. either the card list or the subview
 screen.
 */
@interface AACTheme : NSObject

- (instancetype)init NS_UNAVAILABLE;

#pragma mark - Colours

- (AACColor *)backgroundButton:(AACCardButtonType)buttonType;
- (AACColor *)backgroundButtonBorder:(AACCardButtonType)buttonType;

@property (nonatomic, strong) AACColor *borderCard;
@property (nonatomic, strong) AACColor *borderMedia;
@property (nonatomic, strong) AACColor *borderComponent;
@property (nonatomic, strong) AACColor *borderSheetItemDivider;

@property (nonatomic, strong) AACColor *backgroundDefault;
@property (nonatomic, strong) AACColor *backgroundCard;
@property (nonatomic, strong) AACColor *backgroundMedia;
@property (nonatomic, strong) AACColor *backgroundMediaThumbnail;
@property (nonatomic, strong) AACColor *backgroundMediaControl;
@property (nonatomic, strong) AACColor *backgroundCardCompletion;
@property (nonatomic, strong) AACColor *backgroundToast;
@property (nonatomic, strong) AACColor *backgroundQuickActionPrimary;
@property (nonatomic, strong) AACColor *backgroundQuickActionSecondary;
@property (nonatomic, strong) AACColor *backgroundStepper;
@property (nonatomic, strong) AACColor *backgroundStepperDisabled;
@property (nonatomic, strong) AACColor *backgroundComponent;
@property (nonatomic, strong) AACColor *backgroundSwitchOn;
@property (nonatomic, strong) AACColor *backgroundSwitchOff;
@property (nonatomic, strong) AACColor *backgroundOptionsActive;
@property (nonatomic, strong) AACColor *backgroundSheet;
@property (nonatomic, strong) AACColor *backgroundSheetItemActive;
@property (nonatomic, strong) AACColor *backgroundNavigation;
@property (nonatomic, strong) AACColor *backgroundBanner;
@property (nonatomic, strong) AACColor *backgroundOptions;

- (AACColor *)textButton:(AACCardButtonType)buttonType;
@property (nonatomic, strong) AACColor *textListTitle;
@property (nonatomic, strong) AACColor *textCategory;
@property (nonatomic, strong) AACColor *textHeadline;
@property (nonatomic, strong) AACColor *textBody;
@property (nonatomic, strong) AACColor *textLink;
@property (nonatomic, strong) AACColor *textMediaTitle;
@property (nonatomic, strong) AACColor *textMediaSubtitle;
@property (nonatomic, strong) AACColor *textMediaAction;
@property (nonatomic, strong) AACColor *textToast;
@property (nonatomic, strong) AACColor *textPrimary;
@property (nonatomic, strong) AACColor *textError;
@property (nonatomic, strong) AACColor *textHint;
@property (nonatomic, strong) AACColor *textSecondary;
@property (nonatomic, strong) AACColor *textPinned;
@property (nonatomic, strong) AACColor *textSheetItem;
@property (nonatomic, strong) AACColor *textSheetItemActive;
@property (nonatomic, strong) AACColor *textNavigationTitle;
@property (nonatomic, strong) AACColor *textNavigationAction;
@property (nonatomic, strong) AACColor *textBanner;
@property (nonatomic, strong) AACColor *textToastAction;
@property (nonatomic, strong) AACColor *textErrorOverlayTitle;
@property (nonatomic, strong) AACColor *textErrorOverlayAction;
@property (nonatomic, strong) AACColor *textListEmptyState;
@property (nonatomic, strong) AACColor *textFooterMessage;

- (AACColor *)iconButton:(AACCardButtonType)buttonType;
@property (nonatomic, strong) AACColor *iconOptions;
@property (nonatomic, strong) AACColor *iconOptionsActive;
@property (nonatomic, strong) AACColor *iconBody;
@property (nonatomic, strong) AACColor *iconListAction;
@property (nonatomic, strong) AACColor *iconMediaBanner;
@property (nonatomic, strong) AACColor *iconMediaControl;
@property (nonatomic, strong) AACColor *iconBullet;
@property (nonatomic, strong) AACColor *iconLoadingSpinner;
@property (nonatomic, strong) AACColor *iconCardCompletion;
@property (nonatomic, strong) AACColor *iconQuickActionPrimary;
@property (nonatomic, strong) AACColor *iconQuickActionSecondary;
@property (nonatomic, strong) AACColor *iconStepper;
@property (nonatomic, strong) AACColor *iconStepperDisabled;
@property (nonatomic, strong) AACColor *iconSwitchOn;
@property (nonatomic, strong) AACColor *iconSwitchOff;
@property (nonatomic, strong) AACColor *iconDropdown;
@property (nonatomic, strong) AACColor *iconSheetItem;
@property (nonatomic, strong) AACColor *iconSheetItemActive;
@property (nonatomic, strong) AACColor *iconListEmptyState;
@property (nonatomic, strong) AACColor *iconSelectionIndicatorActive;

@property (nonatomic, strong) AACColor *shadowCard;
@property (nonatomic, strong) AACColor *shadowNavigation;

@property (nonatomic, strong) AACColor *overlayMediaBanner;
@property (nonatomic, strong) AACColor *overlaySheet;

#pragma mark - Typography
- (AACTypography *)typographyButton:(AACCardButtonType)buttonType;
- (AACThemeAlignment)buttonTitleAlign:(AACCardButtonType)buttonType;

@property (nonatomic, strong) AACTypography *typographyListTitle;
@property (nonatomic, strong) AACTypography *typographyCategory;
@property (nonatomic, strong) AACTypography *typographyHeadline;
@property (nonatomic, strong) AACTypography *typographyBody;
@property (nonatomic, strong) AACTypography *typographyBullet;
@property (nonatomic, strong) AACTypography *typographyMediaTitle;
@property (nonatomic, strong) AACTypography *typographyMediaSubtitle;
@property (nonatomic, strong) AACTypography *typographyMediaAction;
@property (nonatomic, strong) AACTypography *typographyMediaTruncation;
@property (nonatomic, strong) AACTypography *typographyToast;
@property (nonatomic, strong) AACTypography *typographyPrimary;
@property (nonatomic, strong) AACTypography *typographySecondary;
@property (nonatomic, strong) AACTypography *typographyPinned;
@property (nonatomic, strong) AACTypography *typographySheetItem;
@property (nonatomic, strong) AACTypography *typographyError;
@property (nonatomic, strong) AACTypography *typographyNavigationTitle;
@property (nonatomic, strong) AACTypography *typographyNavigationAction;
@property (nonatomic, strong) AACTypography *typographyBanner;
@property (nonatomic, strong) AACTypography *typographyToastAction;
@property (nonatomic, strong) AACTypography *typographyErrorOverlayTitle;
@property (nonatomic, strong) AACTypography *typographyErrorOverlayAction;
@property (nonatomic, strong) AACTypography *typographyListEmptyState;
@property (nonatomic, strong) AACTypography *typographyFooterMessage;

#pragma mark - Shape
- (AACMeasurement *)borderRadiusButton:(AACCardButtonType)buttonType;
- (AACMeasurement *)borderWidthButton:(AACCardButtonType)buttonType;
- (AACEdgeInsets *)paddingsButton:(AACCardButtonType)buttonType;
- (AACMeasurement *)lineHeightButtonIcon:(AACCardButtonType)buttonType;
/**
 Button icon alignment only has left and right alignment.
 */
- (AACThemeAlignment)buttonIconAlign:(AACCardButtonType)buttonType;

@property (nonatomic) AACThemeButtonFits buttonFits;
@property (nonatomic) AACThemeButtonLayout buttonLayout;
@property (nonatomic) AACThemeAlignment buttonAlignment;
@property (nonatomic, strong) AACMeasurement *buttonSpacingAfter;
@property (nonatomic, strong) AACMeasurement *blurCardShadow;
@property (nonatomic, strong) AACMeasurement *offsetCardShadow;
@property (nonatomic, strong) AACMeasurement *blurNavigationShadow;
@property (nonatomic, strong) AACMeasurement *offsetNavigationShadow;

@property (nonatomic, strong) AACMeasurement *borderRadiusCard;
@property (nonatomic, strong) AACMeasurement *borderRadiusMedia;
@property (nonatomic, strong) AACMeasurement *borderRadiusSheet;

@property (nonatomic, strong) AACMeasurement *borderWidthCard;

#pragma mark - Button shadow
- (AACThemeShadow *)shadowButton:(AACCardButtonType)buttonType;

@end

NS_ASSUME_NONNULL_END
