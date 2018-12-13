// "frequency" or "freq" refers to a Hz value, and "pitch" refers to
// a numeric musical note with 0 for C0, 12 for C1, etc..

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define fr(i, bound) for (int i = 0; i < (bound); i++)
double const tau = 6.28318530717958647692528676655900576839433879875;
double sinTau(double n) {return sin(tau*n);}
double fractionalPart(double n) {return n - (long)n;}

static void sdlec(int line, char const *file) {
	char const *error = SDL_GetError();
	if (!error || !error[0]) return;
	printf("SDL error at line %i in %s :\n%s\n", line, file, error);
	SDL_ClearError();
}
#define _sdlec sdlec(__LINE__, __FILE__);


double const A4freq  = 440.0;
double const A4pitch =  57.0;
double const semitoneRatio = 1.059463094359295264562; // the 12th root of 2

double freqFromPitch(double pitch) {
	return pow(semitoneRatio, pitch-A4pitch)*A4freq;
}

uint32_t sampleRate = 48000; // may be changed by init(), but not after
uint32_t floatStreamSize = 1024; // must be a power of 2

SDL_AudioSpec audioSpec;
void logSpec(SDL_AudioSpec const as) {
	printf(
		" freq______%5d\n"
		" format____%5d\n"
		" channels__%5d\n"
		" silence___%5d\n"
		" samples___%5d\n"
		" size______%5d\n\n",
		as.freq,
		as.format,
		as.channels,
		as.silence,
		as.samples,
		as.size
	);
}

void audioCallback(void *_unused, uint8_t *byteStream, int byteStreamLength) {
	
}

SDL_AudioDeviceID audioDeviceId = 0;

int init(void) {
	SDL_Init(SDL_INIT_AUDIO);_sdlec;
	int audioOutDeviceCount = SDL_GetNumAudioDevices(SDL_FALSE);_sdlec;
	int audioInDeviceCount  = SDL_GetNumAudioDevices(SDL_TRUE);_sdlec;
	fr (i, audioOutDeviceCount) {
		SDL_Log("output device %d: %s\n", i, SDL_GetAudioDeviceName(i, SDL_FALSE));_sdlec;
	}
	fr (i, audioInDeviceCount) {
		SDL_Log("input device %d: %s\n", i, SDL_GetAudioDeviceName(i, SDL_TRUE));_sdlec;
	}
	SDL_AudioSpec want = {0};
	want.freq     = sampleRate;
	want.format   = AUDIO_F32;
	want.channels = 2; // stereo
	want.samples  = 1024; // must be a power of 2
	want.callback = audioCallback;
	audioDeviceId = SDL_OpenAudioDevice(NULL, 0, &want, &audioSpec, 0);_sdlec;
	puts("want:");
	logSpec(want);
	puts("audioSpec:");
	logSpec(audioSpec);
	if (!audioDeviceId) return 1;
	sampleRate = audioSpec.freq;
	floatStreamSize = audioSpec.size/sizeof(float);
	return 0;
}

void cleanup(void) {
	SDL_CloseAudioDevice(audioDeviceId);_sdlec;
	SDL_Quit();
}


int main(int argc, char const **argv) {
	if (init()) return 1;
	puts("Press enter to stop.");
	getc(stdin);
	cleanup();
	puts("exited normally");
	return 0;
}


