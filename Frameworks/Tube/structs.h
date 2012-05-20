//  This file is part of Gnuspeech, an extensible, text-to-speech package, based on real-time, articulatory, speech-synthesis-by-rules. 
//  Copyright 1991-2012 David R. Hill, Leonard Manzara, Craig Schock

#ifndef __STRUCTS_H
#define __STRUCTS_H

#include <stdint.h> // For uint8_t, uint32_t, etc.
#include <stdio.h> // For FILE
#include "ring_buffer.h"
#include "wavetable.h"

#import "TRMParameters.h"

// Oropharynx Regions
#define TRM_R1          0      //  S1
#define TRM_R2          1      //  S2
#define TRM_R3          2      //  S3
#define TRM_R4          3      //  S4 & S5
#define TRM_R5          4      //  S6 & S7
#define TRM_R6          5      //  S8
#define TRM_R7          6      //  S9
#define TRM_R8          7      //  S10
#define TOTAL_REGIONS   8

// Nasal Tract Sections
#define TRM_N1                    0
#define TRM_VELUM                 TRM_N1
#define TRM_N2                    1
#define TRM_N3                    2
#define TRM_N4                    3
#define TRM_N5                    4
#define TRM_N6                    5
#define TOTAL_NASAL_SECTIONS      6


// Sample Rate Conversion Constants
#define ZERO_CROSSINGS            13                           // Source cutoff frequency
#define LP_CUTOFF                 (11.0/13.0)                  // 0.846 of Nyquist

#define N_BITS                    16
#define L_BITS                    8
#define L_RANGE                   256                          // must be 2^L_BITS
#define M_BITS                    8
#define M_RANGE                   256                          // must be 2^M_BITS
#define FRACTION_BITS             (L_BITS + M_BITS)
#define FRACTION_RANGE            65536                        // must be 2^FRACTION_BITS
#define FILTER_LENGTH             (ZERO_CROSSINGS * L_RANGE)
#define FILTER_LIMIT              (FILTER_LENGTH - 1)

#define N_MASK                    0xFFFF0000
#define L_MASK                    0x0000FF00
#define M_MASK                    0x000000FF
#define FRACTION_MASK             0x0000FFFF

#define nValue(x)                 (((x) & N_MASK) >> FRACTION_BITS)
#define lValue(x)                 (((x) & L_MASK) >> M_BITS)
#define mValue(x)                 ((x) & M_MASK)
#define fractionValue(x)          ((x) & FRACTION_MASK)

#define OUTPUT_SRATE_LOW          22050.0
#define OUTPUT_SRATE_HIGH         44100.0

// Variables for sample rate conversion
typedef struct _TRMSampleRateConverter {
    double sampleRateRatio;
    double h[FILTER_LENGTH], deltaH[FILTER_LENGTH];
    uint32_t timeRegisterIncrement, filterIncrement, phaseIncrement;
    uint32_t timeRegister;

    // Temporary sample storage values
    double maximumSampleValue;
    int32_t numberSamples;
    FILE *tempFilePtr;
} TRMSampleRateConverter;

// Oropharynx scattering junction coefficients (between each region)
#define C1                        TRM_R1     // R1-R2 (S1-S2)
#define C2                        TRM_R2     // R2-R3 (S2-S3)
#define C3                        TRM_R3     // R3-R4 (S3-S4)
#define C4                        TRM_R4     // R4-R5 (S5-S6)
#define C5                        TRM_R5     // R5-R6 (S7-S8)
#define C6                        TRM_R6     // R6-R7 (S8-S9)
#define C7                        TRM_R7     // R7-R8 (S9-S10)
#define C8                        TRM_R8     // R8-AIR (S10-AIR)
#define TOTAL_COEFFICIENTS        TOTAL_REGIONS

// Oropharynx sections
#define S1                        0      // R1
#define S2                        1      // R2
#define S3                        2      // R3
#define S4                        3      // R4
#define S5                        4      // R4
#define S6                        5      // R5
#define S7                        6      // R5
#define S8                        7      // R6
#define S9                        8      // R7
#define S10                       9      // R8
#define TOTAL_SECTIONS            10

// Nasal tract coefficients
#define NC1                       TRM_N1     // N1-N2
#define NC2                       TRM_N2     // N2-N3
#define NC3                       TRM_N3     // N3-N4
#define NC4                       TRM_N4     // N4-N5
#define NC5                       TRM_N5     // N5-N6
#define NC6                       TRM_N6     // N6-AIR
#define TOTAL_NASAL_COEFFICIENTS  TOTAL_NASAL_SECTIONS

// Three-way junction alpha coefficients
#define LEFT                      0
#define RIGHT                     1
#define UPPER                     2
#define TOTAL_ALPHA_COEFFICIENTS  3

// Frication injection coefficients
#define FC1                       0      // S3
#define FC2                       1      // S4
#define FC3                       2      // S5
#define FC4                       3      // S6
#define FC5                       4      // S7
#define FC6                       5      // S8
#define FC7                       6      // S9
#define FC8                       7      // S10
#define TOTAL_FRIC_COEFFICIENTS   8


// Scaling constant for input to vocal tract and throat (matches DSP)
//#define VT_SCALE                  0.03125       // 2^(-5)

// this is a temporary fix only, to try to match dsp synthesizer
#define VT_SCALE                  0.125         // 2^(-3)

// Bi-directional transmission line pointers
#define TOP                       0
#define BOTTOM                    1

#endif
