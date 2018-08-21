open Tea.Svg;

open TypedSvg;

open TypedSvg.PxUnits;

open TypedSvg.Types;

open TypedSvg.Attributes;

open Path;

let svgAreaProportional =
    (~width=500., ~height=500., ~maxX=100., ~maxY=100., children) =>
  Tea.Svg.svg(
    [
      TypedSvg.PxUnits.width(width),
      TypedSvg.PxUnits.height(height),
      viewBox(0., 0., maxX, maxY),
    ],
    children,
  );

let svgArea = (width, height, children) =>
  svgAreaProportional(~width, ~height, ~maxX=width, ~maxY=height, children);

let translate = (x: float, y: float, children) =>
  g([transform([Translate(x, y)])], children);

let dPath = (path: Path.path) => d(Path.pathToString(path));

let pill = (x, y, w, h, outlineColor) =>
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
      fill(Some(Color("white"))),
      stroke(Some(outlineColor)),
      strokeWidth(1.5),
    ],
    [],
  );

type direction =
  | Left
  | Right;

let block = (w, h, mouthHeight) => {
  let fillColor = Color("#4797ff");
  let outlineColor = Color("#4280d7");
  let unit = 10.0;
  let hh = h /. 2.0;
  let right = 70.0 +. w;

  /* Draw a connector tab */
  let tabPath = (dir: direction) => {
    let mul =
      switch (dir) {
      | Left => (-1.0)
      | Right => 1.0
      };
    [
      LineToRel((unit *. mul, unit)),
      HorizontalToRel(unit *. 2.0 *. mul),
      LineToRel((unit *. mul, -. unit)),
    ];
  };

  let optionalMouth =
    if (mouthHeight > 0.0) {
      Belt.List.concatMany([|
        [
          /* Top of Mouth */
          HorizontalTo(80.0),
        ],
        tabPath(Left),
        [
          /* Top of Mouth */
          HorizontalTo(20.0),
          /* Left inner side */
          VerticalToRel(mouthHeight),
          /* Bottom of Mouth */
          HorizontalTo(40.0),
        ],
        tabPath(Right),
        [
          /* Bottom of Mouth */
          HorizontalTo(right),
          /* Right outer side */
          VerticalToRel(40.0),
        ],
      |]);
    } else {
      [];
    };

  [
    /* Block Outline */
    Tea.Svg.path(
      [
        dPath(
          Belt.List.concatMany([|
            [
              /* Start in Upper-Left Corner */
              MoveTo(0.0, -. hh),
              /* Top */
              HorizontalTo(20.0),
            ],
            tabPath(Right),
            [
              /* Top */
              HorizontalTo(right),
              /* Right side */
              VerticalTo(hh),
            ],
            optionalMouth,
            [
              /* Bottom */
              HorizontalTo(60.0),
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
        fill(Some(fillColor)),
        stroke(Some(outlineColor)),
        strokeWidth(1.5),
      ],
      [],
    ),
  ];
};