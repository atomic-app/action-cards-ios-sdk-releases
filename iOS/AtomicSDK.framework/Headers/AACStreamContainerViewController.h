//
// AACStreamContainerViewController.h
// Atomic SDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AACSessionDelegate.h"
#import "AACConfiguration.h"

/**
 Creates an instance of a stream container, which renders a list of
 cards for a given stream instance. A stream container is identified by
 its ID in the Workbench.
 
 This view controller supports several methods of presentation,
 defined in the `AACConfigurationPresentationStyle` and specified via the
 `AACConfiguration` object.
 
 The navigation flow is managed entirely by this view controller.
 
 @note Do not subclass this view controller.
 */
__attribute__((objc_subclassing_restricted))
@interface AACStreamContainerViewController: UIViewController

/**
 Creates a new view controller that renders a stream container by its identifier.
 
 @param containerId (Required) The ID for this stream container, as identified in the Workbench.
 @param sessionDelegate (Required) A delegate that supplies a user authentication token when requested
 by the SDK.
 @param configuration (Required) A configuration object for defining behaviour of the stream container.
 */
- (instancetype __nonnull)initWithContainerId:(NSNumber* __nonnull)containerId
                              sessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate
                                configuration:(AACConfiguration* __nonnull)configuration NS_DESIGNATED_INITIALIZER;

- (instancetype __nonnull)init NS_UNAVAILABLE;
- (instancetype __nonnull)initWithCoder:(NSCoder* __nonnull)aDecoder NS_UNAVAILABLE;
- (instancetype __nonnull)initWithNibName:(NSString* __nullable)nibNameOrNil
                                   bundle:(NSBundle* __nullable)nibBundleOrNil NS_UNAVAILABLE;

/**
 The ID of this stream container, located in the Atomic Workbench.
 */
@property (nonatomic, copy, nonnull, readonly) NSNumber *containerId;

@end
