#include "lux_cpu.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../shared/lux_priv.h"

typedef struct lux_cpu_scene {
  lux_instruction_buffer* buffer;
} lux_cpu_scene;

static lux_instruction_buffer* get_instruction_buffer(lux_scene* generic_scene) {
  lux_cpu_scene* scene = generic_scene->data;
  return scene->buffer;
}

static void free_scene(lux_scene* scene) {
  if (scene == NULL) {
    return;
  }

  lux_cpu_scene* cpu_scene = scene->data;
  lux_priv_free_instruction_buffer(cpu_scene->buffer);
  free(cpu_scene);
  free(scene);
}

static void dispatch(lux_scene*, lux_dispatch_args, lux_color*);

lux_scene* lux_cpu_create_scene(void) {
  lux_scene* scene = malloc(sizeof(lux_scene));
  lux_cpu_scene* cpu_scene = malloc(sizeof(lux_cpu_scene));
  lux_instruction_buffer* buffer = lux_priv_create_instruction_buffer(1024);

  if (buffer == NULL || cpu_scene == NULL || scene == NULL) {
    free(cpu_scene);
    free(scene);
    free(buffer);
    return NULL;
  }

  *cpu_scene = (lux_cpu_scene){.buffer = buffer};
  *scene = (lux_scene){
      .data = cpu_scene, .get_instruction_buffer = &get_instruction_buffer, .dispatch = &dispatch, .free = &free_scene};
  return scene;
}

static void write_pixel(lux_color* output, int32_t x, int32_t y, uint32_t width, lux_color color) {
  if (x >= 0 && x < (int32_t)width && y >= 0 && y < (int32_t)width) {
    if (color.a == 255) {
      output[(size_t)y * width + (size_t)x] = color;
    } else {
      lux_color dst = output[(size_t)y * width + (size_t)x];
      uint32_t src_a = color.a;
      uint32_t dst_a = dst.a;
      uint32_t inv_src_a = 255 - src_a;
      uint32_t out_a = src_a + (dst_a * inv_src_a + 127) / 255;
      lux_color out;

      if (out_a == 0) {
        out = (lux_color){0, 0, 0, 0};
      } else {
        out.r = (uint8_t)((src_a * color.r + (inv_src_a * dst_a * dst.r) / 255 + out_a / 2) / out_a);
        out.g = (uint8_t)((src_a * color.g + (inv_src_a * dst_a * dst.g) / 255 + out_a / 2) / out_a);
        out.b = (uint8_t)((src_a * color.b + (inv_src_a * dst_a * dst.b) / 255 + out_a / 2) / out_a);
        out.a = (uint8_t)out_a;
      }

      output[(size_t)y * width + (size_t)x] = out;
    }
  }
}

static void draw_pixel(lux_instr_pixel instr, lux_dispatch_args args, lux_color* output) {
  int32_t x = instr.x - args.dx;
  int32_t y = instr.y - args.dy;
  write_pixel(output, x, y, args.width, instr.color);
}

static void draw_rect(lux_instr_rect instr, lux_dispatch_args args, lux_color* output) {
  // TODO: bail out of these loops early if remainder of row or columns is out of bounds.
  int32_t x = instr.x - args.dx;
  int32_t y = instr.y - args.dy;
  for (int32_t dy = 0; dy < (int32_t)instr.h; dy++) {
    for (int32_t dx = 0; dx < (int32_t)instr.w; dx++) {
      write_pixel(output, x + dx, y + dy, args.width, instr.color);
    }
  }
}

static void dispatch(lux_scene* scene, lux_dispatch_args args, lux_color* output) {
  lux_cpu_scene* cpu_scene = scene->data;
  lux_instruction_buffer* buffer = cpu_scene->buffer;

  // Clear output buffer
  for (uint32_t y = 0; y < args.height; y++) {
    for (uint32_t x = 0; x < args.width; x++) {
      output[y * args.width + x] = (lux_color){0, 0, 0, 0};
    }
  }

  for (size_t i = 0; i < buffer->length; i++) {
    lux_instruction instr = buffer->data[i];
    switch (instr.kind) {
      case NoOp:
        break;
      case Pixel:
        draw_pixel(instr.data.Pixel, args, output);
        break;
      case Rect:
        draw_rect(instr.data.Rect, args, output);
        break;
    }
  }
}
