open BlockM;
module List = Belt.List;

let getTagsAndBox = (mtag: tag) =>
  switch (mtag) {
  | Hexagon(childTags, box) => (childTags, box^)
  | Pill(childTags, box) => (childTags, box^)
  | Text(_string, box) => ([], box^)
  };

let renderTag = (mtag: tag): list(Vdom.t('msg)) => {
  let style = BlockStyle.getStyle("motion");
  let blankStyle = BlockStyle.getStyle("blank");

  let rec loop = (x: float, mtag: tag): list(Vdom.t('msg)) => {
    let (childTags, box) = getTagsAndBox(mtag);

    let boxes = childTags->List.map(Tag.getBox);
    let widths = boxes->List.map(Box.outerWidth);
    let positions = [x, ...Utils.cumuSum(widths)];

    let addLeftMargin = (pos: float, box: box) => box.margin.left +. pos;
    let positionsPlusMargins: list(float) =
      List.zipBy(positions, boxes, addLeftMargin);

    let renderedChildTags =
      loop |> List.zipBy(positionsPlusMargins, childTags);

    let element =
      switch (mtag) {
      | Hexagon(_, _) => Shapes.hexagon(box.width, box.height, style)
      | Pill(_, _) => Shapes.pill(box.width, box.height, blankStyle)
      | Text(t, _) => Shapes.text(t)
      };

    List.concat(
      [Graphic.translate(x, 0., [element])],
      renderedChildTags->List.flatten,
    );
  };
  loop(0., mtag);
};