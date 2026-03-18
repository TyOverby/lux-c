(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/single_pixel.png actual/single_pixel.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/corners.png actual/corners.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/alpha_blend.png actual/alpha_blend.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/scatter.png actual/scatter.png)
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
 (deps "../imgdiff.sh" expected/oob_edge_left.png actual/oob_edge_left.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_edge_right.png actual/oob_edge_right.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_edge_top.png actual/oob_edge_top.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_edge_bottom.png actual/oob_edge_bottom.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_edge_top_left.png actual/oob_edge_top_left.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_edge_top_right.png actual/oob_edge_top_right.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_edge_bottom_left.png actual/oob_edge_bottom_left.png)
 (action
  (bash "%{deps}")))

(rule
 (alias runtest)
 (deps "../imgdiff.sh" expected/oob_edge_bottom_right.png actual/oob_edge_bottom_right.png)
 (action
  (bash "%{deps}")))

