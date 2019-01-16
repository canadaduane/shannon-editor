open BlockM;

module BuiltinList = List;
module List = Belt.List;

let getTagsAndBox = (mtag: tag) =>
  switch (mtag) {
  | Hexagon(childTags, box) => (childTags, box^)
  | Pill(childTags, box) => (childTags, box^)
  | Text(_string, box) => ([], box^)
  };

/* open BlockMeasure; */
let renderBadge = (mtag: tag): list(Vdom.t('msg)) => {
  let style = BuiltinList.assoc("motion", BlockStyles.styles);

  let rec loop = (x: float, mtag: tag): list(Vdom.t('msg)) => {
    let (childTags, box) = getTagsAndBox(mtag);
    /* Js.log3("box", box.width, box.margin.left); */

    let boxes = childTags->List.map(Tag.getBox);
    let widths = boxes->List.map(Box.outerWidth);
    let positions = [x, ...Utils.cumuSum(widths)];

    let addLeftMargin = (pos: float, box: box) => box.margin.left +. pos;
    let positionsPlusMargins: list(float) =
      List.zipBy(positions, boxes, addLeftMargin);
    /* Js.Console.log3(
         "margin",
         box.margin.left,
         switch (mtag) {
         | Pill(_) => "pill"
         | Hexagon(_) => "hexagon"
         | Text(_) => "text"
         },
       ); */

    let renderedInnerBadges =
      loop |> List.zipBy(positionsPlusMargins, childTags);

    let element =
      switch (mtag) {
      | Hexagon(_, _) => BlockShapes.hexagon(box.width, box.height, style)
      | Pill(_, _) => BlockShapes.pill(box.width, box.height, style)
      | Text(_, _) => BlockShapes.pill(10., 10., style)
      };

    List.concat(
      [Graphic.translate(x, 0., [element])],
      renderedInnerBadges->List.flatten,
    );
  };
  loop(0., mtag);
};