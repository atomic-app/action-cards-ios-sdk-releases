//
// AACThemeShadow.h
// ActionCardsSDK
// Copyright © 2023 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <AtomicSDK/AACMeasurement.h>
#import <AtomicSDK/AACColor.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents a shadow configuration utilised by the SDK's theme, converting the JSON values into their respective properties.
 */
@interface AACThemeShadow: NSObject

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly) AACMeasurement *blur;
@property (nonatomic, readonly) AACColor *colour;
@property (nonatomic, readonly) AACMeasurement *xAxisOffset;
@property (nonatomic, readonly) AACMeasurement *yAxisOffset;
@property (nonatomic, readonly) BOOL isInnerShadow;

@end

NS_ASSUME_NONNULL_END

