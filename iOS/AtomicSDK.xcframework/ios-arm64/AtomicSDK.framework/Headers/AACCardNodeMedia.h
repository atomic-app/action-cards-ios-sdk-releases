//
// AACCardNodeMedia.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

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

@interface AACCardNodeMedia: AACCardNode

/// The kind of media represented by this object.
@property (nonatomic, readonly) AACCardNodeMediaKind mediaKind;

/// The format to display the media element in.
@property (nonatomic) AACCardNodeMediaFormat format;

/// The label to display for the media if the `format` is `text` or `thumbnail`.
@property (nonatomic, copy) NSString* label;

/// A description of the media - e.g. `JPEG` for a JPEG image, or `01:41` for a video.
@property (nonatomic, copy) NSString* mediaDescription;

/// The URL to the thumbnail image for the media.
@property (nonatomic, strong) NSURL* thumbnailUrl;

/// The URL to the full version of the media.
@property (nonatomic, strong) NSURL* url;

/// The alternate text, provided in the Atomic Workbench, that describes the thumbnail image.
@property (nonatomic, copy) NSString *thumbnailAlternateText;

/// The alternate text, provided in the Atomic Workbench, that describes the source media.
@property (nonatomic, copy) NSString *alternateText;

@end
