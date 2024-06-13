//
// AACCardNodeText.h
// ActionCardsSDK
// Copyright © 2019 Atomic.io Limited. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <AtomicSDK/AACCardNode.h>
#import <AtomicSDK/AACCardNodeCustomIcon.h>

/**
 A body of text, with an optional icon to the left.
 The `text` property supports basic Markdown formatting; namely bold,
 italic, links, and ordered lists and unordered lists.
 */
@interface AACCardNodeText: AACCardNode

/**
 The name of the optional FontAwesome icon to render next to the text.
 */
@property (nonatomic, copy, nullable) NSString* icon DEPRECATED_MSG_ATTRIBUTE("The icon property has been deprecated and will be removed in future releases. Please use customIcon instead.");

/**
 An optional icon to render next to the text.
 */
@property (nonatomic, nullable) AACCardNodeCustomIcon *customIcon;

/**
 The raw text to render, including all Markdown tokens.
 To get the formatted text in a performant way, use `attributedText` instead.
 */
@property (nonatomic, copy, nonnull) NSString* text;

@end
