#include "lux_priv.h"
#include <stdint.h>
#include "lux.h"

lux_instruction_buffer* lux_get_instruction_buffer(lux_scene* scene) {
  return scene->get_instruction_buffer(scene);
}

void lux_dispatch(lux_scene* scene, lux_dispatch_args args, lux_color* pixel_buffer) {
  scene->dispatch(scene, args, pixel_buffer);
}

void lux_free(lux_scene* scene) {
  scene->free(scene);
}

size_t lux_priv_push_instruction(lux_instruction_buffer* buffer, lux_instruction instruction) {
  size_t index = buffer->length;

  if (buffer->length >= buffer->capacity) {
    size_t new_capacity;
    if (buffer->capacity < 1024) {
      new_capacity = 1024;
    } else {
      new_capacity = (buffer->capacity * 3) / 2;
    }

    lux_instruction* new_data = (lux_instruction*)realloc(buffer->data, new_capacity * sizeof(lux_instruction));

    if (new_data == NULL) {
      return 0;
    }

    buffer->data = new_data;
    buffer->capacity = new_capacity;
  }

  buffer->data[index] = instruction;
  buffer->length++;
  return index;
}

size_t lux_push_pixel(lux_instruction_buffer* buffer, int32_t x, int32_t y, lux_color color) {
  lux_instruction_data data = (lux_instruction_data){.Pixel.x = x, .Pixel.y = y, .Pixel.color = color};
  return lux_priv_push_instruction(buffer, (lux_instruction){.kind = Pixel, .data = data});
}

size_t lux_push_rect(lux_instruction_buffer* buffer, int32_t x, int32_t y, int32_t w, int32_t h, lux_color color) {
  lux_instruction_data data =
      (lux_instruction_data){.Rect.x = x, .Rect.y = y, .Rect.w = w, .Rect.h = h, .Rect.color = color};
  return lux_priv_push_instruction(buffer, (lux_instruction){.kind = Rect, .data = data});
}

size_t lux_push_noop(lux_instruction_buffer* buffer) {
  return lux_priv_push_instruction(
      buffer, (lux_instruction){.kind = NoOp, .data = (lux_instruction_data){.NoOp.for_alignment = 0}});
}

lux_instruction_buffer* lux_priv_create_instruction_buffer(size_t capacity) {
  if (capacity == 0) {
    capacity = 1;
  }

  lux_instruction_buffer* buffer = malloc(sizeof(lux_instruction_buffer));
  lux_instruction* data = malloc(capacity * sizeof(lux_instruction));

  if (buffer == NULL || data == NULL) {
    free(buffer);
    free(data);
    return NULL;
  }

  buffer->data = data;
  buffer->length = 0;
  buffer->capacity = capacity;

  // Always push a noop to ensure that all indexes returned by future pushes return nonzero.
  lux_push_noop(buffer);

  return buffer;
}

void lux_priv_free_instruction_buffer(lux_instruction_buffer* buffer) {
  free(buffer->data);
  buffer->data = NULL;
  buffer->length = 0;
  buffer->capacity = 0;
  free(buffer);
}
