#include <stdlib.h>
#include "../../cpu/lux_cpu.h"
#include "../../shared/lux.h"
#include "../../utilities/stb/stb_image_write.h"

int main(void) {
  uint32_t width = 32, height = 32;
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buffer = lux_get_instruction_buffer(scene);

  lux_push_pixel(buffer, 1, 1, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
  lux_push_rect(buffer, 5, 5, width - 20, height - 20, (lux_color){.r = 255, .g = 255, .b = 255, .a = 255});

  lux_color* output = malloc(width * height * sizeof(lux_color));
  lux_dispatch(scene, (lux_dispatch_args){.dx = 0, .dy = 0, .width = width, .height = height}, output);
  stbi_write_png("output.png", (int)width, (int)height, 4, output, (int)(width * sizeof(lux_color)));
}
