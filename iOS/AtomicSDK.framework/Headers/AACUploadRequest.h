//
// AACUploadRequest.h
// ActionCardsSDK
// Copyright © 2024 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACLoadedFileData.h>

NS_ASSUME_NONNULL_BEGIN

/// Represents an upload request in the SDK.
@interface AACUploadRequest: NSObject

/// The name of the upload component triggering this upload request.
@property (nonatomic, copy) NSString* inputName;

/// The identifier of the card instance holding the upload component.
@property (nonatomic, copy) NSString* cardInstanceId;

/// The identifier of the stream container containing the associated card.
@property (nonatomic, copy) NSString* streamContainerId;

/// The data loaded by the file upload component.
@property (nonatomic) AACLoadedFileData *loadedFileData;

- (instancetype)init NS_UNAVAILABLE;


/// Instantiates an AACUploadRequest object, associating it with the given parameters.
///  - Parameters:
///    - inputName: The name of the upload component  
///    - cardInstanceId: The identifier for the card instance.
///    - containerId: The identifier for the stream container.
///    - loadedFileData: The data loaded by the file upload component, either from the file system or from the camera.
- (instancetype)initWithInputName:(NSString *)inputName
                   cardInstanceId:(NSString *)cardInstanceId
                      containerId:(NSString *)containerId
                   loadedFileData:(AACLoadedFileData *)loadedFileData;

@end


NS_ASSUME_NONNULL_END
