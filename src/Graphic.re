open Tea.Svg;

open TypedSvg;

open TypedSvg.PxUnits;

open TypedSvg.Types;

open TypedSvg.Attributes;

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

let block = (w, h) => {
  let fillColor = Color("#4797ff");
  let outlineColor = Color("#4280d7");
  /* let corner = 5.0; */
  let unit = 10.0;
  let hh = h /. 2.0;
  /* let width1 = 20.;
     let width2 = 40.;
     let width3 = 150.; */
  let right = 70.0 +. w;
  /* let holeX = 70.0 +. width1 +. unit *. 3.0;
     let holeY = -. height /. 2.0 +. unit;
     let holeW = width2 +. unit *. 4.0;
     let holeH = height -. unit *. 2.0; */

  [
    /* Block Outline */
    Tea.Svg.path(
      [
        dPath([
          MoveTo(0.0, 0.0),
          LineTo(0.0, -. hh),
          LineTo(20.0, -. hh),
          LineTo(30.0, -. hh +. unit),
          LineTo(50.0, -. hh +. unit),
          LineTo(60.0, -. hh),
          LineTo(right, -. hh),
          LineTo(right, hh),
          LineTo(60.0, hh),
          LineTo(50.0, hh +. unit),
          LineTo(30.0, hh +. unit),
          LineTo(20.0, hh),
          LineTo(0.0, hh),
          Close,
        ]),
        fill(Some(fillColor)),
        stroke(Some(outlineColor)),
        strokeWidth(1.5),
      ],
      [],
    ),
    /* Inner Oval Carve-Out */
    /* pill(holeX, holeY, holeW, holeH, outlineColor), */
  ];
};