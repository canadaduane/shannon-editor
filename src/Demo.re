open Tea.App;

open Tea.Html;

/* Global Style Example */
let bgColor = Css.rgb(255, 255, 255);
Css.(
  global(
    "body",
    [padding(px(0)), margin(px(0)), backgroundColor(bgColor)],
  )
);

/* Styles Definition Example */
module Styles = {
  open Css;
  let header =
    Css.style([
      padding(px(20)),
      margin(px(0)),
      backgroundColor(black),
      textAlign(center),
    ]);
  let headline = Css.style([margin(px(0)), color(rgb(230, 230, 230))]);
  let container =
    Css.style([
      display(flexBox),
      justifyContent(center),
      backgroundColor(bgColor),
      margin(px(20)),
      border(px(2), `solid, rgb(100, 100, 100)),
    ]);
};

let tagText = Measure.Tag.measure(BlockU.Text("a tag"));
let tagPill = Measure.Tag.measure(BlockU.Pill([]));
let tagHexagon = Measure.Tag.measure(BlockU.Hexagon([]));
let tagRecurse1 =
  Measure.Tag.measure(
    BlockU.Hexagon([BlockU.Pill([]), BlockU.Hexagon([])]),
  );

/* let () = [%bs.raw {| console.log("badge1", badge1) |}]; */
/* let () = Js.log2("badge1", badge1); */

let view = _model =>
  div(
    [],
    [
      header(
        [class'(Styles.header)],
        [h1([class'(Styles.headline)], [text("Shannon Editor")])],
      ),
      div(
        [class'(Styles.container)],
        [
          Graphic.svgArea(
            800.,
            600.,
            [
              Graphic.translate(50., 50., BlockRender.renderBadge(tagText)),
              Graphic.translate(50., 100., BlockRender.renderBadge(tagPill)),
              Graphic.translate(
                50.,
                150.,
                BlockRender.renderBadge(tagHexagon),
              ),
              Graphic.translate(
                50.,
                200.,
                BlockRender.renderBadge(tagRecurse1),
              ),
            ],
          ),
        ],
      ),
    ],
  );

let update = (_i: int, _j: int) => 0;
let main = beginnerProgram({model: 0, update, view});