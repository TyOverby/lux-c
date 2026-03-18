#include "../test_harness.h"

#define WIDTH 32
#define HEIGHT 32

static void test_single_pixel(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, 16, 16, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_corners(lux_instruction_buffer* buf) {
  lux_color red = {.r = 255, .g = 0, .b = 0, .a = 255};
  lux_color green = {.r = 0, .g = 255, .b = 0, .a = 255};
  lux_color blue = {.r = 0, .g = 0, .b = 255, .a = 255};
  lux_color white = {.r = 255, .g = 255, .b = 255, .a = 255};
  lux_push_pixel(buf, 0, 0, red);
  lux_push_pixel(buf, WIDTH - 1, 0, green);
  lux_push_pixel(buf, 0, HEIGHT - 1, blue);
  lux_push_pixel(buf, WIDTH - 1, HEIGHT - 1, white);
}

static void test_alpha_blend(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, 16, 16, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
  lux_push_pixel(buf, 16, 16, (lux_color){.r = 0, .g = 0, .b = 255, .a = 128});
}

static void test_scatter(lux_instruction_buffer* buf) {
  lux_color colors[] = {
      {.r = 255, .g = 0, .b = 0, .a = 255},   {.r = 0, .g = 255, .b = 0, .a = 255},
      {.r = 0, .g = 0, .b = 255, .a = 255},   {.r = 255, .g = 255, .b = 0, .a = 255},
      {.r = 255, .g = 0, .b = 255, .a = 255}, {.r = 0, .g = 255, .b = 255, .a = 255},
  };
  int positions[][2] = {{4, 4}, {12, 8}, {20, 4}, {8, 20}, {24, 16}, {16, 28}};
  for (int i = 0; i < 6; i++) {
    lux_push_pixel(buf, positions[i][0], positions[i][1], colors[i]);
  }
}

static test_case tests[] = {
    {"single_pixel", test_single_pixel},
    {"corners", test_corners},
    {"alpha_blend", test_alpha_blend},
    {"scatter", test_scatter},
};

int main(int argc, char** argv) {
  return test_main(tests, sizeof(tests) / sizeof(tests[0]), WIDTH, HEIGHT, argc, argv);
}
