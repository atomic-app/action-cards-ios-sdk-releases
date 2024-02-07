//
// AACValidator.h
// AtomicSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACValidation.h>
#import <AtomicSDK/AACValidationResult.h>

/**
 An object that takes a collection of validations (added via `addValidation:`),
 running those validations over a supplied value, and returning the result.
 */
@interface AACValidator: NSObject

/**
 Validations stored in this validator.
 */
@property (nonatomic, strong, readonly, nonnull) NSMutableArray<AACValidation*> *validations;

/**
 Adds a validation to this validator, which will be included when determining whether
 the supplied value is valid or invalid.
 
 @param validation The validation to include.
 */
- (void)addValidation:(AACValidation* __nonnull)validation;

/**
 Determines whether, after running the validations within this validator, the supplied
 value is valid.
 
 @param value The value to validate.
 */
- (AACValidationResult* __nonnull)resultForValue:(id __nullable)value;

@end
