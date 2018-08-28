open BlockTypes;

let estimateTextWidth = (text: string): float =>
  float_of_int(String.length(text) * 16);

let sumWidthMaxHeight = ((w1, h1), (w2, h2)) => (w1 +. w2, max(h1, h2));

let maxWidthSumHeight = ((w1, h1), (w2, h2)) => (max(w1, w2), h1 +. h2);

/* and getShapeListDims = (shapes: list(shape)) =>
   shapes
   ->Belt.List.map(getShapeDims)
   ->Belt.List.reduce((0., 0.), sumWidthMaxHeight); */

/* Given an unmeasured shape, build a measuredShape tree */
let rec measureShape = (shape: shape): measuredShape =>
  switch (shape) {
  | Text(str) =>
    MText((estimateTextWidth(str), BlockConfig.defaultTextHeight), str)
  | Hexagon([]) => MHexagon(BlockConfig.defaultShapeDims, [])
  | Hexagon(shapes) => measureShapes(shapes)
  | Pill([]) => MPill(BlockConfig.defaultShapeDims, [])
  | Pill(shapes) => measureShapes(shapes)
  }
and measureShapes = (shapes: list(shape)) =>
  shapes
  ->Belt.List.map(measureShape)
  ->Belt.List.reduce((0., 0.), sumWidthMaxHeight);

let measureLastBlock = (block: lastBlock): measuredLastBlock => {
  let style = List.assoc("motion", BlockStyles.styles);
  let (shapesWidth, shapesHeight) = getShapeListDims(block.headline);
  {headline: shapesWidth};
};