//
// AACSwiftUISession.h
// AtomicSDK
// Copyright © 2024 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACAppearanceCollection.h>
#import <AtomicSDK/AACSDKEvent.h>
#import <AtomicSDK/AACSwiftUIAnalyticsEvent.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Handler called when the request for a theme completes.
 If the request succeeds, the `appearanceCollection` parameter is non-nil and the `error` parameter is nil.
 If the request fails, the `appearanceCollection` parameter is nil and the `error` parameter is non-nil.
 */
typedef void(^AACSessionAppearanceCollectionCompletionHandler)(AACAppearanceCollection* __nullable appearanceCollection, NSError* __nullable error);

/**
 A singleton designed to support the SwiftUI SDK, not meant for external use.
 */
@interface AACSwiftUISession : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 Requests an appearance collection for the stream container.
 
 If no cached appearance collection is available, the latest information is retrieved from the API, cached, and returned
 on completion.
 
 If a cached appearance collection is available, it is returned immediately, and in the background, the latest appearance
 collection for this stream container is retrieved from the theme API and cached for next use.
 
 An appearance collection includes appearances for different interface styles (e.g. light, dark), and within those,
 themes used by different parts of the SDK, as well as custom fonts that the theme utilises.
 
 @param streamContainerId The ID of the stream container to fetch appearance information for.
 @param instanceId The unique request ID to identify stream container instances.
 @param completionHandler Completion handler called when the appearance request completes. If the `error` parameter is nil, the request was successful.
 */
+ (void)appearanceCollectionWithIdentifier:(NSString *)streamContainerId
                                instanceId:(NSString *)instanceId
                         completionHandler:(AACSessionAppearanceCollectionCompletionHandler)completionHandler;

/**
 Dispatch an analytics event to the platform. The caller must ensure the payload is correctly prepared for each specific event.
 This method operates quietly, failing without notification if the event object does not satisfy validation criteria.
 
 @param event The event from SwiftUI SDK.
 */
+ (void)dispatchAnalyticsWithEventType:(AACSwiftUIAnalyticsEvent *)event;

/**
 Given a markdown string, returns an attributed string.
 
 @return An attributed string rendered from the provided markdown text.
 */
+ (NSAttributedString*)attributedStringFromMarkdown:(NSString *)markdown
                                    typographyStyle:(AACTypography *)typographyStyle
                                          textColor:(AACColor *)textColor
                                          linkColor:(AACColor *)linkColor
                            isVerticalCentreAligned:(BOOL)isVerticalCentreAligned;

@end

NS_ASSUME_NONNULL_END
