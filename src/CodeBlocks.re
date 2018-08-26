open BlockTypes;

let defaultSpacerWidth = 10.;
let defaultTextHeight = 20.;
let defaultShapeDims = (20., 30.);
let estimateTextWidth = (text: string) => String.length(text) * 16;

let sumWidthMaxHeight = ((w1, h1), (w2, h2)) => (w1 +. w2, max(h1, h2));

let maxWidthSumHeight = ((w1, h1), (w2, h2)) => (max(w1, w2), h1 +. h2);

let rec getShapeDims = (shape: shape) =>
  switch (shape) {
  | Text(s) => (float_of_int(estimateTextWidth(s)), defaultTextHeight)
  | Hexagon([]) => defaultShapeDims
  | Hexagon(shapes) => getShapeListDims(shapes)
  | Pill([]) => defaultShapeDims
  | Pill(shapes) => getShapeListDims(shapes)
  }
and getShapeListDims = (shapes: list(shape)) =>
  shapes
  ->Belt.List.map(getShapeDims)
  ->Belt.List.reduce((0., 0.), sumWidthMaxHeight);

let rec getFirstBlockDims = (block: firstBlock) => {
  let headlineDims = getShapeListDims(block.headline);
  let bodyDims = getMiddleBlockListDims(block.body);
  let tailDims = getTailDims(block.tail);
  maxWidthSumHeight(headlineDims, maxWidthSumHeight(bodyDims, tailDims));
}
and getMiddleBlockDims = (block: middleBlock) => {
  let headlineDims = getShapeListDims(block.headline);
  let allSectionDims = getSectionListDims(block.sections);
  maxWidthSumHeight(headlineDims, allSectionDims);
}
and getMiddleBlockListDims = (blocks: list(middleBlock)) =>
  blocks
  ->Belt.List.map(getMiddleBlockDims)
  ->Belt.List.reduce((0., 0.), maxWidthSumHeight)
and getLastBlockDims = (block: lastBlock) => getShapeListDims(block.headline)
and getSectionDims = (section: section) => {
  let bodyDims = getMiddleBlockListDims(section.body);
  let tailDims = getTailDims(section.tail);
  let footlineDims = getShapeListDims(section.footline);
  maxWidthSumHeight(footlineDims, maxWidthSumHeight(bodyDims, tailDims));
}
and getSectionListDims = (sections: list(section)) =>
  sections
  ->Belt.List.map(getSectionDims)
  ->Belt.List.reduce((0., 0.), maxWidthSumHeight)
and getTailDims = (tail: option(lastBlock)) =>
  switch (tail) {
  | None => (0., 0.)
  | Some(lastBlock) => getLastBlockDims(lastBlock)
  };

let renderFirstBlock = (block: firstBlock) => {
  let style = List.assoc("motion", BlockStyles.styles);
  let shapeDims = getShapeListDims(block.headline);
  ();
  /* let bodyDims = getMiddleBlockListDims(block.body); */
  /* BasicShape.block(w, h, mouth, style); */
};
/* Body Code Block */
/* let body = (: list(slot), children: list(code)) => {
     let attrsWidth = getSlotDims(attrs);
     let w = 100.;
     let h = 48.;
     let mouthHeight = 100.;
     let style = List.assoc("motion", BlockStyles.styles);

     [BasicShape.block(w, h, mouthHeight, style)];
   }; */