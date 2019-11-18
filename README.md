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
To display an Atomic stream container in your app, create an instance of `AACStreamContainerViewController`. To create an instance, you must supply:

1. A stream container ID, which uniquely identifies the stream container in the app;
2. An object conforming to the `AACSessionDelegate` protocol, which is used to pass an authentication token to the SDK;
3. A configuration object, which provides initial styling and presentation information to the SDK for this stream container.

### Stream container ID
First, you’ll need to locate your stream container ID. Navigate to the Workbench, select “Containers” and find the ID next to the stream container you are integrating.

### Session delegate
The session delegate supplies a JSON Web Token (JWT) to the SDK when requested, via the method `cardSessionDidRequestAuthenticationTokenWithHandler:` (Objective-C) or `cardSessionDidRequestAuthenticationToken(handler:)` (Swift). This method is called before each API request in the SDK.

You are responsible for generating, caching and handling expiry of the JWT. Once you have a valid token, call the `handler` block with the token. More information on the JWT structure is available in the [Authentication](/install/authentication) section.

### Configuration object

The configuration object specifies the initial styling and display mode via the following properties:

- `presentationStyle`: indicates how the stream container is being displayed: 
    - With no button in its top left; 
    - With an action button that triggers a custom action you handle;
    - With a contextual button, which displays `Close` for modal presentations, or `Back` when inside a navigation controller.
- `cardListTitle`: The title to display at the top of the card list. If not specified, defaults to `Cards`.
- `actionDelegate`: An optional delegate that handles actions triggered inside of the stream container, such as the tap of the custom action button in the top left of the stream container.
- `launchBackgroundColor`: The background colour to use for the launch screen, seen on first load.
- `launchIconColor`: The colour of the icon displayed on the launch screen, seen on first load.
- `launchButtonColor`: The colour of the buttons that allow the user to retry the first load, if the request fails.
- `launchTextColor`: The text colour to use for the view displayed when the SDK is first presented.
- `cardListRefreshInterval`: How frequently the card list should be refreshed. Defaults to 15 seconds, and must be at least 1 second. 

!> Setting the card refresh interval to a value less than 15 seconds may negatively impact device battery life and is not recommended.

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

let streamContainer = AACStreamContainerViewController(containerId: "1234", sessionDelegate: self, configuration: config)
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

AACStreamContainerViewController *streamContainer = [[AACStreamContainerViewController alloc] initWithContainerId:@"1234" sessionDelegate:self configuration:config];
[self presentViewController:streamContainer animated:YES completion:nil];
```

## API and additional methods

### Push notifications
To use push notifications in the SDK, you'll need to set up your notification preferences and add your iOS push certificate in the Workbench, then [request push notification permission](https://developer.apple.com/documentation/usernotifications/registering_your_app_with_apns) in your app.

Once this is done, you can configure push notifications via the SDK. The steps below can occur in either order in your app.

#### 1. Register the user against specific stream containers for push notifications

You need to signal to the Atomic Platform which stream containers are eligible to receive push notifications in your app for the current device.

**Swift**

```swift
AACSession.registerStreamContainers(forNotifications:with:)
```

**Objective-C**

```objectivec
+[AACSession registerStreamContainersForNotifications:withSessionDelegate:]
```

You will need to do this each time the logged in user changes.

To unregister the device for notifications (such as when a user completely logs out of your app), you can pass an empty array as the first argument to the method above. This will disable notifications for the device, until you make a subsequent call to the method above with an array of valid stream container IDs.

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

### Retrieving card count
The SDK supports observing the card count for a particular stream container, even when that stream container does not exist in memory.

**Swift**

```swift
AACSession.observeCardCountForStreamContainer(withId:interval:sessionDelegate:handler:)
```

**Objective-C**

```objectivec
+[AACSession observeCardCountForStreamContainerWithId:interval:sessionDelegate:handler:]
```

The card count is updated periodically at the interval you specify. When the card count changes, the `handler` block is called with the new card count, or `nil` if the card count could not be fetched.

When you want to stop observing the card count, you can remove the observer using the token returned from the observation call above:

**Swift**

```swift
AACSession.stopObservingCardCount(_)
```

**Objective-C**

```objectivec
+[AACSession stopObservingCardCount:]
```

When a stream container is present on screen, a notification is posted (`AACSessionCardCountDidChange`) every time the card count changes, such as when a card is dismissed or completed. You can observe this notification to get the latest card count:

**Swift**
```swift
NotificationCenter.default.addObserver(forName: NSNotification.Name(rawValue: AACSessionCardCountDidChange), object: nil, queue: nil) { (notification) in
    if let userInfo = notification.userInfo,
        let totalCards = userInfo[AACSessionCardCountUserInfoKey],
        let streamContainerId = notification.object {
        print("*** There are \(totalCards) cards in stream container \(streamContainerId).")
    }
}
```

**Objective-C**
```objectivec    
[[NSNotificationCenter defaultCenter] addObserverForName:AACSessionCardCountDidChange
                                                        object:nil
                                                        queue:nil
                                                    usingBlock:^(NSNotification *note) {
        NSString *cardCount = note.userInfo[AACSessionCardCountUserInfoKey];
        NSLog(@"*** There are %@ cards in stream container %@.", cardCount, note.object);
    }];
```

The count of cards is available via the `AACSessionCardCountUserInfoKey` in the `userInfo` dictionary, and the notification’s `object` represents the stream container ID. You can listen for the card count of only a particular stream container by specifying that stream container ID in the `object` parameter when adding an observer.

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

## Advanced

### Custom API URL
If you need to change the base URL for all API requests in the SDK, add the following to your app's `Info.plist` file:

```
<key>AACRequestBaseURL</key>
<string>[your custom URL]</string>
```