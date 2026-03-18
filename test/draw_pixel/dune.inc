(rule
 (alias runtest)
 (action
  (run ./main.exe))
 (targets
  single_pixel.png
  corners.png
  alpha_blend.png
  scatter.png)
 (mode promote))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/single_pixel.png single_pixel.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/corners.png corners.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/alpha_blend.png alpha_blend.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/scatter.png scatter.png)
 (action
  (bash "%{deps}")))

