/* Type Definitions */
type margin = {
  top: float,
  right: float,
  bottom: float,
  left: float,
};
type t = margin;

/* Type Helper Functions */
let zero: margin = {top: 0., right: 0., bottom: 0., left: 0.};

let add = (p1: margin, p2: margin): margin => {
  top: p1.top +. p2.top,
  right: p1.right +. p2.right,
  bottom: p1.bottom +. p2.bottom,
  left: p1.left +. p2.left,
};