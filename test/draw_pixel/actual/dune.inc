(rule
 (alias runtest)
 (deps ../main.exe)
 (action
  (bash "../main.exe 2>assertion_results.txt || true"))
 (targets
  single_pixel.png
  corners.png
  alpha_blend.png
  scatter.png
  assertion_results.txt)
 (mode promote))

(rule
 (alias runtest)
 (deps assertion_results.txt)
 (action
  (bash "if [ -s assertion_results.txt ]; then cat assertion_results.txt >&2; exit 1; fi")))
