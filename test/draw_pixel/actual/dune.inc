(rule
 (alias runtest)
 (deps ../main.exe)
 (action
  (run ../main.exe))
 (targets
  single_pixel.png
  corners.png
  alpha_blend.png
  scatter.png
  oob_full_left.png
  oob_full_right.png
  oob_full_top.png
  oob_full_bottom.png
  oob_full_top_left.png
  oob_full_top_right.png
  oob_full_bottom_left.png
  oob_full_bottom_right.png
  oob_edge_left.png
  oob_edge_right.png
  oob_edge_top.png
  oob_edge_bottom.png
  oob_edge_top_left.png
  oob_edge_top_right.png
  oob_edge_bottom_left.png
  oob_edge_bottom_right.png)
 (mode promote))
