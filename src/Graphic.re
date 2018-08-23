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
  TypedSvg.g([transform([Translate(x, y)])], children);