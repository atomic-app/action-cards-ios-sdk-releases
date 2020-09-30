# iOS SDK

## Introduction

The Atomic iOS SDK is a dynamic framework for integrating an Atomic stream container into your iOS app, presenting cards from a stream to your end users.

The SDK is written in Objective-C and supports iOS 9.0 and above.

## Installation

The SDK can be installed using CocoaPods, Carthage, or manually.

### CocoaPods

1. Add the path to the SDK spec repo to your Podfile, along with the default specs repo:

```ruby
source 'https://github.com/atomic-app/action-cards-ios-sdk-specs.git'
source 'https://github.com/CocoaPods/Specs.git'
```

2. Add the SDK as a dependency:

```ruby
pod 'AtomicSDK'
```

3. Run `pod update`.

### Carthage

1. Add `github "atomic-app/action-cards-ios-sdk-releases"` to your `Cartfile`.
2. Run `carthage update`.
3. [Follow the instructions](https://github.com/Carthage/Carthage#if-youre-building-for-ios-tvos-or-watchos) provided by Carthage to add the SDK to your app.

### Manual Installation

1. You can download releases of the SDK from the [Releases page](https://github.com/atomic-app/action-cards-ios-sdk-releases/releases) on Github.
2. Once you've downloaded the version you need, navigate to your project in Xcode and select the "General" settings tab. Drag `AtomicSDK.framework` from the directory where you unzipped the release, to the `Embedded Binaries` section. 
3. When prompted, ensure that "Copy items if needed" is selected, and then click "Finish".
4. You will also need to run the `strip-frameworks.sh` script (downloadable from this repository) as part of a `Run Script` phase in your target, to get around an App Store submission bug, caused by iOS simulator architectures being present in the framework.

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
- `AACCustomStringCardListFooterMessage`: The message to display below the last card in the card list, provided there is at least one present. Does not apply in single card view, and requires `enabledUiElements` to contain `AACUIElementCardListFooterMessage`. Defaults to an empty string.

**Single card view features**

As of release 0.16.2, there is now a subclass of `AACConfiguration` - `AACSingleCardConfiguration` - which can be used to enable features that only apply to single card view.

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

Avaialable features are:

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
func singleCardView(_ singleCardView: AACSingleCardView, willChangeSize size: CGSize) {
    // Perform animation here. 
}
```

**Objective-C**

```objectivec
- (void)singleCardView:(AACSingleCardView *)cardView willChangeSize:(CGSize)newSize {
    // Perform animation here.
}
```

## API and additional methods

### Push notifications

To use push notifications in the SDK, you'll need to set up your notification preferences and add your iOS push certificate in the Workbench, then [request push notification permission](https://developer.apple.com/documentation/usernotifications/registering_your_app_with_apns) in your app.

Once this is done, you can configure push notifications via the SDK. The steps below can occur in either order in your app.

#### 1. Register the user against specific stream containers for push notifications

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

#### 2. Send the push token to the Atomic Platform

Send the device's push token to the Atomic platform when it changes, by calling: 

**Swift**

```swift
AACSession.registerDeviceForNotifications(_:with:)
```

**Objective-C**

```objectivec
+[AACSession registerDeviceForNotifications:withSessionDelegate:]
```

in your app delegate's `application:didRegisterForRemoteNotificationsWithDeviceToken:` method.

You can also call this SDK method any time you want to update the push token stored for the user in the Atomic Platform; pass the method the `NSData` instance representing the push token. The token is automatically converted to a hex string by the SDK.

You will also need to update this token every time the logged in user changes in your app, so the Atomic Platform knows who to send notifications to.

#### 3. (Optional) Perform a custom action when tapping on a push notification

When a user taps on a push notification delivered to your app, you can ask the SDK whether the push notification payload originated from Atomic. If so, you will be provided with a structured object that you can inspect, to perform custom actions based on the payload. The custom data for the notification, that was sent with the original event to Atomic, is in the `detail` property.

For a consistent experience, you should handle the scenarios where the push notification triggers your app to open when already running, and when not previously running.

**While app is running - targeting iOS 9+**

**Objective-C**

```objectivec
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {    
    AACPushNotification *notification = [AACSession notificationFromPushPayload:userInfo];
    
    if(notification != nil) {
        // The payload originated from Atomic - use the properties on the object to determine the action to take.
    }
}
```

**Swift**

```swift
func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable : Any]) {
    if let payload = userInfo as? NSDictionary {
        if let notification = AACSession.notificationFromPushPayload(payload) {
            // The payload originated from Atomic - use the properties on the object to determine the action to take.
        }
    }
}
```

**While app is running - targeting iOS 10+**

**Objective-C**

```objectivec
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler {
    if([response.actionIdentifier isEqualToString:UNNotificationDefaultActionIdentifier]) {
        AACPushNotification *notification = [AACSession notificationFromPushPayload:response.notification.request.content.userInfo];
        
        if(notification != nil) {
            // The payload originated from Atomic - use the properties on the object to determine the action to take.
        }
        
        completionHandler();
    }
}
```

**Swift**

```swift
func userNotificationCenter(_ center: UNUserNotificationCenter, didReceive response: UNNotificationResponse, withCompletionHandler completionHandler: @escaping () -> Void) {
    if response.actionIdentifier == UNNotificationDefaultActionIdentifier,
        let payload = response.notification.request.content.userInfo as? NSDictionary {
        if let notification = AACSession.notificationFromPushPayload(payload) {
            // The payload originated from Atomic - use the properties on the object to determine the action to take.
        }
    }
}
```

**When app is not running**

**Objective-C**

```objectivec
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    ...
    if(launchOptions[UIApplicationLaunchOptionsRemoteNotificationKey] != nil) {
        AACPushNotification *notification = [AACSession notificationFromPushPayload:launchOptions[UIApplicationLaunchOptionsRemoteNotificationKey]];
        
        if(notification != nil) {
            // The payload originated from Atomic - use the properties on the object to determine the action to take.
        }
    }
    
    return YES;
}
```

**Swift**

```swift
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey : Any]? = nil) -> Bool {
    if let payload = launchOptions?[.remoteNotification] as? NSDictionary {
        if let notification = AACSession.notificationFromPushPayload(payload) {
            // The payload originated from Atomic - use the properties on the object to determine the action to take.
        }
    }
}
```

#### 4. (Optional) Track when push notifications are received

To track when push notifications are delivered to your user's device, you can use a [Notification Service Extension](https://developer.apple.com/documentation/usernotifications/unnotificationserviceextension), supported in iOS 10 and above. If you are supporting iOS 9, you can choose to track delivery of notifications when a user taps on your notification instead. 

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

### Supporting custom actions on submit and link buttons

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
func streamContainerDidTapLinkButton(_ streamContainer: AACStreamContainer, withAction action: AACCardCustomAction) {
    if let screenName = action.actionPayload["screen"] as? String, screenName == "home-screen" {
        navigateToHomeScreen()
    }
}

func streamContainerDidTapSubmitButton(_ streamContainer: AACStreamContainer, withAction action: AACCardCustomAction) {
    if let outcome = action.actionPayload["outcome"] as? String, outcome == "success" {
        navigateToSuccessScreen()
    }
}
```

