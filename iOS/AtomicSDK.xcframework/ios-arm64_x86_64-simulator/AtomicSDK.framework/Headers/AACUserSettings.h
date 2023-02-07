//
// AACUserSettings.h
// ActionCardsSDK
// Copyright © 2022 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A time frame in which notifications can be pushed to the user. The frame includes two timestamps: the start and end of the time frame.
 These times are in the format of 24 hour, the end time must be later than the start time.
 */
@interface AACUserNotificationTimeframe: NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 Creates a time frame in which the notification can be pushed to the user. The frame includes two timestamps: the start and end of the time frame.
 These times are in the format of 24 hour, the end time must be later than the start time.
 
 @param startHour The hour part of the starting time. Must be no less than 0 and no more than 23.
 @param startMinute The minute part of the starting time. Must be no less than 0 and no more than 59.
 @param endHour The hour part of the end time. Must be no less than 0 and no more than 23.
 @param endMinute The minute part of the end time. Must be no less than 0 and no more than 59.
 */
- (instancetype __nonnull)initWithStartHour:(NSInteger)startHour startMinute:(NSInteger)startMinute endHour:(NSInteger)endHour endMinute:(NSInteger)endMinute;

@property (nonatomic, readonly) NSInteger startHour;
@property (nonatomic, readonly) NSInteger startMinute;
@property (nonatomic, readonly) NSInteger endHour;
@property (nonatomic, readonly) NSInteger endMinute;

@end

/**
 The day that a time frame applies to.
 */
typedef NS_ENUM(NSUInteger, AACUserNotificationTimeframeWeekdays) {
    /**
     Represents the default notification timeframe to be applied if a value has not been specified for a particular weekday.
     */
    AACUserNotificationTimeframeWeekdaysDefault,
    AACUserNotificationTimeframeWeekdaysMonday,
    AACUserNotificationTimeframeWeekdaysTuesday,
    AACUserNotificationTimeframeWeekdaysWednesday,
    AACUserNotificationTimeframeWeekdaysThursday,
    AACUserNotificationTimeframeWeekdaysFriday,
    AACUserNotificationTimeframeWeekdaysSaturday,
    AACUserNotificationTimeframeWeekdaysSunday
};

/**
 Represents a user setting object, exclusively for the user identified by the authentication token provided by the
 session delegate that is registered when initiating the SDK. A user setting object is equivalent to those settings
 in the `Customers` page on the Workbench.
 
 All properties in `AACUserSettings` are optional. However, you must update user with at least one property.
 */
@interface AACUserSettings: NSObject

/**
 An external ID of the user.
 */
@property (nonatomic, nullable) NSString *externalID;

/**
 The name of the user.
 */
@property (nonatomic, nullable) NSString* name;

/*
 The email address of the user.
 */
@property (nonatomic, nullable) NSString* email;

/**
 The phone number of the user.
 */
@property (nonatomic, nullable) NSString* phone;

/**
 The city of the user.
 */
@property (nonatomic, nullable) NSString* city;

/**
 The country of the user.
 */
@property (nonatomic, nullable) NSString* country;

/**
 The region of the user.
 */
@property (nonatomic, nullable) NSString* region;

/**
 Whether push notifications are enabled for this user.
 */
@property (nonatomic) BOOL notificationsEnabled;

/**
 Set up a notification time frame for the user. `timeframes` must be non-nil.
 
 @param timeframes The array of notification time frames.
 @param weekday The day of the week when the time frames apply to.
 */
-(void)setNotificationTime:(NSArray<AACUserNotificationTimeframe*> *__nonnull)timeframes weekday:(AACUserNotificationTimeframeWeekdays)weekday;

/**
 Assigns the given text to a custom field defined by the given name, which is defined as type `text` on Atomic Workbench.
 `value` must be non-nil.
 
 @param text The value of the custom field.
 @param fieldName The name of the custom field. Note: in the Atomic Workbench a custom field has a `name` and a `label` property. This parameter matches
 the `name` property in the Workbench.
 */
- (void)setText:(NSString *__nonnull)text forCustomField:(NSString *__nonnull)fieldName;

/**
 Assigns the given date to a custom field defined by the given name, which is defined as type `date` on Atomic Workbench.
 `value` must be non-nil. Note: custom fields defined as `date` must be updated by this method.
 
 @param date The date to be updated on the custom field.
 @param fieldName The name of the custom field. Note: in Atomic Workbench a custom field has a `name` and a `label` property. This parameter matches
 the `name` property in the Workbench.
 */
- (void)setDate:(NSDate *__nonnull)date forCustomField:(NSString *__nonnull)fieldName;

/**
 A utility method to check whether data is valid.
 
 @return `Nil` if the data is valid. Otherwise the reason why it's invalid.
 */
- (NSString *__nullable)validate;

@end
