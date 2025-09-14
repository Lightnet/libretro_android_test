#include <libretro.h>
#include <stdio.h>

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;

void retro_init(void) { printf("Test core initialized\n"); }
void retro_deinit(void) { printf("Test core deinitialized\n"); }
unsigned retro_api_version(void) { return RETRO_API_VERSION; }
void retro_get_system_info(struct retro_system_info *info) {
    info->library_name = "TestLib";
    info->library_version = "1.0";
    info->valid_extensions = NULL;
    info->need_fullpath = false;
    info->block_extract = false;
}
void retro_get_system_av_info(struct retro_system_av_info *info) {}
void retro_set_controller_port_devices(struct retro_input_descriptor *input, unsigned port) {}
void retro_set_environment(retro_environment_t cb)
{
   environ_cb = cb;
   struct retro_variable variables[] = {
      { "testgl_resolution", "Internal resolution; 320x240|360x480|480x272|512x384|512x512|640x240|640x448|640x480|720x576|800x600|960x720|1024x768|1024x1024|1280x720|1280x960|1600x1200|1920x1080|1920x1440|1920x1600|2048x2048" },
      { NULL, NULL },
   };
   bool no_rom = true;
   cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_rom);
   cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
}
void retro_set_video_refresh(retro_video_refresh_t cb) {}
void retro_set_audio_sample(retro_audio_sample_t cb) {}
void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {}
void retro_set_input_poll(retro_input_poll_t cb) {}
void retro_set_input_state(retro_input_state_t cb) {}
void retro_run(void) { printf("Test core running\n"); }
bool retro_load_game(const struct retro_game_info *game) { return true; }
void retro_unload_game(void) {}
unsigned retro_get_region(void) { return RETRO_REGION_NTSC; }