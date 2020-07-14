//
// AACSingleCardView.h
// AtomicSDK
// Copyright © 2020 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AACSessionDelegate.h"
#import "AACConfiguration.h"

@class AACSingleCardView;

/**
 Delegate that responds to events in the single card view.
 */
@protocol AACSingleCardViewDelegate <NSObject>

@optional
/**
 The single card view is about to change to the provided size, as a result of a card
 appearing due to polling, being dismissed, snoozed or disappearing due to polling.
 
 @param cardView The single card view affected by the change.
 @param newSize The new size of the single card view.
 */
- (void)singleCardView:(AACSingleCardView* __nonnull)cardView
        willChangeSize:(CGSize)newSize;

@end

/**
 A view designed to display a single card (the first in the user's stream).
 */
@interface AACSingleCardView: UIView

- (instancetype __nonnull)init NS_UNAVAILABLE;
- (instancetype __nonnull)initWithFrame:(CGRect)frame NS_UNAVAILABLE;
- (instancetype __nonnull)initWithCoder:(NSCoder* __nonnull)coder NS_UNAVAILABLE;

/**
 Creates a new view for displaying a single card.
 
 @param frame The initial size of the single card view. Its `intrinsicSize` is updated when the card view resizes.
 @param containerId The ID of the stream container to render the first card from.
 @param sessionDelegate A session delegate that provides a user's JWT and resolves runtime variables.
 @param configuration Stream container configuration to apply to this single card view.
 */
- (instancetype __nonnull)initWithFrame:(CGRect)frame
                    containerIdentifier:(NSString* __nonnull)containerId
                        sessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate
                          configuration:(AACConfiguration* __nonnull)configuration;

/**
 Delegate that responds to events in the single card view.
*/
@property (nonatomic, weak, nullable) id<AACSingleCardViewDelegate> delegate;

/**
 Requests that runtime variables, across the single card view, be updated.
 Must be called from the main thread.
 */
- (void)updateVariables;

#pragma mark - Deprecated methods
/**
 Creates a new view for displaying a single card.
 */
- (instancetype __nonnull)initWithFrame:(CGRect)frame
                            containerId:(NSNumber* __nonnull)containerId
                        sessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate
                          configuration:(AACConfiguration* __nonnull)configuration DEPRECATED_MSG_ATTRIBUTE("Use -initWithFrame:containerIdentifier:sessionDelegate:configuration: instead.");

@end
