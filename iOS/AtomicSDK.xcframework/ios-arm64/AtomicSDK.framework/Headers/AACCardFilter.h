//
// AACCardFilter.h
// AtomicSDK
// Copyright © 2021 Atomic.io Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Represents a value of one of the card's properties supported by the SDK, which can be used to filter cards.
 Cards are filtered by applying one or more `AACCardFilterValue`s to an operator, such as `equal to` or `less than`.
 
 Properties can be card's metadata such as its priority or created date, or user defined variables.

 Combine `AACCardFilterValue` with `AACCardListFilter` to create card filters. For more details on
 card filtering, head to the Atomic documentation site.
 
 Note: `list` type user defined variables in Atomic Workbench are not supported for filtering yet.
 */
@interface AACCardFilterValue: NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 Generates a priority value that can be used to filter cards.
 
 Card priority works on all operators.
 
 @param priority The priority value of card.
 */
+ (AACCardFilterValue* __nonnull)byPriority:(NSInteger)priority;

/**
 Generates a card template ID that can be used to filter cards.
 
 Card template ID works only on `equal`, `not equal`, `in` and `not in` operators.
 
 @param templateId The unique ID of a card.
 */
+ (AACCardFilterValue* __nonnull)byCardTemplateID:(NSString* __nonnull)templateId;

/**
 Generates a card template name that can be used to filter cards.
 For filtering untitled cards, pass an empty string to it.
  
 Card template name works only on `equal`, `not equal`, `in` and `not in` operators.
 
 @param templateName The name of a card.
 */
+ (AACCardFilterValue* __nonnull)byCardTemplateName:(NSString* __nonnull)templateName;

/**
 Generates a date when a card instance is created, which can be used to filter cards.
 
 Created date works on all operators.
 
 @param createdDate The date when a card instance is created, in UTC timezone.
 */
+ (AACCardFilterValue* __nonnull)byCreatedDate:(NSDate* __nonnull)createdDate;

/**
 Generates a string value of a given variable that can be used to filter cards.
 
 String variables work only on `equal`, `not equal`, `in` and `not in` operators.
 
 @param name The name of the variable, it must be the `string` type in Atomic Workbench.
 @param string The value of that string variable.
 */
+ (AACCardFilterValue* __nonnull)byVariableName:(NSString* __nonnull)name string:(NSString* __nonnull)string;

/**
 Generates a date value of a given variable that can be used to filter cards.
 
 Date variables work on all operators.
 
 @param name The name of the variable, it must be the `date` type in Atomic Workbench.
 @param date The value of that date variable.
 */
+ (AACCardFilterValue* __nonnull)byVariableName:(NSString* __nonnull)name date:(NSDate* __nonnull)date;

/**
 Generates a number of a given variable that can be used to filter cards.
 
 Number variables work on all operators.
 
 @param name The name of the variable, it must be the `number` type in Atomic Workbench.
 @param number The value of that number variable.
 */
+ (AACCardFilterValue* __nonnull)byVariableName:(NSString* __nonnull)name number:(NSNumber* __nonnull)number;

/**
 Generates a boolean value of a given variable that can be used to filter cards.
 
 Boolean variables work only on `equal` and `not equal` operator.
 
 @param name The name of the variable, it must be the `boolean` type in Atomic Workbench.
 @param boolean The value of that boolean variable.
 */
+ (AACCardFilterValue* __nonnull)byVariableName:(NSString* __nonnull)name boolean:(BOOL)boolean;

@end

/**
 Represents an instance of a filter that can be applied to a list of cards.
 */
@interface AACCardFilter: NSObject

@end

/**
 Provides static methods to generate card list filters supported by the SDK.
 */
@interface AACCardListFilter: NSObject

- (instancetype __nonnull)init NS_UNAVAILABLE;

/**
 Generates a card list filter that is restricted to the card with the provided instance ID.
 This can be used in stream containers or single card view to show only a particular card.
 
 @param cardInstanceId The instance ID of the card to show.
 */
+ (AACCardFilter* __nonnull)filterByCardInstanceId:(NSString* __nonnull)cardInstanceId NS_SWIFT_NAME(filter(byCardInstanceId:));

