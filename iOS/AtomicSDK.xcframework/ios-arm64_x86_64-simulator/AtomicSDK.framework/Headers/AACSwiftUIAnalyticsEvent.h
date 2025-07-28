//
// AACSwiftUIAnalyticsEvent.h
// AtomicSDK
// Copyright © 2024 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACSDKEvent.h>
#import <AtomicSDK/AACAppearanceCollection.h>

NS_ASSUME_NONNULL_BEGIN

/// Styles of the displaying container.
typedef NS_ENUM(NSInteger, AACSwiftUIAnalyticsEventContainerStyle) {
    /// Display all available cards in a vertical list.
    AACSwiftUIAnalyticsEventContainerStyleVertical,
    /// Display only the first card.
    AACSwiftUIAnalyticsEventContainerStyleSingle,
    /// Display all available cards in a horizontal list.
    AACSwiftUIAnalyticsEventContainerStyleHorizon
};

/**
 Analytics event that serves SwiftUI.
 */
@interface AACSwiftUIAnalyticsEvent : NSObject

/**
 Initialise the event with a specific event type. Only limited types are supported.
 */
- (instancetype)initWithEventType:(AACSDKEventType)eventType;

/// The ID of the stream container that the event occurred in.
@property (nonatomic, copy) NSString *containerId;

/// The total number of cards available for the stream container.
@property (nonatomic, copy) NSNumber *streamLength;

/// The total number of cards rendered by the stream container.
@property (nonatomic, copy) NSNumber *streamLengthVisible;

/// The position of the card this event pertains to, within the card list or single card view.
@property (nonatomic, copy) NSNumber *streamCardPosition;

/// The instance ID of the card the event pertains to.
@property (nonatomic, copy) NSString *cardInstanceId;

/// The status of the card at the time the event was generated.
@property (nonatomic, copy) NSString *cardInstanceStatus;

/// Whether the event was triggered from a vertical stream container, single card view, or a horizontal container.
@property (nonatomic) AACSwiftUIAnalyticsEventContainerStyle containerStyle;

/// The payload related to this event.
@property (nonatomic) NSDictionary *eventPayload;

@end

NS_ASSUME_NONNULL_END
