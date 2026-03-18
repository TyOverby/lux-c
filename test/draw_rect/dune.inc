(rule
 (alias runtest)
 (action
  (run ./main.exe))
 (targets
  single_rect.png
  overlapping.png
  alpha_rects.png
  full_canvas.png
  nested.png)
 (mode promote))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" single_rect.expected.png single_rect.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" overlapping.expected.png overlapping.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" alpha_rects.expected.png alpha_rects.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" full_canvas.expected.png full_canvas.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" nested.expected.png nested.png)
 (action
  (bash "%{deps}")))

