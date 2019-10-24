Mix_Chunk * carregaMusica(char const file[40])
{    
    int canal_audio = 2;
    int taxa_audio = 22050;
    Uint16 formato_audio = AUDIO_S16SYS;
    int audio_buffers = 4096;

    if (Mix_OpenAudio(taxa_audio, formato_audio, canal_audio, audio_buffers) != 0)
    {
        printf("Não pode inicializar audio: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Chunk* music= Mix_LoadWAV(file);

    if (music == NULL)
    {
        printf("Não foi possível inicializar audio: %s\n", Mix_GetError());
        return NULL;
    }
    
    return music;
}

void comecaMusica(Mix_Chunk * music, int channel, int loop) 
{
    int canal;

    Mix_HaltChannel(channel);
    canal = Mix_PlayChannel(channel, music, loop);

    if (canal == -1) 
    {
        printf("Não foi possível inicializar audio: %s\n", Mix_GetError());
    }
}

void paraMusica(int channel) 
{
    Mix_HaltChannel(channel);
}