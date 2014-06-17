# include "flappy_box/view/boxAudible.hpp"

using namespace view;

BoxAudible::BoxAudible(const std::shared_ptr<::model::Box> _l) : l(_l){
	//void alGenSources(ALsizei n, ALuint *sourceNames);
	_al_box_buffer1 = alutCreateBufferWaveform(ALUT_WAVEFORM_SINE, base_frequency, 90, 10);
	_al_box_buffer2 = alutCreateBufferWaveform(ALUT_WAVEFORM_SINE, base_frequency, 90, 10);
			
	// Generate the sources
	alGenSources(1, &_al_box_source1);
	alSource3f(1, AL_POSITION, 0.5, 0, 0);

	alGenSources(1, &_al_box_source2);
	alSource3f(1, AL_POSITION, -0.5, 0, 0);

	alSourcei(_al_box_source1, AL_BUFFER, _al_box_buffer1);
	alSourcei(_al_box_source1, AL_LOOPING, AL_TRUE);

	alSourcei(_al_box_source2, AL_BUFFER, _al_box_buffer2);
	alSourcei(_al_box_source2, AL_LOOPING, AL_TRUE);

	alSourcePlay(_al_box_source1);
	alSourcePlay(_al_box_source2);
}

void BoxAudible::auralize(AlRenderer&){
	
	std::cout << "Test Sound!" << std::endl;
	vec3_type position = l->getPosition();
		
	float target_f = target_frequency + (10 * fabs(position[2]));
	float speed = target_f / base_frequency * 10;
	
	alSourcef(_al_box_source1, AL_PITCH, speed);
	alSourcef(_al_box_source2, AL_PITCH, speed);

	alSourcei(_al_box_source1, AL_BUFFER, _al_box_buffer1);
	alSourcei(_al_box_source1, AL_LOOPING, AL_TRUE);
	alSourcePlay(_al_box_source1);

	alSourcei(_al_box_source2, AL_BUFFER, _al_box_buffer2);
	alSourcei(_al_box_source2, AL_LOOPING, AL_TRUE);
	alSourcePlay(_al_box_source2);	
}

