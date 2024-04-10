//
// AACValidationResult.h
// AtomicSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/// The different validation results possible in the SDK.
typedef NS_ENUM(NSUInteger, AACValidationResultKind) {
    /// The supplied input is valid in the given context.
    AACValidationResultKindValid,
    /// The supplied input is invalid in the given context.
    AACValidationResultKindInvalid
};

/**
 Represents the result of running a validation, or multiple validations
 across an input.
 */
@interface AACValidationResult: NSObject

/**
 Convenience method for creating an immutable validation result of the given kind,
 with an optional message corresponding to that state.
 
 @param kind The kind of validation result represented by this object.
 @param message The optional message to display to the end user.
 */
+ (AACValidationResult* __nonnull)resultOfKind:(AACValidationResultKind)kind
                                       message:(NSString* __nullable)message;

/**
 The kind of validation result (currently either valid or invalid).
 */
@property (nonatomic, readonly) AACValidationResultKind kind;

/**
 The optional message to display to the end user.
 */
@property (nonatomic, copy, readonly, nullable) NSString *message;

@end
