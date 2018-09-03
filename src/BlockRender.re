open BlockTypes;

let defaultPadding = 5.;

/* open BlockMeasure; */
let rec renderBadge = (badge: badge): list(Vdom.t('msg)) =>
  renderBadgeHelper(badge, 0.)
and renderBadgeHelper = (badge: badge, x: float): list(Vdom.t('msg)) => {
  let style = List.assoc("motion", BlockStyles.styles);
  let (element, innerBadges) =
    switch (badge) {
    | Hexagon(innerBadges, size) =>
      let (w, h) = size^;
      (BlockShapes.hexagon(w, h, style), innerBadges);
    | Pill(innerBadges, size) =>
      let (w, h) = size^;
      (BlockShapes.hexagon(w, h, style), innerBadges);
    | Text(string, size) =>
      let (w, h) = size^;
      (BlockShapes.hexagon(w, h, style), []);
    };

  let widths =
    innerBadges
    ->Belt.List.map(b => {
        let (w, _) = dimOfBadge(b);
        w +. defaultPadding;
      });
  let cumuWidths = [defaultPadding, ...Utils.cumuSum(widths)];

  let renderedInnerBadges =
    Belt.List.zipBy(innerBadges, cumuWidths, renderBadgeHelper);

  Belt.List.concat(
    [Graphic.translate(x, 0., [element])],
    renderedInnerBadges->Belt.List.flatten,
  );
};