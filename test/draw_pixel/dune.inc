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
 (deps "../imgdiff.sh" single_pixel.expected.png single_pixel.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" corners.expected.png corners.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" alpha_blend.expected.png alpha_blend.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" scatter.expected.png scatter.png)
 (action
  (bash "%{deps}")))

