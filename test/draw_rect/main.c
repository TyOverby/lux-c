#include <stdlib.h>
#include <string.h>
#include "../../cpu/lux_cpu.h"
#include "../../shared/lux.h"
#include "../../utilities/stb/stb_image_write.h"

#define WIDTH 64u
#define HEIGHT 64u

static void write_test(const char* name, lux_scene* scene) {
  lux_color* output = malloc(WIDTH * HEIGHT * sizeof(lux_color));
  lux_dispatch(scene, (lux_dispatch_args){.dx = 0, .dy = 0, .width = WIDTH, .height = HEIGHT}, output);
  stbi_write_png(name, WIDTH, HEIGHT, 4, output, WIDTH * (int)sizeof(lux_color));
  free(output);
  lux_free_scene(scene);
}

static void test_single_rect(void) {
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);
  lux_push_rect(buf, 10, 10, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
  write_test("single_rect.png", scene);
}

static void test_overlapping(void) {
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);
  lux_push_rect(buf, 5, 5, 30, 30, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
  lux_push_rect(buf, 20, 20, 30, 30, (lux_color){.r = 0, .g = 0, .b = 255, .a = 255});
  write_test("overlapping.png", scene);
}

static void test_alpha_rects(void) {
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);
  lux_push_rect(buf, 10, 10, 30, 30, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
  lux_push_rect(buf, 25, 25, 30, 30, (lux_color){.r = 0, .g = 0, .b = 255, .a = 128});
  write_test("alpha_rects.png", scene);
}

static void test_full_canvas(void) {
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
  write_test("full_canvas.png", scene);
}

static void test_nested(void) {
  lux_scene* scene = lux_cpu_create_scene();
  lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);
  lux_push_rect(buf, 0, 0, 64, 64, (lux_color){.r = 50, .g = 50, .b = 50, .a = 255});
  lux_push_rect(buf, 8, 8, 48, 48, (lux_color){.r = 100, .g = 0, .b = 0, .a = 255});
  lux_push_rect(buf, 16, 16, 32, 32, (lux_color){.r = 0, .g = 150, .b = 0, .a = 255});
  lux_push_rect(buf, 24, 24, 16, 16, (lux_color){.r = 0, .g = 0, .b = 200, .a = 255});
  write_test("nested.png", scene);
}

int main(void) {
  test_single_rect();
  test_overlapping();
  test_alpha_rects();
  test_full_canvas();
  test_nested();
  return 0;
}
