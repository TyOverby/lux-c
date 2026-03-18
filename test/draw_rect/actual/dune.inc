(rule
 (alias runtest)
 (deps ../main.exe)
 (action
  (run ../main.exe))
 (targets
  single_rect.png
  overlapping.png
  alpha_rects.png
  full_canvas.png
  nested.png
  oob_partial_left.png
  oob_partial_right.png
  oob_partial_top.png
  oob_partial_bottom.png
  oob_partial_top_left.png
  oob_partial_top_right.png
  oob_partial_bottom_left.png
  oob_partial_bottom_right.png)
 (mode promote))