/**
 Generates a card list filter that is restricted to the card with the same filter value.
 
 @param value The value used to compare with cards. For example, the priority of the card.
 */
+ (AACCardFilter* __nonnull)filterByCardsEqualTo:(AACCardFilterValue* __nonnull)value NS_SWIFT_NAME(filter(byCardsEqualTo:));

/**
 Generates a card list filter that is restricted to the card different with the filter value.
 
 @param value The value used to compare with cards. For example, the priority of the card.
 */
+ (AACCardFilter* __nonnull)filterByCardsNotEqualTo:(AACCardFilterValue* __nonnull)value NS_SWIFT_NAME(filter(byCardsNotEqualTo:));

/**
 Generates a card list filter that is restricted to the card with the value greater than the filter.
 
 `Greater than` operator works only on number or date values.
 
 @param value The value used to compare with cards. For example, the priority of the card.
 */
+ (AACCardFilter* __nonnull)filterByCardsGreaterThan:(AACCardFilterValue* __nonnull)value NS_SWIFT_NAME(filter(byCardsGreaterThan:));

/**
 Generates a card list filter that is restricted to the card with the value greater than or equal to the filter.
 
 `Greater than or equal to` operator works only on number or date values.
 
 @param value The value used to compare with cards. For example, the priority of the card.
 */
+ (AACCardFilter* __nonnull)filterByCardsGreaterThanOrEqualTo:(AACCardFilterValue* __nonnull)value NS_SWIFT_NAME(filter(byCardsGreaterThanOrEqualTo:));

/**
 Generates a card list filter that is restricted to the card with the value less than the filter.
 
 `Less than` operator works only on number or date values.
 
 @param value The value used to compare with cards. For example, the priority of the card.
 */
+ (AACCardFilter* __nonnull)filterByCardsLessThan:(AACCardFilterValue* __nonnull)value NS_SWIFT_NAME(filter(byCardsLessThan:));

/**
 Generates a card list filter that is restricted to the card with the value less than or equal to the filter.
 
 `Less than or equal to` operator works only on number or date values.
 
 @param value The value used to compare with cards. For example, the priority of the card.
 */
+ (AACCardFilter* __nonnull)filterByCardsLessThanOrEqualTo:(AACCardFilterValue* __nonnull)value NS_SWIFT_NAME(filter(byCardsLessThanOrEqualTo:));

/**
 Generates a card list filter that is restricted to the card with the value equal to one of the filter values.
 
 `In` operator works only on number, date or string values.
 
 Note: values must be of the same type. For example, they must all be priority values. Otherwise an exception will be raised.
 
 @param values The values for the card to match within. For example, the priority values of cards.
 */
+ (AACCardFilter* __nonnull)filterByCardsIn:(NSArray<AACCardFilterValue*>* __nonnull)values NS_SWIFT_NAME(filter(byCardsIn:));

/**
 Generates a card list filter that is restricted to the card with the value equal to NONE of the filter values.
 
 `Not in` operator works only on number, date or string values.
 
 Note: values must be of the same type. For example, they must all be priority values. Otherwise an exception will be raised.
 
 @param values The values for the card to match within. For example, the priority values of cards.
 */
+ (AACCardFilter* __nonnull)filterByCardsNotIn:(NSArray<AACCardFilterValue*>* __nonnull)values NS_SWIFT_NAME(filter(byCardsNotIn:));

/**
 Generates a card list filter that is restricted to the card with the values within a closed interval, defined by the start and end value.
 
 `Between` operator works only on number or date values.
 
 Note: Values defining the interval must be of the same type. For example, they must be both priority values. Otherwise an exception will be raised.
 
 @param start The start of the interval, included when checking.
 @param end The end of the interval, included when checking.
 */
+ (AACCardFilter* __nonnull)filterByCardsBetweenStartValue:(AACCardFilterValue* __nonnull)start endValue:(AACCardFilterValue* __nonnull)end
NS_SWIFT_NAME(filter(byCardsBetweenStartValue:endValue:));

@end
