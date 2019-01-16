type box = {
  width: float,
  height: float,
  margin: Margin.margin /* margin outside */
};
type t = box;

let zero: box = {width: 0., height: 0., margin: Margin.zero};

let outerWidth = (box: box): float =>
  box.width +. box.margin.left +. box.margin.right;

let outerHeight = (box: box): float =>
  box.height +. box.margin.top +. box.margin.bottom;

let innerDim = (box: box): Dim.t => {width: box.width, height: box.height};