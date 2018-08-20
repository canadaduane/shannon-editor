type point = (float, float);

type command =
  | MoveTo(float, float)
  | MoveToP(point)
  | MoveToRel(point)
  | LineTo(float, float)
  | LineToP(point)
  | LineToRel(point)
  | HorizontalTo(float)
  | HorizontalToRel(float)
  | VerticalTo(float)
  | VerticalToRel(float)
  | CurveTo(point, point, point)
  | CurveToRel(point, point, point)
  | ShortCurveTo(point, point)
  | ShortCurveToRel(point, point)
  | QuadCurveTo(point, point)
  | QuadCurveToRel(point, point)
  | ShortQuadCurveTo(float, float)
  | ShortQuadCurveToP(point)
  | ShortQuadCurveToRel(point)
  | ArcTo(point, float, bool, bool, point)
  | ArcToRel(point, float, bool, bool, point)
  | Close;

type path = list(command);

let commandToString = (part: command) =>
  switch (part) {
  | MoveTo(x, y) => {j|M$(x),$(y)|j}
  | MoveToP((x, y)) => {j|M$(x),$(y)|j}
  | MoveToRel((x, y)) => {j|m$(x),$(y)|j}

  | LineTo(x, y) => {j|L$(x),$(y)|j}
  | LineToP((x, y)) => {j|L$(x),$(y)|j}
  | LineToRel((x, y)) => {j|l$(x),$(y)|j}

  | HorizontalTo(x) => {j|H$(x)|j}
  | HorizontalToRel(x) => {j|h$(x)|j}

  | VerticalTo(x) => {j|V$(x)|j}
  | VerticalToRel(x) => {j|v$(x)|j}

  | CurveTo((x1, y1), (x2, y2), (x, y)) => {j|C$(x1),$(y1) $(x2),$(y2) $(x),$(y)|j}
  | CurveToRel((x1, y1), (x2, y2), (x, y)) => {j|c$(x1),$(y1) $(x2),$(y2) $(x),$(y)|j}

  | ShortCurveTo((x2, y2), (x, y)) => {j|S$(x2),$(y2) $(x),$(y)|j}
  | ShortCurveToRel((x2, y2), (x, y)) => {j|s$(x2),$(y2) $(x),$(y)|j}

  | QuadCurveTo((x1, y1), (x, y)) => {j|Q$(x1),$(y1) $(x),$(y)|j}
  | QuadCurveToRel((x1, y1), (x, y)) => {j|q$(x1),$(y1) $(x),$(y)|j}

  | ShortQuadCurveTo(x, y) => {j|T$(x),$(y)|j}
  | ShortQuadCurveToP((x, y)) => {j|T$(x),$(y)|j}
  | ShortQuadCurveToRel((x, y)) => {j|t$(x),$(y)|j}

  | ArcTo((rx, ry), xAxisRotation, largeArc, sweep, (x, y)) =>
    let largeArcValue = if (largeArc) {1} else {0};
    let sweepValue = if (sweep) {1} else {0};
    {j|A$(rx),$(ry) $(xAxisRotation) $(largeArcValue),$(sweepValue) $(x),$(y)|j};
  | ArcToRel((rx, ry), xAxisRotation, largeArc, sweep, (x, y)) =>
    let largeArcValue = if (largeArc) {1} else {0};
    let sweepValue = if (sweep) {1} else {0};
    {j|a$(rx),$(ry) $(xAxisRotation) $(largeArcValue),$(sweepValue) $(x),$(y)|j};
  | Close => "z"
  };

let pathToString = (path: path) => {
  let pathStrs = Belt.List.map(path, commandToString);
  Js.Array.joinWith(" ", Belt.List.toArray(pathStrs));
};

/* For example of rounded path function, see http://plnkr.co/edit/kGnGGyoOCKil02k04snu?p=info */