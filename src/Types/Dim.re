module Float = Utils.Float;

/* Type Definitions */
type dim = {
  width: float,
  height: float,
};
type t = dim;

/* Type Helper Functions */
let zero: dim = {width: 0., height: 0.};

let sumWidthMaxHeight = (dim1: dim, dim2: dim): dim => {
  width: Float.(dim1.width + dim2.width),
  height: max(dim1.height, dim2.height),
};

let maxWidthSumHeight = (dim1: dim, dim2: dim): dim => {
  width: max(dim1.width, dim2.width),
  height: Float.(dim1.height + dim2.height),
};