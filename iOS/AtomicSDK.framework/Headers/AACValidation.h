//
// AACValidation.h
// AtomicSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AtomicSDK/AACValidationResult.h>

/**
 Represents a validation that processes a single input, determining
 whether that input is valid or invalid.
 
 Call `resultForValue:` to determine the validation result given this
 input.
 */
@interface AACValidation: NSObject

/**
 Creates a new validation object from the supplied dictionary.
 
 @param dict The dictionary to transform into a validation.
 */
- (instancetype __nonnull)initWithDictionary:(NSDictionary* __nonnull)dict;

/**
 Determines whether the given value is valid in the context of this validation.
 
 @param value The value to validate.
 */
- (AACValidationResult* __nonnull)resultForValue:(id __nullable)value;

@end
