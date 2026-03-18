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

// --- Out of bounds: fully off each edge and corner (should produce blank images) ---

static void test_oob_full_left(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, -10, 16, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_right(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, WIDTH + 10, 16, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_top(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, 16, -10, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_bottom(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, 16, HEIGHT + 10, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_top_left(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, -10, -10, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_top_right(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, WIDTH + 10, -10, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_bottom_left(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, -10, HEIGHT + 10, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_bottom_right(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, WIDTH + 10, HEIGHT + 10, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

// --- Out of bounds: just past each edge and corner (one pixel off) ---

static void test_oob_edge_left(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, -1, 16, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_edge_right(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, WIDTH, 16, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_edge_top(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, 16, -1, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_edge_bottom(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, 16, HEIGHT, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_edge_top_left(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, -1, -1, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_edge_top_right(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, WIDTH, -1, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_edge_bottom_left(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, -1, HEIGHT, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_edge_bottom_right(lux_instruction_buffer* buf) {
  lux_push_pixel(buf, WIDTH, HEIGHT, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static test_case tests[] = {
    {"single_pixel", test_single_pixel},
    {"corners", test_corners},
    {"alpha_blend", test_alpha_blend},
    {"scatter", test_scatter},
    // fully out of bounds
    {"oob_full_left", test_oob_full_left},
    {"oob_full_right", test_oob_full_right},
    {"oob_full_top", test_oob_full_top},
    {"oob_full_bottom", test_oob_full_bottom},
    {"oob_full_top_left", test_oob_full_top_left},
    {"oob_full_top_right", test_oob_full_top_right},
    {"oob_full_bottom_left", test_oob_full_bottom_left},
    {"oob_full_bottom_right", test_oob_full_bottom_right},
    // one pixel past each edge
    {"oob_edge_left", test_oob_edge_left},
    {"oob_edge_right", test_oob_edge_right},
    {"oob_edge_top", test_oob_edge_top},
    {"oob_edge_bottom", test_oob_edge_bottom},
    {"oob_edge_top_left", test_oob_edge_top_left},
    {"oob_edge_top_right", test_oob_edge_top_right},
    {"oob_edge_bottom_left", test_oob_edge_bottom_left},
    {"oob_edge_bottom_right", test_oob_edge_bottom_right},
};

int main(int argc, char** argv) {
  return test_main(tests, sizeof(tests) / sizeof(tests[0]), WIDTH, HEIGHT, argc, argv);
}
