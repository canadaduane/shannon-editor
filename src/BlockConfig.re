/* Pixels per "unit", where a unit is a grid square in the scratch block design guidelines */
let unit = 8.0;

/* Common constants used to build left-hand side of blocks, i.e. the snap-together parts */
let widthOfSnapMargin = unit *. 2.0;
let widthOfSnapRise = unit;
let widthOfSnapCenter = unit *. 2.0;
let widthOfMarginPlusSnap =
  widthOfSnapMargin +. widthOfSnapRise *. 2. +. widthOfSnapCenter;

let defaultTextHeight = 20.;
let defaultBadgeDim = (50., 30.);
let defaultBlockDim = (50., 30.);

/* let defaultSpacerWidth = 10.; */