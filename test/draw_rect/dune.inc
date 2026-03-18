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

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_full_left.png actual/oob_full_left.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_full_right.png actual/oob_full_right.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_full_top.png actual/oob_full_top.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_full_bottom.png actual/oob_full_bottom.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_full_top_left.png actual/oob_full_top_left.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_full_top_right.png actual/oob_full_top_right.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_full_bottom_left.png actual/oob_full_bottom_left.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_full_bottom_right.png actual/oob_full_bottom_right.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_partial_left.png actual/oob_partial_left.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_partial_right.png actual/oob_partial_right.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_partial_top.png actual/oob_partial_top.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_partial_bottom.png actual/oob_partial_bottom.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_partial_top_left.png actual/oob_partial_top_left.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_partial_top_right.png actual/oob_partial_top_right.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_partial_bottom_left.png actual/oob_partial_bottom_left.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_partial_bottom_right.png actual/oob_partial_bottom_right.png)
 (action
  (bash "%{deps}")))

