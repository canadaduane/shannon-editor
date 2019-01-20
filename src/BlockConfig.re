/* Pixels per "unit", where a unit is a grid square in the scratch block design guidelines */
let unit = 8.0;

/* Common constants used to build left-hand side of blocks, i.e. the snap-together parts */
let widthOfSnapMargin = unit *. 2.0;
let widthOfSnapRise = unit;
let widthOfSnapCenter = unit *. 2.0;
let widthOfMarginPlusSnap =
  widthOfSnapMargin +. widthOfSnapRise *. 2. +. widthOfSnapCenter;

let defaultTextHeight = 20.;
let defaultTagWidth = unit *. 12.;
let defaultTagHeight = unit *. 5.;
let defaultBlockWidth = unit *. 14.;
let defaultBlockHeight = unit *. 5.;

let defaultMarginLeftRight = 0.;
let defaultMarginTopBottom = unit;
let defaultMargin: Margin.t = {
  top: defaultMarginTopBottom,
  right: defaultMarginLeftRight,
  bottom: defaultMarginTopBottom,
  left: defaultMarginLeftRight,
};

let defaultSpacerWidth = unit;