### Retrieving card count

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

### Dark mode

Stream containers in the Atomic iOS SDK support dark mode. You configure an (optional) dark theme for your stream container in the Atomic Workbench.

The interface style determines which theme is rendered:
- `AACConfigurationInterfaceStyleAutomatic`: If the user's device is currently set to light mode, the stream container will use the light (default) theme. If the user's device is currently set to dark mode, the stream container will use the dark theme (or fallback to the light theme if this has not been configured). On iOS versions less than 13, this setting is equivalent to `AACConfigurationInterfaceStyleLight`.
- `AACConfigurationInterfaceStyleLight`: The stream container will always render in light mode, regardless of the device setting.
- `AACConfigurationInterfaceStyleDark`: The stream container will always render in dark mode, regardless of the device setting.

To change the interface style, set the corresponding value for the `interfaceStyle` property on the `AACConfiguration` object when creating the stream container.

### Runtime variables

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
func cardSessionDidRequestRuntimeVariables(_ cardsToResolve: [AACCardInstance], completionHandler: ([AACCardInstance]) -> Void) {
    for card in cardsToResolve {
        // Resolve variables on all cards.
        // You can also inspect `lifecycleId` and `eventName` to determine what type of card this is.
        card.resolveVariableWithName("numberOfItems", value: "12")
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

#### Updating runtime variables manually

You can manually update runtime variables at any time by calling the `updateVariables` method on `AACStreamContainerViewController` or `AACSingleCardView`:

**Swift**

```swift
streamVc.updateVariables()
```

**Objective-C**

```objectivec
[streamVc updateVariables];
```

### Responding to card events

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


### Card voting

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
