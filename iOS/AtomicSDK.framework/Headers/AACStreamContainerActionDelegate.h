//
// AACStreamContainerActionDelegate.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AACStreamContainerViewController;

/**
 Optional delegate called when external actions are triggered in the stream container.
 */
@protocol AACStreamContainerActionDelegate <NSObject>

@optional
/**
 The user tapped on the button in the top left of the stream container.
 This method is only called when the `presentationStyle` of the stream container is set
 to `AACConfigurationPresentationStyleWithActionButton`.
 
 @param streamContainer The stream container view controller that initiated the request.
 */
- (void)streamContainerDidTapActionButton:(AACStreamContainerViewController* __nonnull)streamContainer;

@end
