// swift-tools-version:5.3

import PackageDescription

let package = Package(
    name: "AtomicSDK",
    platforms: [
        .iOS(.v12)
    ],
    products: [
        .library(
            name: "AtomicSDK",
            targets: ["AtomicSDK"]),
    ],
    dependencies: [],
    targets: [
        .binaryTarget(name: "AtomicSDK", path: "iOS/AtomicSDK.xcframework")
    ]
)
