//
// AACCardNodeFileUpload.h
// AtomicSDK
// Copyright © 2024 Atomic.io Limited. All rights reserved.
//

#import <AtomicSDK/AACCardNode.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Types of files allowed for upload.
 */
typedef NS_OPTIONS(NSUInteger, AACCardNodeFileUploadType) {
    /// No file type allowed.
    AACCardNodeFileUploadTypeNone = 0,
    /// Allows the upload of static images.
    AACCardNodeFileUploadTypeStaticImage = 1 << 0,
};

/**
 A node that renders a file upload element.
 */
@interface AACCardNodeFileUpload: AACCardNodeSubmittable

/// Text displayed before a file is selected.
@property (nonatomic, copy, nullable) NSString* placeholder;

/// Indicates whether a thumbnail placeholder is shown before a file is uploaded.
@property (nonatomic) BOOL displayThumbnailPlaceholder;

/// Specifies the allowed file types for upload. Currently, only static images are supported. Future updates will include additional file types.
@property (nonatomic) AACCardNodeFileUploadType allowedTypes;

/// The ID of the bucket where the file will be uploaded.
@property (nonatomic, nonnull) NSString *bucketId;

@end

NS_ASSUME_NONNULL_END
