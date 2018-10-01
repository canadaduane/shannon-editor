open BlockTypes;

module BuiltinList = List;
module List = Belt.List;

let getBadgesAndBox = (badge: badge) =>
  switch (badge) {
  | Hexagon(innerBadges, box) => (innerBadges, box^)
  | Pill(innerBadges, box) => (innerBadges, box^)
  | Text(_string, box) => ([], box^)
  };

/* open BlockMeasure; */
let renderBadge = (badge: badge): list(Vdom.t('msg)) => {
  let style = BuiltinList.assoc("motion", BlockStyles.styles);

  let rec loop = (x: float, badge: badge): list(Vdom.t('msg)) => {
    let (innerBadges, box) = getBadgesAndBox(badge);

    let addLeftPadding = (pos, box) => box.padding.left +. pos;
    let boxes = innerBadges->List.map(boxOfBadge);
    let widths = boxes->List.map(boxWidthPadded);
    let positions =
      addLeftPadding |> List.zipBy([x, ...Utils.cumuSum(widths)], boxes);

    let renderedInnerBadges = loop |> List.zipBy(positions, innerBadges);

    let element =
      switch (badge) {
      | Hexagon(_, _) => BlockShapes.hexagon(box.width, box.height, style)
      | Pill(_, _) => BlockShapes.pill(box.width, box.height, style)
      | Text(_, _) => BlockShapes.pill(10., 10., style)
      };

    List.concat(
      [Graphic.translate(x, 0., [element])],
      renderedInnerBadges->List.flatten,
    );
  };
  loop(0., badge);
};