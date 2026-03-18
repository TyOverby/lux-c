#include "lux_cpu.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct lux_cpu_scene {
  lux_instruction_buffer* buffer;
} lux_cpu_scene;

static lux_instruction_buffer* get_instruction_buffer(lux_scene* generic_scene) {
  lux_cpu_scene* scene = generic_scene->data;
  return scene->buffer;
}

static void dispatch(lux_scene* scene, lux_dispatch_args args, lux_color* output) {
  (void)scene;
  (void)output;
  for (u_int32_t y = 0; y < args.height; y++) {
    for (u_int32_t x = 0; x < args.width; x++) {
      output[y * args.width + x] = (lux_color){0, 0, 0, 255};
    }
  }
}

static void free_scene(lux_scene* scene) {
  lux_cpu_scene* cpu_scene = (lux_cpu_scene*)scene->data;
  lux_priv_free_instruction_buffer(cpu_scene->buffer);
  free(cpu_scene);
  free(scene);
}

lux_scene* lux_cpu_create_scene(void) {
  lux_scene* scene = malloc(sizeof(lux_scene));
  lux_cpu_scene* cpu_scene = malloc(sizeof(lux_cpu_scene));
  lux_instruction_buffer* buffer = lux_priv_create_instruction_buffer(1024);

  if (buffer == NULL || cpu_scene == NULL || scene == NULL) {
    free(cpu_scene);
    free(scene);
    free(cpu_scene);
    return NULL;
  }

  *cpu_scene = (lux_cpu_scene){.buffer = buffer};
  *scene = (lux_scene){
      .data = cpu_scene, .get_instruction_buffer = &get_instruction_buffer, .dispatch = &dispatch, .free = &free_scene};
  return scene;
}
