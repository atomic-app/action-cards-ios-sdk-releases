# Atomic iOS SDK

The Atomic SDK supports iOS 9.0 and above.

## Installation

The Atomic SDK can be installed using any of the following methods:

### Carthage

1. Add `github "atomic-app/action-cards-ios-sdk-releases"` to your `Cartfile`.
2. Run `carthage update`.
3. [Follow the instructions](https://github.com/Carthage/Carthage#if-youre-building-for-ios-tvos-or-watchos) provided by Carthage to add the SDK to your app.

### Cocoapods

1. Add the path to the Atomic SDK spec repo to your Podfile, along with the default specs repo:
```
source 'https://github.com/atomic-app/action-cards-ios-sdk-specs.git'
source 'https://github.com/CocoaPods/Specs.git'
```
2. Add the Atomic SDK as a dependency:
```
pod 'AtomicSDK'
```
3. Run `pod update`.

### Manual Installation

1. You can download releases of the Atomic SDK from the [Releases page](https://github.com/atomic-app/action-cards-ios-sdk-releases/releases) on Github.
2. Once you've downloaded the version you need, navigate to your project in Xcode and select the "General" settings tab. Drag `AtomicSDK.framework` from the directory where you unzipped the release, to the `Embedded Binaries` section. 
3. When prompted, ensure that "Copy items if needed" is selected, and then click "Finish".
4. You will also need to run the `strip-frameworks.sh` script (downloadable from this repository) as part of a `Run Script` phase in your target, to get around an App Store submission bug, caused by iOS simulator architectures being present in the framework.

## Setup

To display an Atomic stream container in your app, create an instance of `AACStreamContainerViewController`. To create an instance, you must supply:
1. A stream container ID, a string which uniquely identifies the stream container in the app;
2. An object conforming to the `AACSessionDelegate` protocol, which is used to pass an authentication token to the SDK;
3. A configuration object, which provides initial styling and presentation information to the SDK for this stream container.

Swift:
```
let config = AACConfiguration()

let streamContainer = AACStreamContainerViewController(containerId: "1357", sessionDelegate: myDelegate, configuration: config)
present(streamContainer, animated: true)
```

Objective-C:
```
AACConfiguration *config = [[AACConfiguration alloc] init];

AACStreamContainerViewController *streamContainer = [[AACStreamContainerViewController alloc] initWithContainerId:@"1357" sessionDelegate:myDelegate configuration:config];
[self presentViewController:streamContainer animated:YES completion:nil];
```

The session delegate must conform to the protocol `AACSessionDelegate`, and implement the method `cardSessionDidRequestAuthenticationTokenWithHandler:` (`cardSessionDidRequestAuthenticationToken(handler:)` in Swift). This method supplies an authentication token to the SDK, and supports asynchronous execution. When you have a token ready to supply to the SDK, simply call `handler` with that token (which is a JWT).

The `AACConfiguration` object allows you to specify configuration options for the SDK. For more information, see the [Configuration](#Configuration) section below.

## Configuration

### Customisation
When instantiating an `AACStreamContainerViewController`, you are required to pass an `AACConfiguration` object. This object supplies initial styling and presentation information to the particular stream container.

See `AACConfiguration.h` for information on what the various configuration options represent.

### Debug logging
Debug logging allows you to view more verbose logs regarding events that happen in the SDK. It is turned off by default, and should not be enabled in release builds. You can enable it like so:

Swift:
```
AACSession.setLoggingEnabled(true)
```

Objective-C:
```
[AACSession setLoggingEnabled:YES];
```

### Purge cached data
The SDK provides a method for purging the local cache of a user's card data. The intent of this method is to clear user data when a previous user logs out, so that the cache is clear when a new user logs in to your app. 

To clear this in-memory cache, simply call:

Swift:
```
AACSession.logout()
```

Objective-C:
```
[AACSession logout];
```

## Advanced

### Custom API URL
If you need to change the base URL for all API requests in the SDK, add the following to your app's `Info.plist` file:

```
<key>AACRequestBaseURL</key>
<string>[your custom URL]</string>
```
