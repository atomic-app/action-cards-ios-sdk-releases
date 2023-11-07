# iOS SDK

## Introduction

The Atomic iOS SDK is a dynamic framework for integrating an Atomic stream container into your iOS app, presenting cards from a stream to your end users.

The SDK is written in Objective-C and supports iOS 12.0 and above.

## Installation

The SDK can be installed using CocoaPods, Carthage, Swift Package Manager, or manually.

### CocoaPods

1. Add the path to the SDK spec repo to your Podfile, along with the default specs repo:

```ruby
source 'https://github.com/atomic-app/action-cards-ios-sdk-specs.git'
source 'https://github.com/CocoaPods/Specs.git'
```

2. Add the SDK as a dependency. As of version 0.19.0, you have two options available:

- `AtomicSDK`: the Atomic SDK distributed as an `xcframework`, with support for Apple Silicon (requires Cocoapods 1.9 or above);
- `AtomicSDK-framework`: the Atomic SDK distributed as a fat framework, with slices for arm64 and x86_64.

```ruby
pod 'AtomicSDK'
# or
pod 'AtomicSDK-framework'
```

3. Run `pod update`.

### Carthage

1. Add `github "atomic-app/action-cards-ios-sdk-releases"` to your `Cartfile`.
2. Run `carthage update`.
3. [Follow the instructions](https://github.com/Carthage/Carthage#if-youre-building-for-ios-tvos-or-watchos) provided by Carthage to add the SDK to your app.

?> Note: As Carthage does not currently support `xcframework`, this will install the fat framework version, which does not include the arm64 simulator slice.

### Swift Package Manager

_(Requires Atomic SDK 0.19.0+)_

1. Open your Xcode project, and choose File > Swift Packages > Add Package Dependency.
2. When prompted to enter a package repository URL, enter `https://github.com/atomic-app/action-cards-ios-sdk-releases`.
3. Select the `AtomicSDK` dependency, and choose the version you'd like to use.

### Manual Installation

1. You can download releases of the SDK from the [Releases page](https://github.com/atomic-app/action-cards-ios-sdk-releases/releases) on Github.
2. Once you've downloaded the version you need, navigate to your project in Xcode and select the "General" settings tab. 
3. Drag either `AtomicSDK.xcframework` or `AtomicSDK.framework` from the directory where you unzipped the release, to the `Embedded Binaries` section. 
4. When prompted, ensure that "Copy items if needed" is selected, and then click "Finish".
5. **If you chose AtomicSDK.framework above**, you will also need to run the `strip-frameworks.sh` script (downloadable from this repository) as part of a `Run Script` phase in your target, to get around an App Store submission bug, caused by iOS simulator architectures being present in the fat framework.

?> Note: `AtomicSDK.xcframework` includes support for Apple Silicon, but requires Xcode 11 or higher, while `AtomicSDK.framework` is a fat framework.

## Setup

Before you can display a stream container or single card, you will need to configure your API base URL, environment ID and API key.

### API base URL

You must specify your API base URL when configuring the Atomic SDK. This URL is found in the Atomic Workbench:

1. In the Workbench, click on the cog icon in the bottom left and select 'Settings';
2. On the screen that appears, click the 'SDK' tab. Your API base URL is displayed in the 'API Host' section.

You can specify your API base URL in two ways:

1. By adding the following to your app's `Info.plist` file, replacing `API_BASE_URL` with your URL:

```
<key>AACRequestBaseURL</key>
<string>API_BASE_URL</string>
```

2. By declaring your API base URL in code, replacing `API_BASE_URL` with your URL:

**Swift**

```swift
if let url = URL(string: "API_BASE_URL") {
    AACSession.setApiBaseUrl(url)
}
```

**Objective-C**

```objectivec
NSURL *url = [NSURL URLWithString:@"API_BASE_URL"];
[AACSession setApiBaseUrl:url];
```

### Environment ID and API key

Within your host app, you will need to call the `+initialiseWithEnvironmentId:apiKey:` method to configure the SDK. Your environment ID and API key can be found in the Atomic Workbench.

If you do not call this method, and attempt to use any functionality in the SDK, an exception will be raised.

**Swift**

```swift
AACSession.initialise(withEnvironmentId: "<environmentId>", apiKey: "<apiKey>")
```

**Objective-C**

```objectivec
[AACSession initialiseWithEnvironmentId:@"<environmentId>" apiKey:@"<apiKey>"];
```

## Display a stream container

To display an Atomic stream container in your app, create an instance of `AACStreamContainerViewController`. To create an instance, you must supply:

1. A stream container ID, which uniquely identifies the stream container in the app;
2. An object conforming to the `AACSessionDelegate` protocol, which is used to pass an authentication token to the SDK, and (if applicable) resolve runtime variables;
3. A configuration object, which provides initial styling and presentation information to the SDK for this stream container.

### Stream container ID

First, you’ll need to locate your stream container ID. Navigate to the Workbench, select "Settings" > "SDK" > “Containers” and find the ID next to the stream container you are integrating.

### Session delegate

The session delegate supplies a JSON Web Token (JWT) to the SDK when requested, via the method `cardSessionDidRequestAuthenticationTokenWithHandler:` (Objective-C) or `cardSessionDidRequestAuthenticationToken(handler:)` (Swift). This method is called before each API request in the SDK.

You are responsible for generating, caching and handling expiry of the JWT. Once you have a valid token, call the `handler` block with the token. If you do not have a valid token, pass `nil` to the handler; this will invoke error handling within the SDK.

More information on the JWT structure is available in the [Authentication](/install/authentication) section.

### Configuration object

The configuration object allows you to configure a stream container or single card view via the following properties:

**Style and presentation**

- `presentationStyle`: indicates how the stream container is being displayed: 
    - With no button in its top left; 
    - With an action button that triggers a custom action you handle;
    - With a contextual button, which displays `Close` for modal presentations, or `Back` when inside a navigation controller.
- `launchBackgroundColor`: The background colour to use for the launch screen, seen on first load.
- `launchIconColor`: The colour of the icon displayed on the launch screen, seen on first load.
- `launchButtonColor`: The colour of the buttons that allow the user to retry the first load, if the request fails.
- `launchTextColor`: The text colour to use for the view displayed when the SDK is first presented.
- `interfaceStyle`: The interface style (light, dark or automatic) to apply to the stream container.
- `enabledUiElements`: A bitmask of UI elements that should be enabled in the stream container. Defaults to showing toast messages and the card list header in a stream container, and has no effect in single card view. Possible values are:
    - `AACUIElementNone`: No UI elements should be displayed. Do not use in conjunction with any other values.
    - `AACUIElementCardListToast`: Toast messages should appear at the bottom of the card list. Toast messages appear when cards are submitted, dismissed or snoozed, or when an error occurs in any of these actions.
    - `AACUIElementCardListFooterMessage`: A footer message should be displayed below the last card in the card list, if at least one is present. The message is customised using the `AACCustomStringCardListFooterMessage` custom string.
    - `AACUIElementCardListHeader`: The header should display at the top of the card list, allowing the user to pull down from the top of the screen to refresh the card list.

**Functionality**

- `cardListRefreshInterval`: How frequently the card list should be automatically refreshed. Defaults to 15 seconds, and must be at least 1 second. If set to 0, the card list will not automatically refresh after initial load.

!> Setting the card refresh interval to a value less than 15 seconds may negatively impact device battery life and is not recommended.

- `actionDelegate`: An optional delegate that handles actions triggered inside the stream container, such as the tap of the custom action button in the top left of the stream container, or submit and link buttons with custom actions.
- `runtimeVariableResolutionTimeout`: The maximum amount of time, in seconds, allocated to the resolution of runtime variables in your session delegate's `cardSessionDidRequestRuntimeVariables:completionHandler:` method. If you do not call the provided `completionHandler` passed to this method before the timeout is reached, the default values for all runtime variables will be used. If you do not implement this delegate method, this property is not used. Defaults to 5 seconds.
- `cardVotingOptions`: A bitmask representing the voting options that a user can choose from in a card's overflow menu. Voting options allow a user to flag a card as useful or not useful.

**Custom strings**

The configuration object also allows you to specify custom strings for features in the SDK, using the `setValue:forCustomString:` method:

- `AACCustomStringCardListTitle`: The title for the card list in this stream container - defaults to "Cards".
- `AACCustomStringCardSnoozeTitle`: The title for the feature allowing a user to snooze a card - defaults to "Remind me".
- `AACCustomStringAwaitingFirstCard`: The message displayed over the card list, when the user has never received a card before - defaults to "Cards will appear here when there’s something to action."
- `AACCustomStringAllCardsCompleted`: The message displayed when the user has received at least one card before, and there are no cards to show - defaults to "All caught up".
- `AACCustomStringVotingUseful`: The title to display for the action a user taps when they flag a card as useful - defaults to "This is useful".
- `AACCustomStringVotingNotUseful`: The title to display for the action a user taps when they flag a card as not useful - defaults to "This isn't useful".
- `AACCustomStringVotingFeedbackTitle`: The title to display at the top of the screen allowing a user to provide feedback on why they didn't find a card useful - defaults to "Send feedback".
- `AACCustomStringCardListFooterMessage`: The message to display below the last card in the card list, provided there is at least one present. Does not apply in single card view, and requires `enabledUiElements` to contain `AACUIElementCardListFooterMessage`. Defaults to an empty string.

### Single card view configuration

As of release 0.17.0, there is now a subclass of `AACConfiguration` - `AACSingleCardConfiguration` - which can be used to enable features that only apply to single card view.

**Swift**

```swift
let config = AACSingleCardConfiguration()
config.automaticallyLoadNextCard = true
```

**Objective-C**

```objectivec
AACSingleCardConfiguration *config = [[AACSingleCardConfiguration alloc] init];
config.automaticallyLoadNextCard = YES;
```

Available features are:

- `automaticallyLoadNextCard`: When enabled, will automatically display the next card in the single card view if there is one, using a locally cached card list. Defaults to `NO`.

### Create the stream container

You can now create a stream container by supplying the stream container ID, session delegate and configuration object on instantiation:

**Swift**

```swift
let config = AACConfiguration()
config.presentationStyle = .withContextualButton
config.launchBackgroundColor = .white
config.launchIconColor = .blue
config.launchButtonColor = .blue
config.launchTextColor = .white

let streamContainer = AACStreamContainerViewController(identifier: "1234", sessionDelegate: self, configuration: config)
present(streamContainer, animated: true)
```

**Objective-C**

```objectivec
AACConfiguration *config = [[AACConfiguration alloc] init];
config.presentationStyle = AACConfigurationPresentationStyleWithContextualButton;
config.launchBackgroundColor = [UIColor whiteColor];
config.launchIconColor = [UIColor blueColor];
config.launchButtonColor = [UIColor blueColor];
config.launchTextColor = [UIColor whiteColor];

AACStreamContainerViewController *streamContainer = [[AACStreamContainerViewController alloc] initWithIdentifier:@"1234" sessionDelegate:self configuration:config];
[self presentViewController:streamContainer animated:YES completion:nil];
```

## Displaying a single card

The Atomic iOS SDK also supports rendering a single card in your host app.

Create an instance of `AACSingleCardView`, which is a `UIView` that is configured in the same way as a stream container. On instantation, you supply the following parameters:

1. The ID of the stream container to render in the single card view. The single card view renders only the first card that appears in that stream container;
2. An object conforming to the `AACSessionDelegate` protocol, which is used to pass an authentication token to the SDK, and (if applicable) resolve runtime variables;
3. A configuration object, which provides initial styling and presentation information to the SDK for the single card view.

The configuration options, supplied using the configuration object above, are the same as those for a stream container. The only configuration option that does not apply is `presentationStyle`, as the single card view does not display a header, and therefore does not show a button in its top left.

**Swift**

```swift
let config = AACConfiguration()
config.launchBackgroundColor = .white
config.launchIconColor = .blue
config.launchButtonColor = .blue
config.launchTextColor = .white

let cardView = AACSingleCardView(frame: view.bounds, containerIdentifier: "1234", sessionDelegate: self, configuration: config)
view.addSubview(cardView)
```

**Objective-C**

```objectivec
AACConfiguration *config = [[AACConfiguration alloc] init];
config.launchBackgroundColor = [UIColor whiteColor];
config.launchIconColor = [UIColor blueColor];
config.launchButtonColor = [UIColor blueColor];
config.launchTextColor = [UIColor whiteColor];

AACSingleCardView *singleCardView = [[AACSingleCardView alloc] initWithFrame:self.view.frame containerIdentifier:@"1234" sessionDelegate:self configuration:config];
[self.view addSubview:singleCardView];
```

Within a single card view, toast messages - such as those seen when submitting, dismissing or snoozing a card in a stream container - do not appear. Pull to refresh functionality is also disabled.

You can set a delegate (conforming to `AACSingleCardViewDelegate`) on the single card view to be notified when the view changes height, either because a card is submitted, dismissed or snoozed, or because a new card arrived into the single card view (if polling is enabled). This allows you to animate changes to the `intrinsicContentSize` of the single card view.

**Swift**

```swift
func singleCardView(_ cardView: AACSingleCardView, willChange newSize: CGSize) {
    // Perform animation here.
}
```

**Objective-C**

```objectivec
- (void)singleCardView:(AACSingleCardView *)cardView willChangeSize:(CGSize)newSize {
    // Perform animation here.
}
```

## Filtering cards

_(Requires Atomic SDK 0.23.0+)_

Stream containers and single card views can have an optional filter applied, which affects the cards displayed. 

One filter is currently supported - `AACCardListFilter.filter(byCardInstanceId:)`. This filter requests that the stream container or single card view show only a card matching the specified card instance ID, if it exists. An instance of this filter can be created using the corresponding static method on the `AACCardListFilter` class.

The card instance ID can be found in the [push notification payload](/install/ios?id=_3-optional-perform-a-custom-action-when-tapping-on-a-push-notification), allowing you to apply the filter in response to a push notification being tapped.

**Swift**

```swift
let filter = AACCardListFilter.filter(byCardInstanceId: "ABCD-1234")
streamContainer.apply(filter)
```

**Objective-C**

```objectivec
AACCardFilter *filter = [AACCardListFilter filterByCardInstanceId:@"ABCD-1234"];
[streamContainer applyFilter:filter];
```

## Push notifications

To use push notifications in the SDK, you'll need to set up your notification preferences and add your iOS push certificate in the Workbench, then [request push notification permission](https://developer.apple.com/documentation/usernotifications/registering_your_app_with_apns) in your app.

Once this is done, you can configure push notifications via the SDK. The steps below can occur in either order in your app.

### 1. Register the user against specific stream containers for push notifications

You need to signal to the Atomic Platform which stream containers are eligible to receive push notifications in your app for the current device.

**Swift**

```swift
AACSession.registerStreamContainers(forPushNotifications: ["1"], sessionDelegate: self)
```

**Objective-C**

```objectivec
[AACSession registerStreamContainersForPushNotifications:@[ @"1" ] sessionDelegate:self];
```

You will need to do this each time the logged in user changes.

To deregister the device for Atomic notifications for your app, such as when a user completely logs out of your app, call `deregisterDeviceForNotifications:` on `AACSession`. If the de-registration fails, the error object will be populated, and the underlying error in the error's `userInfo` dictionary will provide additional context.

**Swift**

```swift
AACSession.deregisterDeviceForNotifications { (error) in
    // Perform an action once de-registration completes.
}
```

**Objective-C**

```objectivec
[AACSession deregisterDeviceForNotificationsWithCompletionHandler:^(NSError *error) {
    // Perform an action once de-registration completes.
}];
```

### 2. Send the push token to the Atomic Platform

Send the device's push token to the Atomic platform when it changes, by calling: 

**Swift**

```swift
AACSession.registerDevice(forNotifications:with:)
```

**Objective-C**

```objectivec
+[AACSession registerDeviceForNotifications:withSessionDelegate:]
```

in your app delegate's `application:didRegisterForRemoteNotificationsWithDeviceToken:` method.

You can also call this SDK method any time you want to update the push token stored for the user in the Atomic Platform; pass the method the `NSData` instance representing the push token. The token is automatically converted to a hex string by the SDK.

You will also need to update this token every time the logged in user changes in your app, so the Atomic Platform knows who to send notifications to.

### 3. (Optional) Perform a custom action when tapping on a push notification

When a user taps on a push notification delivered to your app, you can ask the SDK whether the push notification payload originated from Atomic. If so, you will be provided with a structured object that you can inspect, to perform custom actions based on the payload. The custom data for the notification, that was sent with the original event to Atomic, is in the `detail` property.

**Objective-C**

```objectivec
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler {
    if([response.actionIdentifier isEqualToString:UNNotificationDefaultActionIdentifier]) {
        AACPushNotification *notification = [AACSession notificationFromPushPayload:response.notification.request.content.userInfo];
        
        if(notification != nil) {
            // The payload originated from Atomic - use the properties on the object to determine the action to take.
        }
    }

    completionHandler();
}
```

**Swift**

```swift
func userNotificationCenter(_ center: UNUserNotificationCenter, didReceive response: UNNotificationResponse, withCompletionHandler completionHandler: @escaping () -> Void) {
    if response.actionIdentifier == UNNotificationDefaultActionIdentifier, let notification = AACSession.notification(fromPushPayload: response.notification.request.content.userInfo) {
            // The payload originated from Atomic - use the properties on the object to determine the action to take.
    }

    completionHandler()
}
```

### 4. (Optional) Track when push notifications are received

To track when push notifications are delivered to your user's device, you can use a [Notification Service Extension](https://developer.apple.com/documentation/usernotifications/unnotificationserviceextension).

While the Atomic SDK does not supply this extension, it does supply a method you can call within your own extension to track delivery.

From within your notification service extension's `didReceiveNotificationRequest:withContentHandler:` method, call the `+ [AACSession trackPushNotificationReceived:withSessionDelegate:completionHandler:]` method to track the delivery of a push notification. You must supply the push notification payload provided to your extension (stored in `request.content.userInfo`), as well as a session delegate, and a completion handler.

**Swift**

```swift
override func didReceive(_ request: UNNotificationRequest, withContentHandler contentHandler: @escaping (UNNotificationContent) -> Void) {

    // You must also ensure that your API base URL is set for your extension's Info.plist `AACRequestBaseURL` key.
    AACSession.initialise(withEnvironmentId: "<environmentId>", apiKey: "<apiKey>")
        
    AACSession.trackPushNotificationReceived(request.content.userInfo, with: self) { (error) in
        contentHandler(request.content)
    }
}
```

**Objective-C**

```objectivec
- (void)didReceiveNotificationRequest:(UNNotificationRequest *)request withContentHandler:(void (^)(UNNotificationContent *))contentHandler {
    
    // You must also ensure that your API base URL is set for your extension's Info.plist `AACRequestBaseURL` key.
    [AACSession initialiseWithEnvironmentId:@"<environmentId>" apiKey:@"<apiKey>"];
    
    [AACSession trackPushNotificationReceived:request.content.userInfo withSessionDelegate:self completionHandler:^(NSError * _Nullable error) {
        contentHandler(request.content);
    }];
}
```

This delivery event appears in your card's analytics as a `notification-received` event, with a timestamp indicating when the event was generated, as well as the card instance ID and stream container ID for the card.

## Supporting custom actions on submit and link buttons

In the Atomic Workbench, you can create a submit or link button with a custom action payload. 

- When such a link button is tapped, the `streamContainerDidTapLinkButton:withAction:` method is called on your action delegate. 
- When such a submit button is tapped, and after the card is successfully submitted, the `streamContainerDidTapSubmitButton:withAction:` method is called on your action delegate.

The second parameter to each of these methods is an action object, containing the payload that was defined in the Workbench for that button. You can use this payload to determine the action to take, within your app, when the submit or link button is tapped.

The action object also contains the card instance ID and stream container ID where the custom action was triggered.

**Objective-C**

```objectivec
// 1. Assign the action delegate
AACConfiguration *config = [[AACConfiguration alloc] init];
config.actionDelegate = self;

// 2. Implement the callbacks
- (void)streamContainerDidTapLinkButton:(AACStreamContainerViewController*)streamContainer withAction:(AACCardCustomAction*)action {
    if([action.actionPayload[@"screen"] isEqualToString:@"home-screen"]) {
        [self navigateToHomeScreen];
    }
}

- (void)streamContainerDidTapSubmitButton:(AACStreamContainerViewController*)streamContainer withAction:(AACCardCustomAction*)action {
    if([action.actionPayload[@"outcome"] isEqualToString:@"success"]) {
        [self navigateToSuccessScreen];
    }
}
```

**Swift**

```swift
// 1. Assign the action delegate
let config = AACConfiguration()
config.actionDelegate = self

// 2. Implement the callbacks
func streamContainerDidTapLinkButton(_ streamContainer: AACStreamContainerViewController, with action: AACCardCustomAction) {
    if let screenName = action.actionPayload["screen"] as? String, screenName == "home-screen" {
        // Perform an action
    }
}

func streamContainerDidTapSubmitButton(_ streamContainer: AACStreamContainerViewController, with action: AACCardCustomAction) {
    if let outcome = action.actionPayload["outcome"] as? String, outcome == "success" {
        // Perform an action
    }
}
```

## Retrieving card count

!> As of iOS SDK version 0.24.0, it is recommended that you use _user metrics_ to retrieve the card count instead. See the next section for more information.

The SDK supports observing the card count for a particular stream container, or receiving a single card count, even when that stream container does not exist in memory.

**Swift**

```swift
// Observe the card count
AACSession.observeCardCountForStreamContainer(withIdentifier: "1", interval: 15, sessionDelegate: self) { (count) in
    print("There are \(count) cards in the container.")
}

// Retrieve a one-off card count
AACSession.requestCardCountForStreamContainer(withIdentifier: "1", sessionDelegate: self) { (count) in
    print("There are \(count) cards in the container.")
}
```

**Objective-C**

```objectivec
// Observe the card count
[AACSession observeCardCountForStreamContainerWithIdentifier:@"1" interval:15 sessionDelegate:self handler:^(NSNumber *cardCount) {
    NSLog(@"There are %@ cards in the container", cardCount);
}];

// Retrieve a one-off card count
[AACSession requestCardCountForStreamContainerWithIdentifier:@"1" sessionDelegate:self handler:^(NSNumber *cardCount) {
    NSLog(@"There are %@ cards in the container", cardCount);
}];
```

If you choose to observe the card count, it is updated periodically at the interval you specify. When the card count changes, the `handler` block is called with the new card count, or `nil` if the card count could not be fetched.

When you want to stop observing the card count, you can remove the observer using the token returned from the observation call above:

**Swift**

```swift
AACSession.stopObservingCardCount(token)
```

**Objective-C**

```objectivec
[AACSession stopObservingCardCount:token];
```

When a stream container is present on screen, or when the card count is requested, a notification is posted (`AACSessionCardCountDidChange`) every time the visible card count changes, such as when a card is dismissed or completed. You can observe this notification to get the latest card count:

**Swift**
```swift
NotificationCenter.default.addObserver(forName: NSNotification.Name(rawValue: AACSessionCardCountDidChange), object: nil, queue: nil) { (notification) in
    if let userInfo = notification.userInfo,
        let visibleCards = userInfo[AACSessionCardCountUserInfoKey],
        let streamContainerId = notification.object {
        print("*** There are \(visibleCards) visible cards in stream container \(streamContainerId).")
    }
}
```

**Objective-C**
```objectivec    
[[NSNotificationCenter defaultCenter] addObserverForName:AACSessionCardCountDidChange
                                                        object:nil
                                                        queue:nil
                                                    usingBlock:^(NSNotification *note) {
        NSNumber *visibleCards = note.userInfo[AACSessionCardCountUserInfoKey];
        NSLog(@"*** There are %@ visible cards in stream container %@.", visibleCards, note.object);
    }];
```

The count of visible cards is available via the `AACSessionCardCountUserInfoKey` key in the `userInfo` dictionary, and the notification's `object` represents the stream container ID. You can listen for the card count of only a particular stream container by specifying that stream container ID in the `object` parameter when adding an observer.

If you want to retrieve the total number of cards in the container (rather than the number visible), use the `AACSessionTotalCardCountUserInfoKey` key in the `userInfo` dictionary. 

When not in single card view, `AACSessionCardCountUserInfoKey` and `AACSessionTotalCardCountUserInfoKey` report the same value.

## Retrieving the count of active and unseen cards

_(Requires Atomic SDK 0.24.0+)_

The Atomic iOS SDK exposes an object known as _user metrics_. These metrics include:
- The number of cards available to the user across all stream containers;
- The number of cards that haven't been seen across all stream containers;
- The number of cards available to the user in a specific stream container (equivalent to the card count functionality in the previous section);
- The number of cards not yet seen by the user in a specific stream container.

These metrics allow you to display badges in your UI that indicate how many cards are available to the user but not yet viewed, or the total number of cards in a given stream container.

**Swift**

```swift
AACSession.userMetrics(with: sessionDelegate) { metrics, error in
    if let userMetrics = metrics {
        print("Total cards across all containers: \(userMetrics.totalCards())")
        print("Total cards across a specific container: \(userMetrics.totalCardsForStreamContainer(withId: "containerId"))")
        
        print("Unseen cards across all containers: \(userMetrics.unseenCards())")
        print("Unseen cards across a specific container: \(userMetrics.unseenCardsForStreamContainer(withId: "containerId"))")
    }
}
```

**Objective-C**

```objectivec
[AACSession userMetricsWithSessionDelegate:sessionDelegate completionHandler:^(AACUserMetrics *response, NSError *error) {
    if(response != nil) {
        NSLog(@"Total cards: %i", [response totalCards]);
        NSLog(@"Total cards in stream container: %i", [response totalCardsForStreamContainerWithId:@"containerId"]);
        
        NSLog(@"Unseen cards: %i", [response unseenCards]);
        NSLog(@"Unseen cards in stream container: %i", [response unseenCardsForStreamContainerWithId:@"containerId"]);
    }
}];
```

## Dark mode

Stream containers in the Atomic iOS SDK support dark mode. You configure an (optional) dark theme for your stream container in the Atomic Workbench.

The interface style determines which theme is rendered:
- `AACConfigurationInterfaceStyleAutomatic`: If the user's device is currently set to light mode, the stream container will use the light (default) theme. If the user's device is currently set to dark mode, the stream container will use the dark theme (or fallback to the light theme if this has not been configured). On iOS versions less than 13, this setting is equivalent to `AACConfigurationInterfaceStyleLight`.
- `AACConfigurationInterfaceStyleLight`: The stream container will always render in light mode, regardless of the device setting.
- `AACConfigurationInterfaceStyleDark`: The stream container will always render in dark mode, regardless of the device setting.

To change the interface style, set the corresponding value for the `interfaceStyle` property on the `AACConfiguration` object when creating the stream container.

## Runtime variables

Runtime variables are resolved in the SDK at runtime, rather than from an event payload when the card is assembled. Runtime variables are defined in the Atomic Workbench.

The SDK will ask the host app to resolve runtime variables when a list of cards is loaded (and at least one card has a runtime variable), or when new cards become available due to polling (and at least one card has a runtime variable).

Runtime variables are resolved by your app via the `-cardSessionDidRequestRuntimeVariables:completionHandler:` method on `AACSessionDelegate`. If this method is not implemented on `AACSessionDelegate`, runtime variables will fall back to their default values, as defined in the Atomic Workbench.

This method, when called by the SDK, provides you with:

- An array of objects representing the cards in the list. Each card object contains:
    - The event name that triggered the card’s creation;
    - The lifecycle identifier associated with the card;
    - A method that you call to resolve each variable on that card (`-resolveRuntimeVariableWithName:value:`).
- A block callback (`completionHandler`), that must be called by the host app, with the resolved cards, once all variables are resolved.

If a variable is not resolved, that variable will use its default value, as defined in the Atomic Workbench.

If you do not call the `completionHandler` before the `runtimeVariableResolutionTimeout` elapses (defined on `AACConfiguration`), the default values for all runtime variables will be used. Calling the completion handler more than once has no effect.

**Swift**

```swift
func cardSessionDidRequestRuntimeVariables(_ cardsToResolve: [AACCardInstance], completionHandler: @escaping AACSessionRuntimeVariablesHandler) {
    for card in cardsToResolve {
        // Resolve variables on all cards.
        // You can also inspect `lifecycleId` and `eventName` to determine what type of card this is.
        card.resolveRuntimeVariable(withName: "numberOfItems", value: "12")
    }
    
    completionHandler(cardsToResolve)
}
```

**Objective-C**

```objectivec
- (void)cardSessionDidRequestRuntimeVariables:(NSArray<AACCardInstance*>*)cardsToResolve completionHandler:(AACSessionRuntimeVariablesHandler)completionHandler {
    for(AACCardInstance* instance in cardsToResolve) {
        // Resolve variables on all cards.
        // You can also inspect `lifecycleId` and `eventName` to determine what type of card this is.
        [instance resolveRuntimeVariableWithName:@"numberOfItems" value:@"12"];
    }
    
    completionHandler(cardsToResolve);
}
```

!> Runtime variables can currently only be resolved to string values.

### Updating runtime variables manually

You can manually update runtime variables at any time by calling the `updateVariables` method on `AACStreamContainerViewController` or `AACSingleCardView`:

**Swift**

```swift
streamVc.updateVariables()
```

**Objective-C**

```objectivec
[streamVc updateVariables];
```

### Analytics

!> In iOS SDK versions prior to 0.23.0, the default behaviour was to send analytics for resolved runtime variables. As of release 0.23.0, this behaviour has changed to default to **not** sending these analytics. Therefore, when upgrading to release 0.23.0, you must explicitly enable this feature to use it.

If you use runtime variables on a card, you can optionally choose to send the resolved values of any runtime variables back to the Atomic Platform as an analytics event. This per-card analytics event - `runtime-vars-updated` - contains the values of runtime variables rendered in the card and seen by the end user. Therefore, you should not enable this feature if your runtime variables contain sensitive data that you do not wish to store on the Atomic Platform.

To enable this feature, set the `runtimeVariableAnalytics` flag on your configuration's `features` object:

**Swift**

```swift
let config = AACConfiguration()
config.features.runtimeVariableAnalytics = true
```

**Objective-C**

```objectivec
AACConfiguration *config = [[AACConfiguration alloc] init];
config.features.runtimeVariableAnalytics = YES;
```

## Responding to card events

The SDK allows you to perform custom actions in response to events occurring on a card, such as when a user:

- submits a card;
- dismisses a card;
- snoozes a card;
- indicates a card is useful (when card voting is enabled);
- indicates a card is not useful (when card voting is enabled).

To be notified when these happen, assign a card event delegate to your stream container:

**Objective-C**

```objectivec
// 1. Assign the event delegate
AACConfiguration *config = [[AACConfiguration alloc] init];
config.cardEventDelegate = self;

// 2. Implement the delegate
- (void)streamContainer:(AACStreamContainerViewController *)streamContainerVc didTriggerCardEvent:(AACCardEvent *)event {
    // Perform a custom action in response to the card event.
}
```

**Swift**

```swift
// 1. Assign the event delegate
let config = AACConfiguration()
config.cardEventDelegate = self

// 2. Implement the delegate
func streamContainer(_ streamContainerVc: AACStreamContainerViewController, didTriggerCardEvent event: AACCardEvent) {
    // Perform a custom action in response to the card event.
}
```


## Card voting

You can optionally allow users to flag cards as either useful or not useful, which are reported as part of a card's analytics. These voting options are displayed in a card's overflow menu, however, they are not enabled by default.

To enable them, specify a bitmask on `AACConfiguration`'s `cardVotingOptions` property, which indicates the voting options to display.

### Refreshing a stream container manually

You can choose to manually refresh a stream container or single card view, such as when a push notification arrives while your app is open. Refreshing will result in the stream container or single card view checking for new cards immediately, and showing any that are available.

**Swift**

```swift
streamContainer.refresh()
```

**Objective-C**

```objectivec
[streamContainer refresh];
```

## Sending events from the SDK

You can send events directly to the Atomic Platform for the logged in user, via the `sendEvent:withSessionDelegate:completionHandler:` method on `AACSession`. 

This allows you to trigger an event, which will generate a card, in response to some user action. The event you wish to trigger must have the 'Enable client trigger' option enabled in the Atomic Workbench.

The card will be created for the user defined by the authentication token returned in the session delegate. As such, you cannot specify target user IDs using this method.

**Swift**

```swift
let payload = AACEventPayload(name: "myEventName")
payload.lifecycleId = "lifecycleId" // Optional
payload.detail = [
    "variable1": "value1" // Optional
]
// You can also optionally set the `metadata` and `notificationDetail` dictionaries.

AACSession.sendEvent(payload, with: self) { (response, error) in
    guard error == nil else {
        // Handle error here.
        return
    }
    
    // `response` contains the details of the processed event.
}
```

**Objective-C**

```objectivec
AACEventPayload *payload = [[AACEventPayload alloc] initWithName:@"myEventName"];
payload.lifecycleId = @"lifecycleId"; // Optional
payload.detail = @{
    @"variable1": @"value1" // Optional
};
// You can also optionally set the `metadata` and `notificationDetail` dictionaries.

[AACSession sendEvent:payload
    withSessionDelegate:self
    completionHandler:^(AACEventResponse *response, NSError *error) {
    if(error) {
        // Handle error here.
        return;
    }
    
    // `response` contains the details of the processed event.
}];
```

## Network request security

The Atomic iOS SDK provides functionality to further secure the SDK implementation in your own app.

### Allow or deny network requests

You can choose to implement a request delegate, which determines whether requests originating from the Atomic SDK are allowed to proceed. This enables you to permit network requests only to domains or subdomains that you approve.

The request delegate is called before every network request in the SDK, and during SSL certificate validation.

To enable this functionality, create a request delegate conforming to the `AACRequestDelegate` protocol, implement the `dispositionForAtomicRequest:` method and call `setRequestDelegate` on `AACSession` to assign it to the SDK. The request delegate is used for every network request from the SDK.

Within the `dispositionForAtomicRequest:` method, you can inspect the request URL and return one of the following dispositions:

- `allow`: The request is allowed to proceed.
- `deny`: The request is not allowed to proceed and will be cancelled.
- `allowWithCertificatePins`: The request can proceed if a hash of the subject public key info (SPKI) from the certificate matches one of the pin objects provided (see below for more information).

All of these dispositions are available as static methods on `AACRequestDisposition`.

If you do not implement this request delegate, all requests are permitted.

### Allow requests with certificate pinning

When you return `allowWithCertificatePins` in the `AACRequestDelegate` above, you will be required to supply a set of `AACCertificatePin` objects. Each object contains a SHA-256 hash of the subject public key info (SPKI) from the domain's certificate, which is base64 encoded. You can generate this using the following command, replacing `[url]` with the domain you want to generate the hash for:

```
openssl s_client -servername [url] -connect [url]:443 | openssl x509 -pubkey -noout | openssl pkey -pubin -outform der | openssl dgst -sha256 -binary | openssl enc -base64
```

If the hashed, base64-encoded SPKI from the request's certificate matches any of the provided pin objects, the request is allowed to proceed. If it does not match any of the provided pins, the request is denied.

If the `allowWithCertificatePins` disposition is used with a non-HTTPS URL, the request will be denied.

**Swift**

```swift
func disposition(forAtomicRequest requestUrl: URL) -> AACRequestDisposition {
    guard let host = requestUrl.host else {
        // Deny requests without a host.
        return .deny()
    }
    
    switch(host) {
    case "atomic.io":
        // Allow requests to atomic.io with certificate pinning.
        let pins = Set([
            AACCertificatePin(sha256Hash: "AAAAAA=")
        ])
        return .allow(with: pins)
    case "placeholder.com":
        // Always allow requests to placeholder.com.
        return .allow()
    default:
        // Deny all other requests.
        return .deny()
    }
}

AACSession.setRequestDelegate(self)
```

**Objective-C**

```objectivec
- (AACRequestDisposition *)dispositionForAtomicRequest:(NSURL *)requestUrl {
    if([[requestUrl host] isEqualToString:@"atomic.io"]) {
        // Allow requests to atomic.io with certificate pinning.
        NSSet *pins = [NSSet setWithArray:@[
            [AACCertificatePin pinWithSha256Hash:@"AAAAAAAA="]
        ]];
        return [AACRequestDisposition allowWithCertificatePins:pins];
    }
    
    if([[requestUrl host] isEqualToString:@"placeholder.com"]) {
        // Always allow requests to placeholder.com.
        return [AACRequestDisposition allow];
    }
    
    // Deny all other requests.
    return [AACRequestDisposition deny];
}

[AACSession setRequestDelegate:self];
```

## Dynamic Type

The Atomic iOS SDK supports Dynamic Type, on an opt-in basis and per-typography style. 

To opt-in to Dynamic Type for a typography style:

1. Open the [Atomic Workbench](https://workbench.atomic.io/);
2. Navigate to Settings > Settings > Themes. Select the theme you want to edit.
3. When editing a typography style in the theme, turn `Dynamic scaling` on.
4. Optionally specify a minimum and maximum font size to use when scaling is applied.

The SDK automatically scales the typography style from the base font size that you specify, adding or subtracting a pixel value from this base font size, to create a size tailored to each Dynamic Type level. The minimum font size is 1px - this is enforced by the SDK.

The pixel value that is added or subtracted for each Dynamic Type level is determined inside the SDK and is not customisable.

## Utility methods

### Debug logging

Debug logging allows you to view more verbose logs regarding events that happen in the SDK. It is turned off by default, and should not be enabled in release builds. To enable debug logging:

**Swift**
```swift
AACSession.setLoggingEnabled(true)
```

**Objective-C**
```objectivec
[AACSession setLoggingEnabled:YES];
```

### Purge cached data

The SDK provides a method for purging the local cache of a user's card data. The intent of this method is to clear user data when a previous user logs out, so that the cache is clear when a new user logs in to your app. 

To clear this in-memory cache, call:

**Swift**
```swift
AACSession.logout()
```

**Objective-C**
```objectivec
[AACSession logout];
```

