/*
    RTKFM.h - (Almost an) API for Realtek RTL2832U FM demodulation
	Copyright (C) 2017  OneTransistor <one1transistor@gmail.com>


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef RTKFM_H
#define RTKFM_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Open the default (first ?) device. Have no idea how to manage multiple devices.
 * Returns true id succeeded. */
bool RTFM_OpenDevice();

/* Close the opened device. Returns true if successful */
bool RTFM_CloseDevice();

/* No idea how to use */
bool RTFM_DebugCMD(); // ???

/* Set sample rate of audio signal. Usually 48000 Hz is OK.
 * Returns true if successful */
bool RTFM_SetAudioSampleRate(uint32_t samplerate);

/* Enable or disable deemphasis. Don't know what time constant it uses.
 * Probably by system locale? */
bool RTFM_SetDeemphasisTC(bool enabled);

/* Set signal quality threshold to stop scan (0..100)*/
bool RTFM_SetScanStopQuality(uint8_t quality);

/* Returns tuner limits in kHz, not FM band limits.
 * Example: lowLimit = 44000, highLimit = 885000 */
bool RTFM_GetTunerRange(uint32_t &lowLimit, uint32_t &highLimit);

/* Returns parameters of PCM stream that will be passed to PCMCallBack.
 * channels (1 = mono, 2 = stereo)
 * samplerate is usually 48000
 * samplesize is 16 bits (integer) */
bool RTFM_GetPCMInfo(uint8_t &channels, uint32_t &samplerate, uint8_t &samplesize);

/* Set frequency in kHz */
bool RTFM_SetFrequency(uint32_t frequency);

/* gets signal lock - don't know what exactly it refers to */
bool RTFM_GetSignalLock(bool &lock);

/* gets signal quality (0..100) */
bool RTFM_GetSignalQuality(uint8_t &quality);

/* gets signal quality control register */
bool RTFM_GetSignalQualityCtr(uint8_t &ctr);

/* sets signal quality control register:
 * 0x01: Soft Mute
 * 0x02: Mono/Stereo Blend
 * 0x04: Mono/Stereo Switch
 * 0x08: High Cut Control (https://github.com/alnicol/Realtek-2832U/blob/master/RadioLib/RadioData.cs)
 * Default value is 0x0B (11), which means High Cut, Soft Mute and M/S Blend are enabled */
bool RTFM_SetSignalQualityCtr(uint8_t ctr);

/* gets RDS signal sync - if RDS service exists */
bool RTFM_GetRDSSync(bool &sync);

/* gets RDS control register */
bool RTFM_GetRDSCtr(uint8_t &ctr);

/* sets RDS control register
 * 0x01: Error Correction
 * ctr >> 1: Threshold (https://github.com/alnicol/Realtek-2832U/blob/master/RadioLib/RadioData.cs) */
bool RTFM_SetRDSCtr(uint8_t ctr);

/* gets RDS signal quality (0..100) */
bool RTFM_GetRDSQuality(uint8_t &quality);

/* perform scan starting - not yet tested */
bool RTFM_ScanNextProg(uint32_t startFrequency,
                       uint8_t interval,
                       bool direction,
                       uint32_t maxSearch,
                       uint32_t &newFrequency,
                       uint8_t &newQuality);

typedef void(*PCMCallBack)(int16_t *buf, uint32_t len);

/* set callback function that will pass PCM audio futher to sound card output */
bool RTFM_SetPCMCallBack(PCMCallBack cb);


typedef void(*RDSCallBack)(int8_t *buf, uint8_t len);

/* set callback function that will process RDS raw bytes */
bool RTFM_SetRDSCallBack(RDSCallBack cb);

/* Start the device */
bool RTFM_Start();

/* Stop the device */
bool RTFM_Stop();

/* Enable RDS - is enabled by default (?) */
bool RTFM_StartRDS();

/* Disable RDS */
bool RTFM_StopRDS();


#ifdef __cplusplus
}
#endif

#endif // RTKFM_H
