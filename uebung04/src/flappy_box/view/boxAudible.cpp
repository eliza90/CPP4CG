# include "flappy_box/view/boxAudible.hpp"

using namespace view;

BoxAudible::BoxAudible(const std::shared_ptr<::model::Box> _l) : l(_l){
	//void alGenSources(ALsizei n, ALuint *sourceNames);

	// Init openAL
	alutInit(0, NULL);
		
	// Generate the sources
	alGenSources(2, _al_box_source);
	alSource3f(1, AL_POSITION, 0.5, 0, 0);
	alSource3f(2, AL_POSITION, -0.5, 0, 0);

	// Create the buffer
	ALuint buffers[2];
	alGenBuffers(1, buffers);
	alutCreateBufferWaveform(ALUT_WAVEFORM_SINE, base_frequency, 90, 10);
	alGenBuffers(2, buffers);
	alutCreateBufferWaveform(ALUT_WAVEFORM_SINE, base_frequency, 90, 10);

	alSourcei(_al_box_source[0], AL_LOOPING, buffers[0]); 
	alSourcei(_al_box_source[1], AL_LOOPING, buffers[1]);

	alSourcePlay(_al_box_source[0]);
	alSourcePlay(_al_box_source[1]);

	

}

void BoxAudible::auralize(AlRenderer&){
	//float currentFrequency = target_frequency + (10 * fabs(l->getPosition().z));
}