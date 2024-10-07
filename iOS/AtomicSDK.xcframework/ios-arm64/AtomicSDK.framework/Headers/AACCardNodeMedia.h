//
// AACCardNodeMedia.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

extern CGFloat const AACCardNodeMediaHeightDynamic;

/**
 Media element kinds (or types) supported by the SDK.
 */
typedef NS_ENUM(NSUInteger, AACCardNodeMediaKind) {
    /// Represents a static image.
    AACCardNodeMediaKindImage,
    /// Represents a video.
    AACCardNodeMediaKindVideo
};

/**
 Possible formats that a media element can be rendered in.
 */
typedef NS_ENUM(NSUInteger, AACCardNodeMediaFormat) {
    /// A format not supported by this version of the SDK.
    AACCardNodeMediaFormatUnknown,
    /// The media should be rendered inline with padding around it.
    AACCardNodeMediaFormatInline,
    /// The media should be rendered as a full width banner.
    AACCardNodeMediaFormatBanner,
    /// The media should be rendered as a text caption.
    AACCardNodeMediaFormatText,
    /// The media should be rendered as a small thumbnail with metadata.
    AACCardNodeMediaFormatThumbnail
};

/**
 Possible actions that a media element can take.
 */
typedef NS_ENUM(NSUInteger, AACCardNodeMediaActionType) {
    /// The media would display an image or video.
    AACCardNodeMediaActionTypeMedia,
    /// The media would redirect to a URL.
    AACCardNodeMediaActionTypeURL,
    /// The media would redirect to a subview.
    AACCardNodeMediaActionTypeSubview,
    /// The media would redirect to a custom payload.
    AACCardNodeMediaActionTypePayload
};

/**
 Defines the possible heights for displaying a media element.
 */
typedef NS_ENUM(NSUInteger, AACCardNodeMediaHeight) {
    /// Tall height (200px). Spans full width, centered with automatic vertical cropping.
    AACCardNodeMediaHeightTall,
    /// Medium height (120px). Spans full width, centered with automatic vertical cropping.
    AACCardNodeMediaHeightMedium,
    /// Short height (50px). Spans full width, centered with automatic vertical cropping.
    AACCardNodeMediaHeightShort,
    /// Original size. Displays the source image at its original dimensions, spanning full width with no cropping.
    AACCardNodeMediaHeightOriginal
};

@interface AACCardNodeMedia: AACCardNode

/// The kind of media represented by this object.
@property (nonatomic, readonly) AACCardNodeMediaKind mediaKind;

/// The format to display the media element in.
@property (nonatomic) AACCardNodeMediaFormat format;

/// The label to display for the media if the `format` is `text` or `thumbnail`.
@property (nonatomic, copy, nullable) NSString* label;

/// A description of the media - e.g. `JPEG` for a JPEG image, or `01:41` for a video.
@property (nonatomic, copy, nullable) NSString* mediaDescription;

/// The URL to the thumbnail image for the media.
@property (nonatomic, strong, nullable) NSURL* thumbnailUrl;

/// The URL to the full version of the media.
@property (nonatomic, strong, nullable) NSURL* url;

/// The alternate text, provided in the Atomic Workbench, that describes the thumbnail image.
@property (nonatomic, copy, nullable) NSString *thumbnailAlternateText;

/// The alternate text, provided in the Atomic Workbench, that describes the source media.
@property (nonatomic, copy, nullable) NSString *alternateText;

/// The action URL to jump to when set in the Atomic Workbench.
@property (nonatomic, strong, nullable) NSURL* actionUrl;

/// The name of the layout to navigate to on tap. If this property is `nil`, the document at `url` will be presented instead.
@property (nonatomic, copy, nullable) NSString* actionLayoutName;

/**
 A payload of key-value pairs that are sent to the host app, to determine the custom action taken
 when tapping on this button. We use the same callback in the `AACStreamContainerActionDelegate` that's used by a link button.
 */
@property (nonatomic, copy, nullable) NSDictionary *actionPayload;

/**
 The action to be taken by this object.
 */
@property (nonatomic) AACCardNodeMediaActionType actionType;

/**
 The specified height type of this object provided in the Atomic Workbench.
 
 Defaults to `AACCardNodeMediaHeightTall`.
 */
@property (nonatomic) AACCardNodeMediaHeight displayedHeightType;

@end
