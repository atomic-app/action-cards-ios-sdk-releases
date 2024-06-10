//
// AACAppearance.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <AtomicSDK/AACFontFamily.h>
#import <AtomicSDK/AACFeedTheme.h>
#import <AtomicSDK/AACSubviewTheme.h>

/**
 Defines the overall appearance of visual elements throughout the SDK.
 
 An appearance object encapsulates 'themes', which are styles that apply to
 a specific subset of the SDK.
 */
@interface AACAppearance : NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 An array of custom fonts that are available for use by the SDK, along with
 information on where to fetch them from, and what style they encapsulate.
 
 These font families are not currently used in the SDK.
 */
@property (nonatomic, strong, nonnull) NSArray<AACFontFamily*>* fontFamilies;

/**
 Theme configuration for the card feed (list).
 */
@property (nonatomic, strong, nonnull) AACFeedTheme *feedTheme;

/**
 Theme configuration for subviews, used for follow-up responses.
 */
@property (nonatomic, strong, nonnull) AACSubviewTheme *workflowTheme;

@end
