//
// AACHomeViewController.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AACSessionDelegate.h"

/**
 Create an instance of this view controller to present a list of cards
 and allow the user to interact with them.
 
 This view controller currently supports being presented modally,
 as it features a 'Done' button that dismisses the screen.
 
 The navigation flow is managed entirely by this view controller.
 
 @note Do not subclass this view controller.
 */
__attribute__((objc_subclassing_restricted))
@interface AACHomeViewController : UINavigationController

/**
 Creates a new view controller that presents a list of cards.
 
 @param sessionDelegate (Required) A delegate that supplies a user authentication token when requested
 by the SDK.
 */
- (instancetype)initWithSessionDelegate:(id<AACSessionDelegate> __nonnull)sessionDelegate NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (instancetype)initWithRootViewController:(UIViewController *)rootViewController NS_UNAVAILABLE;
- (instancetype)initWithNavigationBarClass:(Class)navigationBarClass toolbarClass:(Class)toolbarClass NS_UNAVAILABLE;

@end
