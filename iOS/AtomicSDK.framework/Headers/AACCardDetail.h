//
// AACCardDetail.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACDeserializable.h>

NS_ASSUME_NONNULL_BEGIN
/**
 An object encapsulating the details of a particular card, including
 important identifiers, creation date and its status.
 */
@interface AACCardDetail: NSObject<AACDeserializable>

@property (nonatomic, strong, readonly) NSDate *createdDate;
@property (nonatomic, copy, readonly) NSString *cardId;
@property (nonatomic, copy, readonly) NSString* status;

@property (nonatomic, copy, readonly) NSString *lifecycleId;
@property (nonatomic, copy, readonly) NSString *eventName;

@end
NS_ASSUME_NONNULL_END
