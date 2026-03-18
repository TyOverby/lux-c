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
 (deps "../imgdiff.sh" expected/single_rect.png single_rect.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/overlapping.png overlapping.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/alpha_rects.png alpha_rects.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/full_canvas.png full_canvas.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/nested.png nested.png)
 (action
  (bash "%{deps}")))

