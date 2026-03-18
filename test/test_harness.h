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

static void generate_dune(const test_case* tests, int count) {
  printf(
      "(rule\n"
      " (alias runtest)\n"
      " (action\n"
      "  (run ./main.exe))\n"
      " (targets");
  for (int i = 0; i < count; i++) {
    printf("\n  %s.png", tests[i].name);
  }
  printf(
      ")\n"
      " (mode promote))\n\n");

  for (int i = 0; i < count; i++) {
    printf(
        "(rule\n"
        " (alias runtest)\n"
        " (deps \"../imgdiff.sh\" expected/%s.png %s.png)\n"
        " (action\n"
        "  (bash \"%%{deps}\")))\n\n",
        tests[i].name, tests[i].name);
  }
}

static void run_tests(const test_case* tests, int count, uint32_t width, uint32_t height) {
  for (int i = 0; i < count; i++) {
    lux_scene* scene = lux_cpu_create_scene();
    lux_instruction_buffer* buf = lux_get_instruction_buffer(scene);

    tests[i].fn(buf);

    lux_color* output = malloc(width * height * sizeof(lux_color));
    lux_dispatch(scene, (lux_dispatch_args){.dx = 0, .dy = 0, .width = width, .height = height}, output);

    char filename[256];
    snprintf(filename, sizeof(filename), "%s.png", tests[i].name);
    stbi_write_png(filename, (int)width, (int)height, 4, output, (int)(width * sizeof(lux_color)));

    free(output);
    lux_free_scene(scene);
  }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
static int test_main(const test_case* tests, int count, uint32_t width, uint32_t height, int argc, char** argv) {
  if (argc > 1 && strcmp(argv[1], "--generate-dune") == 0) {
    generate_dune(tests, count);
    return 0;
  }
  run_tests(tests, count, width, height);
  return 0;
}
#pragma clang diagnostic pop
