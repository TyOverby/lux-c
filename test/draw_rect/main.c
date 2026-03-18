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

static test_case tests[] = {
    {"single_rect", test_single_rect}, {"overlapping", test_overlapping}, {"alpha_rects", test_alpha_rects},
    {"full_canvas", test_full_canvas}, {"nested", test_nested},
};

int main(int argc, char** argv) {
  return test_main(tests, sizeof(tests) / sizeof(tests[0]), WIDTH, HEIGHT, argc, argv);
}
