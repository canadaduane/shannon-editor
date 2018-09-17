open BlockTypes;

/* Pixels per "unit", where a unit is a grid square in the scratch block design guidelines */
let unit = 8.0;

/* Common constants used to build left-hand side of blocks, i.e. the snap-together parts */
let widthOfSnapMargin = unit *. 2.0;
let widthOfSnapRise = unit;
let widthOfSnapCenter = unit *. 2.0;
let widthOfMarginPlusSnap =
  widthOfSnapMargin +. widthOfSnapRise *. 2. +. widthOfSnapCenter;

let defaultTextHeight = 20.;
let defaultBadgeWidth = unit *. 12.;
let defaultBadgeHeight = unit *. 5.;
let defaultBlockWidth = unit *. 14.;
let defaultBlockHeight = unit *. 5.;

let defaultPadWidth = unit;
let defaultPadHeight = unit;
let defaultPadding = {
  top: defaultPadHeight,
  right: defaultPadWidth,
  bottom: defaultPadHeight,
  left: defaultPadWidth,
};

let defaultSpacerWidth = unit;

let mkBox = (w: float, h: float) => {
  width: w,
  height: h,
  padding: defaultPadding,
};

let defaultBlockBox = mkBox(defaultBlockWidth, defaultBlockHeight);
let defaultBadgeBox = mkBox(defaultBadgeWidth, defaultBadgeHeight);