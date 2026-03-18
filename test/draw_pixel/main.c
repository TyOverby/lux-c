#include <stdlib.h>
#include <string.h>
#include "../../cpu/lux_cpu.h"
#include "../../shared/lux.h"
#include "../../utilities/stb/stb_image_write.h"

#define WIDTH 32
#define HEIGHT 32

static void write_test(const char* name, lux_scene* scene) {
  lux_color* output = malloc(WIDTH * HEIGHT * sizeof(lux_color));
  lux_dispatch(scene, (lux_dispatch_args){.dx = 0, .dy = 0, .width = WIDTH, .height = HEIGHT}, output);
  stbi_write_png(name, WIDTH, HEIGHT, 4, output, WIDTH * (int)sizeof(lux_color));
  free(output);
  lux_free_scene(scene);
}

static void test_single_pixel(void) {
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);
  lux_push_pixel(buf, 16, 16, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
  write_test("single_pixel.png", scene);
}

static void test_corners(void) {
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);
  lux_color red   = {.r = 255, .g = 0,   .b = 0,   .a = 255};
  lux_color green = {.r = 0,   .g = 255, .b = 0,   .a = 255};
  lux_color blue  = {.r = 0,   .g = 0,   .b = 255, .a = 255};
  lux_color white = {.r = 255, .g = 255, .b = 255, .a = 255};
  lux_push_pixel(buf, 0, 0, red);
  lux_push_pixel(buf, WIDTH - 1, 0, green);
  lux_push_pixel(buf, 0, HEIGHT - 1, blue);
  lux_push_pixel(buf, WIDTH - 1, HEIGHT - 1, white);
  write_test("corners.png", scene);
}

static void test_alpha_blend(void) {
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);
  lux_push_pixel(buf, 16, 16, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
  lux_push_pixel(buf, 16, 16, (lux_color){.r = 0, .g = 0, .b = 255, .a = 128});
  write_test("alpha_blend.png", scene);
}

static void test_scatter(void) {
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);
  lux_color colors[] = {
    {.r = 255, .g = 0,   .b = 0,   .a = 255},
    {.r = 0,   .g = 255, .b = 0,   .a = 255},
    {.r = 0,   .g = 0,   .b = 255, .a = 255},
    {.r = 255, .g = 255, .b = 0,   .a = 255},
    {.r = 255, .g = 0,   .b = 255, .a = 255},
    {.r = 0,   .g = 255, .b = 255, .a = 255},
  };
  int positions[][2] = {{4, 4}, {12, 8}, {20, 4}, {8, 20}, {24, 16}, {16, 28}};
  for (int i = 0; i < 6; i++) {
    lux_push_pixel(buf, positions[i][0], positions[i][1], colors[i]);
  }
  write_test("scatter.png", scene);
}

int main(void) {
  test_single_pixel();
  test_corners();
  test_alpha_blend();
  test_scatter();
  return 0;
}
