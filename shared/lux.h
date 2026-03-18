#pragma once

#include <stddef.h>
#include <stdint.h>

#define LUX_NODISCARD __attribute__((warn_unused_result))

typedef struct lux_scene lux_scene;
typedef struct lux_instruction_buffer lux_instruction_buffer;

typedef struct {
  uint8_t r, g, b, a;
} lux_color;

// Returns an instruction buffer that you can use to push drawing instructions.
// Use of any instruction buffer after a call to lux_dispatch is undefined.
LUX_NODISCARD lux_instruction_buffer* lux_get_instruction_buffer(lux_scene*);

// Pushes a pixel to be drawn to the instruction buffer.  Returns `0` if the buffer can't grow to fit the new
// instruction, non-zero otherwise.
size_t lux_push_pixel(lux_instruction_buffer*, int32_t x, int32_t y, lux_color color);

// Pushes a rectangle to be drawn to the instruction buffer.  Returns `0` if the buffer can't grow to fit the new
// instruction, non-zero otherwise.
size_t lux_push_rect(lux_instruction_buffer*, int32_t x, int32_t y, uint32_t w, uint32_t h, lux_color color);

typedef struct {
  int32_t dx, dy;
  uint32_t width, height;
} lux_dispatch_args;

// Dispatches the instruction buffer to the scene and fills in the pixel buffer.
void lux_dispatch(lux_scene*, lux_dispatch_args, lux_color*);

//
void lux_free_scene(lux_scene*);
