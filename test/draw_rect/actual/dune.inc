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
  nested.png)
 (mode promote))
