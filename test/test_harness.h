#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cpu/lux_cpu.h"
#include "../shared/lux.h"
#include "../utilities/stb/stb_image_write.h"

typedef void (*test_fn)(lux_instruction_buffer*);

typedef enum {
  TEST_IMAGE,
  TEST_FULLY_TRANSPARENT,
} test_type;

typedef struct {
  const char* name;
  test_fn fn;
  test_type type;
} test_case;

static void generate_dune_targets(const test_case* tests, int count) {
  int has_image_tests = 0;
  for (int i = 0; i < count; i++) {
    if (tests[i].type == TEST_IMAGE) {
      has_image_tests = 1;
      break;
    }
  }
  if (!has_image_tests) {
    return;
  }

  // Rule 1: generate images, capture assertion stderr, always succeed
  printf(
      "(rule\n"
      " (alias runtest)\n"
      " (deps ../main.exe)\n"
      " (action\n"
      "  (bash \"../main.exe 2>assertion_results.txt || true\"))\n"
      " (targets");
  for (int i = 0; i < count; i++) {
    if (tests[i].type == TEST_IMAGE) {
      printf("\n  %s.png", tests[i].name);
    }
  }
  printf(
      "\n  assertion_results.txt"
      ")\n"
      " (mode promote))\n\n");

  // Rule 2: check assertion results (fails if any assertions produced output)
  printf(
      "(rule\n"
      " (alias runtest)\n"
      " (deps assertion_results.txt)\n"
      " (action\n"
      "  (bash \"if [ -s assertion_results.txt ]; then cat assertion_results.txt >&2; exit 1; fi\")))\n");
}

static void generate_dune_comparisons(const test_case* tests, int count) {
  for (int i = 0; i < count; i++) {
    if (tests[i].type == TEST_IMAGE) {
      printf(
          "(rule\n"
          " (alias runtest)\n"
          " (deps \"../imgdiff.sh\" expected/%s.png actual/%s.png)\n"
          " (action\n"
          "  (bash \"%%{deps}\")))\n\n",
          tests[i].name, tests[i].name);
    }
  }
}

static int run_tests(const test_case* tests, int count, uint32_t width, uint32_t height, int write_images) {
  int failures = 0;
  for (int i = 0; i < count; i++) {
    lux_scene* scene = lux_cpu_create_scene();
    lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);

    tests[i].fn(buf);

    lux_color* output = malloc(width * height * sizeof(lux_color));
    lux_dispatch(scene, (lux_dispatch_args){.dx = 0, .dy = 0, .width = width, .height = height}, output);

    switch (tests[i].type) {
      case TEST_IMAGE:
        if (write_images) {
          char filename[256];
          snprintf(filename, sizeof(filename), "%s.png", tests[i].name);
          stbi_write_png(filename, (int)width, (int)height, 4, output, (int)(width * sizeof(lux_color)));
        }
        break;
      case TEST_FULLY_TRANSPARENT: {
        lux_color zero = {0, 0, 0, 0};
        for (uint32_t j = 0; j < width * height; j++) {
          if (memcmp(&output[j], &zero, sizeof(lux_color)) != 0) {
            fprintf(stderr, "FAIL: %s — pixel %u is (%u,%u,%u,%u), expected (0,0,0,0)\n", tests[i].name, j, output[j].r,
                    output[j].g, output[j].b, output[j].a);
            failures++;
            break;
          }
        }
        break;
      }
    }

    free(output);
    lux_free_scene(scene);
  }
  return failures;
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
    return run_tests(tests, count, width, height, 0);
  }
  return run_tests(tests, count, width, height, 1);
}
#pragma clang diagnostic pop
