//
// AACDeserializable.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Defines an initializer to create an instance of this class
 from the specified NSDictionary.
 */
@protocol AACDeserializable <NSObject>

/**
 Creates a new instance of this class from the specified
 NSDictionary instance.
 */
- (instancetype)initWithDictionary:(NSDictionary*)dictionary;

@end
