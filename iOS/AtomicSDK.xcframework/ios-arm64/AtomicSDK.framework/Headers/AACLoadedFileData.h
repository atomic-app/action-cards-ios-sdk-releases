//
// AACLoadedFileData.h
// ActionCardsSDK
// Copyright © 2024 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// A structure for handling loaded file.
@interface AACLoadedFileData : NSObject

/// The identifier of the upload bucket. This value is assigned after creation, from the file upload node.
@property (nonatomic, copy) NSString *bucketId;

/// Whether the file has been successfully uploaded. Set by the upload manager.
@property (nonatomic) BOOL hasUploaded;

/// The name used to display on the user interface.
@property (nonatomic, readonly) NSString *displayedName;

/// The name used for uploading, suffixed with a unique UUID string.
@property (nonatomic, readonly) NSString *platformFilename;

/// The data converted from the underlying file object.
@property (nonatomic, readonly) NSData *data;

/// The file size obtained via NSFileManager, or the length of the converted data.
@property (nonatomic, readonly) NSNumber *fileSize;

/// Abstract data types of the file, which determines the extension of the platform filename.
@property (nonatomic, readonly) UTType *utType API_AVAILABLE(ios(14.0));

/// The content string used when uploading images via HTTP requests, determined by `utType`, or is 'image/jpeg'.
@property (nonatomic, readonly) NSString *contentTypeString;

/// Get the legacy filename extension, only to satisfy iOS 14-.
- (NSString *__nullable)getFallbackFilenameExtension;

+ (instancetype)dataWithData:(NSData *)data platformFilename:(NSString *)platformFilename utType:(UTType *)utType API_AVAILABLE(ios(16.0));

@end

NS_ASSUME_NONNULL_END
