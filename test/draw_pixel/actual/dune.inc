(rule
 (alias runtest)
 (deps ../main.exe)
 (action
  (run ../main.exe))
 (targets
  single_pixel.png
  corners.png
  alpha_blend.png
  scatter.png)
 (mode promote))
