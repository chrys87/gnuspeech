//
//  PhoneToSpeech.m
//  GnuTTSServer
//
//  Created by Dalmazio on 05/01/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "PhoneToSpeech.h"

// Location of the diphones XML file that allows speech to happen.
#define GNUSPEECH_SERVER_DIPHONES_XML_PATH	@"/Library/GnuSpeech/diphones.mxml"

// These defines were taken from Monet's MSynthesisController.m
#define MDK_ShouldUseSmoothIntonation @"ShouldUseSmoothIntonation"
#define MDK_ShouldUseMacroIntonation @"ShouldUseMacroIntonation"
#define MDK_ShouldUseMicroIntonation @"ShouldUseMicroIntonation"
#define MDK_ShouldUseDrift @"ShouldUseDrift"

@implementation PhoneToSpeech

- (id) init;
{
	[super init];
			
    eventList = [[EventList alloc] init];
    synthesizer = [[TRMSynthesizer alloc] init];
	
	// Now get the model from the diphones XML file.
    MDocument * document = [[MDocument alloc] init];
    BOOL result = [document loadFromXMLFile:GNUSPEECH_SERVER_DIPHONES_XML_PATH];
    if (result == YES)
        [self setModel:[document model]];
    [document release];	
	
	return self;
}

- (void) dealloc;
{
    [model release];
    [eventList release];
    [synthesizer release];	
	
	[super dealloc];
}

- (void) speakPhoneString:(NSString *)phoneString;
{
	[self synthesize:phoneString];
}

- (MModel *) model;
{
    return model;
}

- (void) setModel:(MModel *)newModel;
{
    if (newModel == model)
        return;
	
    [model release];
    model = [newModel retain];	
    [eventList setModel:model];
}

- (void) synthesize:(NSString *)phoneString;
{
    [self prepareForSynthesis];
	
    [eventList parsePhoneString:phoneString];  // this creates the tone groups, feet, etc.
    [eventList applyRhythm];
    [eventList applyRules];  // this applies the rules, adding events to the EventList
    [eventList generateIntonationPoints];
	
    [self continueSynthesis];
}

- (void) prepareForSynthesis;
{
    NSUserDefaults * defaults = [NSUserDefaults standardUserDefaults];
		
    [eventList setUp];
	
    [eventList setPitchMean:[[[self model] synthesisParameters] pitch]];
    [eventList setGlobalTempo:1.0];  // hard-coded defaults taken from Monet
    [eventList setShouldStoreParameters:NO];
	
    [eventList setShouldUseMacroIntonation:[defaults boolForKey:MDK_ShouldUseMacroIntonation]];
    [eventList setShouldUseMicroIntonation:[defaults boolForKey:MDK_ShouldUseMicroIntonation]];
    [eventList setShouldUseDrift:[defaults boolForKey:MDK_ShouldUseDrift]];
    //setDriftGenerator(0.5, 250, 0.5);
	setDriftGenerator(1.0, 500, 4.0);  // hard-coded defaults taken from Monet

    [eventList setRadiusMultiply:1.0];  // hard-coded defaults taken from Monet
	
    [self _takeIntonationParametersFromUI];
    [eventList setIntonationParameters:intonationParameters];
}

- (void) _takeIntonationParametersFromUI;
{
	// These are the Monet defaults we've just hard-coded (for now).
    intonationParameters.notionalPitch = 0.0;
    intonationParameters.pretonicRange = 5.0;
    intonationParameters.pretonicLift = -2.0;
    intonationParameters.tonicRange = -10.0;
    intonationParameters.tonicMovement = -6.0;
}

- (void) continueSynthesis;
{
    NSUserDefaults * defaults = [NSUserDefaults standardUserDefaults];
	
    [eventList setShouldUseSmoothIntonation:[defaults boolForKey:MDK_ShouldUseSmoothIntonation]];
    [eventList applyIntonation];
		
    [synthesizer setupSynthesisParameters:[[self model] synthesisParameters]]; // TODO (2004-08-22): This may overwrite the file type...
    [synthesizer removeAllParameters];
	
    [eventList setDelegate:synthesizer];
    [eventList generateOutput];
    [eventList setDelegate:nil];
	
    [synthesizer synthesize];		
}

@end
