//
// AACUploadServiceError.h
// ActionCardsSDK
// Copyright © 2024 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACUploadRequest.h>

/// Error domain for errors relating to the AACUserSettingsService.
extern NSString* const AACUploadServiceErrorDomain;

/// Error codes for AACUserSettingsServiceErrorDomain.
NS_ERROR_ENUM(AACUploadServiceErrorDomain) {
    /// The upload request was invalid.
    AACUploadServiceErrorDomainInvalidRequest = 1,
    /// The upload process was interrupted.
    AACUploadServiceErrorDomainInterrupted = 2,
    /// The upload process was cancelled.
    AACUploadServiceErrorDomainCanceled = 3,
    /// The upload service couldn't get a valid token.
    AACUploadServiceErrorDomainInvalidToken = 4
};

/// Typed error for upload data.
@interface AACUploadServiceError: NSObject

/// The original upload request.
@property (nonatomic) AACUploadRequest *request;

/// The error from AACUploadServiceErrorDomain.
@property (nonatomic) NSError *error;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithUploadRequest:(AACUploadRequest *)request error:(NSError *)error;

@end
