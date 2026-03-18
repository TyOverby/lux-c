#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cpu/lux_cpu.h"
#include "../shared/lux.h"
#include "../utilities/stb/stb_image_write.h"

typedef void (*test_fn)(lux_instruction_buffer*);

typedef struct {
  const char* name;
  test_fn fn;
} test_case;

static void generate_dune_targets(const test_case* tests, int count) {
  printf(
      "(rule\n"
      " (alias runtest)\n"
      " (deps ../main.exe)\n"
      " (action\n"
      "  (run ../main.exe))\n"
      " (targets");
  for (int i = 0; i < count; i++) {
    printf("\n  %s.png", tests[i].name);
  }
  printf(
      ")\n"
      " (mode promote))\n");
}

static void generate_dune_comparisons(const test_case* tests, int count) {
  for (int i = 0; i < count; i++) {
    printf(
        "(rule\n"
        " (alias runtest)\n"
        " (deps \"../imgdiff.sh\" expected/%s.png actual/%s.png)\n"
        " (action\n"
        "  (bash \"%%{deps}\")))\n\n",
        tests[i].name, tests[i].name);
  }
}

static void run_tests(const test_case* tests, int count, uint32_t width, uint32_t height, int write_images) {
  for (int i = 0; i < count; i++) {
    lux_scene* scene = lux_cpu_create_scene();
    lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);

    tests[i].fn(buf);

    lux_color* output = malloc(width * height * sizeof(lux_color));
    lux_dispatch(scene, (lux_dispatch_args){.dx = 0, .dy = 0, .width = width, .height = height}, output);

    if (write_images) {
      char filename[256];
      snprintf(filename, sizeof(filename), "%s.png", tests[i].name);
      stbi_write_png(filename, (int)width, (int)height, 4, output, (int)(width * sizeof(lux_color)));
    }

    free(output);
    lux_free_scene(scene);
  }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
static int test_main(const test_case* tests, int count, uint32_t width, uint32_t height, int argc, char** argv) {
  if (argc > 1 && strcmp(argv[1], "--generate-targets") == 0) {
    generate_dune_targets(tests, count);
    return 0;
  }
  if (argc > 1 && strcmp(argv[1], "--generate-comparisons") == 0) {
    generate_dune_comparisons(tests, count);
    return 0;
  }
  if (argc > 1 && strcmp(argv[1], "--no-images") == 0) {
    run_tests(tests, count, width, height, 0);
    return 0;
  }
  run_tests(tests, count, width, height, 1);
  return 0;
}
#pragma clang diagnostic pop
