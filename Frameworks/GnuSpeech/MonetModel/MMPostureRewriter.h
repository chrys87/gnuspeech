//  This file is part of Gnuspeech, an extensible, text-to-speech package, based on real-time, articulatory, speech-synthesis-by-rules. 
//  Copyright 1991-2012 David R. Hill, Leonard Manzara, Craig Schock

#import <Foundation/Foundation.h>

@class EventList, MModel, MMPosture;

@interface MMPostureRewriter : NSObject

- (id)initWithModel:(MModel *)aModel;
- (void)dealloc;

- (void)_setupCategoryNames;
- (void)_setup;

- (MModel *)model;
- (void)setModel:(MModel *)newModel;

- (MMPosture *)lastPosture;
- (void)setLastPosture:(MMPosture *)newPosture;

- (void)resetState;
- (void)rewriteEventList:(EventList *)eventList withNextPosture:(MMPosture *)nextPosture wordMarker:(BOOL)followsWordMarker;

@end
