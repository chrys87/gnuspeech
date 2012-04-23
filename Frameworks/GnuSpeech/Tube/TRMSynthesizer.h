//  This file is part of Gnuspeech, an extensible, text-to-speech package, based on real-time, articulatory, speech-synthesis-by-rules. 
//  Copyright 1991-2012 David R. Hill, Leonard Manzara, Craig Schock

#import <Foundation/Foundation.h>
#import <Tube/TubeModel.h>

@class AVAudioPlayer;
@class MMSynthesisParameters;

@interface TRMSynthesizer : NSObject

- (id)init;
- (void)dealloc;

- (void)setupSynthesisParameters:(MMSynthesisParameters *)synthesisParameters;
- (void)removeAllParameters;
- (void)addParameters:(float *)values;

- (BOOL)shouldSaveToSoundFile;
- (void)setShouldSaveToSoundFile:(BOOL)newFlag;

- (NSString *)filename;
- (void)setFilename:(NSString *)newFilename;

- (int)fileType;
- (void)setFileType:(int)newFileType;

- (void)synthesize;
- (NSData *)generateWAVDataWithSampleRateConverter:(TRMSampleRateConverter *)sampleRateConverter;

- (AVAudioPlayer *)audioPlayer;
- (void)setAudioPlayer:(AVAudioPlayer *)audioPlayer;

- (void)startPlaying:(TRMTubeModel *)tube;

- (void)stopPlaying;

@end
