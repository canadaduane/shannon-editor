open TypedSvg.Attributes;

open TypedSvg.PxUnits;

open BlockStyles;
open Path;

type direction =
  | Left
  | Right;

type mouth = {
  openingHeight: float,
  footlineHeight: float,
};

let dPath = (path: path) => TypedSvg.Attributes.d(pathToString(path));

let pill = (x, y, w, h, style: blockStyle) =>
  Tea.Svg.path(
    [
      dPath([
        MoveTo(x, y),
        LineTo(x +. w, y),
        ArcTo((h /. 2.0, h /. 2.0), 0.0, false, true, (x +. w, y +. h)),
        LineTo(x, y +. h),
        ArcTo((h /. 2.0, h /. 2.0), 0.0, false, true, (x, y)),
        Close,
      ]),
      fill(Some(style.fill)),
      stroke(Some(style.outline)),
      strokeWidth(style.stroke),
    ],
    [],
  );

let hexagon = (w, h, style) => {
  let hh = h /. 2.0;

  Tea.Svg.path(
    [
      dPath([
        MoveTo(0., 0.),
        LineToRel(hh, -. hh),
        HorizontalToRel(w -. h),
        LineToRel(hh, hh),
        LineToRel(-. hh, hh),
        HorizontalToRel(-. (w -. h)),
        Close,
      ]),
      fill(Some(style.fill)),
      stroke(Some(style.outline)),
      strokeWidth(style.stroke),
    ],
    [],
  );
};

let block = (w, headingHeight, mouths: list(mouth), style) => {
  let unit = 8.0;
  let hh = headingHeight /. 2.0;
  let right = 7.0 *. unit +. w;

  /* Draw a connector tab */
  let tabPath = (dir: direction) => {
    let mul =
      switch (dir) {
      | Left => (-1.0)
      | Right => 1.0
      };
    [
      LineToRel(unit *. mul, unit),
      HorizontalToRel(unit *. 2.0 *. mul),
      LineToRel(unit *. mul, -. unit),
    ];
  };

  let makeMouth = ({openingHeight, footlineHeight}) =>
    /* Only make the mouth if its heights are positive */
    if (openingHeight > 0.0 && footlineHeight > 0.0) {
      Some(
        Belt.List.concatMany([|
          [
            /* Top of Mouth */
            HorizontalTo(8.0 *. unit),
          ],
          tabPath(Left),
          [
            /* Top of Mouth */
            HorizontalTo(2.0 *. unit),
            /* Left inner side */
            VerticalToRel(openingHeight),
            /* Bottom of Mouth */
            HorizontalTo(4.0 *. unit),
          ],
          tabPath(Right),
          [
            /* Bottom of Mouth */
            HorizontalTo(right),
            /* Right outer side */
            /* VerticalToRel(4.0 *. unit), */
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
      dPath(
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
          ],
          optionalMouths,
          [
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