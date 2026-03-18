#include "../test_harness.h"

#define WIDTH 64u
#define HEIGHT 64u

static void test_single_rect(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 10, 10, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_overlapping(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 5, 5, 30, 30, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
  lux_push_rect(buf, 20, 20, 30, 30, (lux_color){.r = 0, .g = 0, .b = 255, .a = 255});
}

static void test_alpha_rects(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 10, 10, 30, 30, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
  lux_push_rect(buf, 25, 25, 30, 30, (lux_color){.r = 0, .g = 0, .b = 255, .a = 128});
}

static void test_full_canvas(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
}

static void test_nested(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, 64, 64, (lux_color){.r = 50, .g = 50, .b = 50, .a = 255});
  lux_push_rect(buf, 8, 8, 48, 48, (lux_color){.r = 100, .g = 0, .b = 0, .a = 255});
  lux_push_rect(buf, 16, 16, 32, 32, (lux_color){.r = 0, .g = 150, .b = 0, .a = 255});
  lux_push_rect(buf, 24, 24, 16, 16, (lux_color){.r = 0, .g = 0, .b = 200, .a = 255});
}

// --- Fully out of region (should produce blank images) ---

static void test_oob_full_left(lux_instruction_buffer* buf) {
  lux_push_rect(buf, -30, 20, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_right(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 70, 20, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_top(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 20, -30, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_bottom(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 20, 70, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_top_left(lux_instruction_buffer* buf) {
  lux_push_rect(buf, -30, -30, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_top_right(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 70, -30, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_bottom_left(lux_instruction_buffer* buf) {
  lux_push_rect(buf, -30, 70, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_full_bottom_right(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 70, 70, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

// --- Partially out of region (gray background to show clipping) ---

static void test_oob_partial_left(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
  lux_push_rect(buf, -10, 20, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_partial_right(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
  lux_push_rect(buf, 54, 20, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_partial_top(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
  lux_push_rect(buf, 20, -10, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_partial_bottom(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
  lux_push_rect(buf, 20, 54, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_partial_top_left(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
  lux_push_rect(buf, -10, -10, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_partial_top_right(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
  lux_push_rect(buf, 54, -10, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_partial_bottom_left(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
  lux_push_rect(buf, -10, 54, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static void test_oob_partial_bottom_right(lux_instruction_buffer* buf) {
  lux_push_rect(buf, 0, 0, WIDTH, HEIGHT, (lux_color){.r = 40, .g = 40, .b = 40, .a = 255});
  lux_push_rect(buf, 54, 54, 20, 20, (lux_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

static test_case tests[] = {
    {"single_rect", test_single_rect},
    {"overlapping", test_overlapping},
    {"alpha_rects", test_alpha_rects},
    {"full_canvas", test_full_canvas},
    {"nested", test_nested},
    // fully out of region
    {"oob_full_left", test_oob_full_left},
    {"oob_full_right", test_oob_full_right},
    {"oob_full_top", test_oob_full_top},
    {"oob_full_bottom", test_oob_full_bottom},
    {"oob_full_top_left", test_oob_full_top_left},
    {"oob_full_top_right", test_oob_full_top_right},
    {"oob_full_bottom_left", test_oob_full_bottom_left},
    {"oob_full_bottom_right", test_oob_full_bottom_right},
    // partially out of region
    {"oob_partial_left", test_oob_partial_left},
    {"oob_partial_right", test_oob_partial_right},
    {"oob_partial_top", test_oob_partial_top},
    {"oob_partial_bottom", test_oob_partial_bottom},
    {"oob_partial_top_left", test_oob_partial_top_left},
    {"oob_partial_top_right", test_oob_partial_top_right},
    {"oob_partial_bottom_left", test_oob_partial_bottom_left},
    {"oob_partial_bottom_right", test_oob_partial_bottom_right},
};

int main(int argc, char** argv) {
  return test_main(tests, sizeof(tests) / sizeof(tests[0]), WIDTH, HEIGHT, argc, argv);
}
