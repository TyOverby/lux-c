(rule
 (alias runtest)
 (deps ../main.exe)
 (action
  (bash "../main.exe 2>assertion_results.txt || true"))
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
  oob_partial_bottom_right.png
  assertion_results.txt)
 (mode promote))

(rule
 (alias runtest)
 (deps assertion_results.txt)
 (action
  (bash "if [ -s assertion_results.txt ]; then cat assertion_results.txt >&2; exit 1; fi")))
