//  This file is part of class-dump, a utility for examining the
//  Objective-C segment of Mach-O files.
//  Copyright (C) 1997-1998, 2000-2001, 2004  Steve Nygard

#import "NSString-Extensions.h"

#import <Foundation/Foundation.h>

@implementation NSString (CDExtensions)

+ (NSString *)stringWithFileSystemRepresentation:(const char *)str;
{
    // 2004-01-16: I'm don't understand why we need to pass in the length.
    return [[NSFileManager defaultManager] stringWithFileSystemRepresentation:str length:strlen(str)];
}

+ (NSString *)spacesIndentedToLevel:(int)level;
{
    return [self spacesIndentedToLevel:level spacesPerLevel:4];
}

+ (NSString *)spacesIndentedToLevel:(int)level spacesPerLevel:(int)spacesPerLevel;
{
    NSString *spaces = @"                                        ";
    NSString *levelSpaces;
    NSMutableString *str;
    int l;

    assert(spacesPerLevel <= [spaces length]);
    levelSpaces = [spaces substringToIndex:spacesPerLevel];

    str = [NSMutableString string];
    for (l = 0; l < level; l++)
        [str appendString:levelSpaces];

    return str;
}

+ (NSString *)stringWithUnichar:(unichar)character;
{
    return [NSString stringWithCharacters:&character length:1];
}

- (BOOL)isFirstLetterUppercase;
{
    NSRange letterRange;

    letterRange = [self rangeOfCharacterFromSet:[NSCharacterSet letterCharacterSet]];
    if (letterRange.length == 0)
        return NO;

    return [[NSCharacterSet uppercaseLetterCharacterSet] characterIsMember:[self characterAtIndex:letterRange.location]];
}

+ (NSString *)stringWithASCIICString:(const char *)bytes;
{
    if (bytes == NULL)
        return nil;

    return [[[NSString alloc] initWithBytes:bytes length:strlen(bytes) encoding:NSASCIIStringEncoding] autorelease];
}

- (BOOL)startsWithLetter;
{
    if ([self length] == 0)
        return NO;

    return [[NSCharacterSet letterCharacterSet] characterIsMember:[self characterAtIndex:0]];
}

- (BOOL)isAllUpperCase;
{
    NSRange range;

    range = [self rangeOfCharacterFromSet:[[NSCharacterSet uppercaseLetterCharacterSet] invertedSet]];

    return range.location == NSNotFound;
}

- (BOOL)containsPrimaryStress;
{
    NSRange range;

    range = [self rangeOfString:@"'"];

    return range.location != NSNotFound;
}

// Returns the pronunciation with the first " converted to a ', or nil otherwise.
- (NSString *)convertedStress;
{
    NSRange range;
    NSMutableString *str;

    range = [self rangeOfString:@"\""];
    if (range.location == NSNotFound)
        return nil;

    str = [NSMutableString stringWithString:self];
    [str replaceCharactersInRange:range withString:@"'"];

    return [NSString stringWithString:str];
}

@end

@implementation NSMutableString (Extensions)

- (void)indentToLevel:(int)level;
{
    [self appendString:[NSString spacesIndentedToLevel:level spacesPerLevel:2]];
}

@end
