# Action Cards iOS SDK

The Action Cards SDK supports iOS 9.0 and above.

## Installation

The Action Cards SDK can be installed using any of the following methods:

### Carthage

1. Add `github "atomic-app/action-cards-ios-sdk-releases"` to your `Cartfile`.
2. Run `carthage update`.
3. [Follow the instructions](https://github.com/Carthage/Carthage#if-youre-building-for-ios-tvos-or-watchos) provided by Carthage to add the SDK to your app.

### Cocoapods

1. Add the path to the Action Cards SDK spec repo to your Podfile, along with the default specs repo:
```
source 'https://github.com/atomic-app/action-cards-ios-sdk-specs.git'
source 'https://github.com/CocoaPods/Specs.git'
```
2. Add the Action Cards SDK as a dependency:
```
pod 'ActionCardsSDK'
```
3. Run `pod update`.

### Manual Installation

1. You can download releases of the Action Cards SDK from the [Releases page](https://github.com/atomic-app/action-cards-ios-sdk-releases/releases) on Github.
2. Once you've downloaded the version you need, navigate to your project in Xcode and select the "General" settings tab. Drag `ActionCardsSDK.framework` from the directory where you unzipped the release, to the `Embedded Binaries` section. 
3. When prompted, ensure that "Copy items if needed" is selected, and then click "Finish".
4. You will also need to run the `strip-frameworks.sh` script (downloadable from this repository) as part of a `Run Script` phase in your target, to get around an App Store submission bug, caused by iOS simulator architectures being present in the framework.

## Setup

To start the SDK, create a new instance of `AACHomeViewController` (along with the required `AACSessionDelegate`), and present it on screen:

Swift:
```
let homeViewController = AACHomeViewController(sessionDelegate: myDelegate)
present(homeViewController, animated: true)
```

Objective-C:
```
AACHomeViewController *homeViewController = [[AACHomeViewController alloc] initWithSessionDelegate:myDelegate];
[self presentViewController:homeViewController animated:YES completion:nil];
```

The session delegate must conform to the protocol `AACSessionDelegate`, and implement the method `cardSessionDidRequestAuthenticationTokenWithHandler:` (`cardSessionDidRequestAuthenticationToken(handler:)` in Swift). This method supplies an authentication token to the SDK, and supports asynchronous execution. When you have a token ready to supply to the SDK, simply call `handler` with that token (which is a JWT).

**Note:** The current iteration of the SDK only supports modal presentation, as it displays a 'Done' button that dismisses the screen on tap.

## Configuration

### Debug logging
Debug logging allows you to view more verbose logs regarding events that happen in the SDK. It is turned off by default, and should not be enabled in release builds. You can enable it like so:

Swift:
```
AACLogger.setLoggingEnabled(true)
```

Objective-C:
```
[AACLogger setLoggingEnabled:YES];
```

## Advanced

### Custom API URL
If you need to change the base URL for all API requests in the SDK, add the following to your app's `Info.plist` file:

```
<key>AACRequestBaseURL</key>
<string>[your custom URL]</string>
```
