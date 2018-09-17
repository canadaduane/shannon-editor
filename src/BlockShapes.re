open TypedSvg.Attributes;

open TypedSvg.PxUnits;

open BlockStyles;
open Path;

type direction =
  | Left
  | Right;

type mouth = {
  /* Height of the open mouth */
  openingHeight: float,
  /* Height of the bottom "jaw" of the mouth */
  footlineHeight: float,
};

/* Pixels per "unit", where a unit is a grid square in the scratch block design guidelines */
let unit = 8.0;

/* Helper: build an SVG "d" attribute from a path sequence */
let dFromPath = (path: path) => TypedSvg.Attributes.d(pathToString(path));

/* Helper: draw a connector tab */
let tabPath = (dir: direction) => {
  let mul =
    switch (dir) {
    | Left => (-1.0)
    | Right => 1.0
    };
  [
    LineToRel(BlockConfig.widthOfSnapRise *. mul, unit),
    HorizontalToRel(BlockConfig.widthOfSnapCenter *. mul),
    LineToRel(BlockConfig.widthOfSnapRise *. mul, -. unit),
  ];
};

/* --- Basic Shapes --- */

/* A "pill" is an oval shape with half-circles on each side */
let pill = (w, h, style: blockStyle) =>
  Tea.Svg.path(
    [
      dFromPath([
        MoveTo(0., 0.),
        LineToRel(w, 0.),
        ArcToRel((h /. 2.0, h /. 2.0), 0.0, false, true, (w, h)),
        LineToRel(0., h),
        ArcToRel((h /. 2.0, h /. 2.0), 0.0, false, true, (0., 0.)),
        Close,
      ]),
      fill(Some(style.fill)),
      stroke(Some(style.outline)),
      strokeWidth(style.stroke),
    ],
    [],
  );

/* A "hexagon" is a 6-sided shape but can potentially be horizontally very long */
let hexagon = (w, h, style) => {
  let hh = h /. 2.0;
  let innerWidth = w -. h;

  Tea.Svg.path(
    [
      dFromPath([
        MoveTo(0., 0.),
        LineToRel(hh, -. hh),
        HorizontalToRel(innerWidth),
        LineToRel(hh, hh),
        LineToRel(-. hh, hh),
        HorizontalToRel(-. innerWidth),
        Close,
      ]),
      fill(Some(style.fill)),
      stroke(Some(style.outline)),
      strokeWidth(style.stroke),
    ],
    [],
  );
};

/* Standard block with N "mouths" */
let block = (w, headingHeight, mouths: list(mouth), style) => {
  let hh = headingHeight /. 2.0;
  let right = 7.0 *. unit +. w;

  let makeMouth = ({openingHeight, footlineHeight}) =>
    /* Only make the mouth if its heights are positive */
    if (openingHeight > 0.0 && footlineHeight > 0.0) {
      Some(
        Belt.List.concatMany([|
          [
            /* Top of Mouth, has 2x margin because tab is inset within mouth */
            HorizontalTo(
              BlockConfig.widthOfSnapMargin
              +. BlockConfig.widthOfMarginPlusSnap,
            ),
          ],
          tabPath(Left),
          [
            /* Top of Mouth */
            HorizontalToRel(BlockConfig.widthOfSnapMargin *. (-1.)),
            /* Left inner side */
            VerticalToRel(openingHeight),
            /* Bottom of Mouth */
            HorizontalToRel(BlockConfig.widthOfSnapMargin),
          ],
          tabPath(Right),
          [
            /* Bottom of Mouth */
            HorizontalTo(right),
            /* Right outer side */
            VerticalToRel(footlineHeight),
          ],
        |]),
      );
    } else {
      None;
    };

  let optionalMouths =
    Belt.List.flatten(mouths->Belt.List.keepMap(makeMouth));

  /* Block Outline */
  Tea.Svg.path(
    [
      dFromPath(
        Belt.List.concatMany([|
          [
            /* Start in Upper-Left Corner */
            MoveTo(0.0, -. hh),
            /* Top */
            HorizontalToRel(BlockConfig.widthOfSnapMargin),
          ],
          tabPath(Right),
          [
            /* Top */
            HorizontalTo(right),
            /* Right side */
            VerticalTo(hh),
          ],
          optionalMouths,
          [
            /* Bottom */
            HorizontalTo(BlockConfig.widthOfMarginPlusSnap),
          ],
          tabPath(Left),
          [
            /* Bottom */
            HorizontalTo(0.0),
            /* Left side */
            Close,
          ],
        |]),
      ),
      fill(Some(style.fill)),
      stroke(Some(style.outline)),
      strokeWidth(style.stroke),
    ],
    [],
  );
};

let startBlock = (w, h, style) => {
  let hh = h /. 2.0;
  let right = 7.0 *. unit +. w;
  let browHeight = 25.;
  let browWidth = right *. (3. /. 5.);

  /* Block Outline */
  Tea.Svg.path(
    [
      dFromPath(
        Belt.List.concatMany([|
          [
            /* Start in Upper-Left Corner */
            MoveTo(0.0, -. hh),
            CurveToRel(
              (browHeight, -. browHeight),
              (browWidth /. 4. *. 3., -. browHeight),
              (browWidth, 0.0),
            ),
            /* Top */
            HorizontalTo(right),
            /* Right side */
            VerticalTo(hh),
            /* Bottom */
            HorizontalTo(6.0 *. unit),
          ],
          tabPath(Left),
          [
            /* Bottom */
            HorizontalTo(0.0),
            /* Left side */
            Close,
          ],
        |]),
      ),
      fill(Some(style.fill)),
      stroke(Some(style.outline)),
      strokeWidth(style.stroke),
    ],
    [],
  );
};

let endBlock = (w, h, style) => {
  let hh = h /. 2.0;
  let right = 7.0 *. unit +. w;

  /* Block Outline */
  Tea.Svg.path(
    [
      dFromPath(
        Belt.List.concatMany([|
          [
            /* Start in Upper-Left Corner */
            MoveTo(0.0, -. hh),
            /* Top */
            HorizontalTo(2.0 *. unit),
          ],
          tabPath(Right),
          [
            /* Top */
            HorizontalTo(right),
            /* Right side */
            VerticalTo(hh),
            /* Bottom */
            HorizontalTo(0.0),
            /* Left side */
            Close,
          ],
        |]),
      ),
      fill(Some(style.fill)),
      stroke(Some(style.outline)),
      strokeWidth(style.stroke),
    ],
    [],
  );
};