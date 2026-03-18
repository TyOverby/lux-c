(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/single_rect.png actual/single_rect.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/overlapping.png actual/overlapping.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/alpha_rects.png actual/alpha_rects.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/full_canvas.png actual/full_canvas.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/nested.png actual/nested.png)
 (action
  (bash "%{deps}")))

