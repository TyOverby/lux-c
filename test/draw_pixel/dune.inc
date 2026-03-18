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

