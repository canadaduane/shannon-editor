open Tea.App;

open Tea.Html;

module List = Belt.List;

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

let tagMeasure = Measure.Tag.measure;
open BlockU;
let demoTags = [
  tagMeasure(Text("a text tag")),
  tagMeasure(Pill([])),
  tagMeasure(Hexagon([])),
  tagMeasure(Hexagon([Text("testing length of tag")])),
  tagMeasure(Hexagon([Pill([])])),
  tagMeasure(Hexagon([Hexagon([])])),
  tagMeasure(Pill([Text("tag")])),
  tagMeasure(Pill([Pill([])])),
  tagMeasure(Pill([Hexagon([])])),
  tagMeasure(Hexagon([Pill([]), Hexagon([]), Pill([])])),
  tagMeasure(Hexagon([Hexagon([]), Pill([]), Hexagon([])])),
  tagMeasure(
    Hexagon([Pill([]), Text("is"), Hexagon([]), Text("ok"), Pill([])]),
  ),
];

let demoBlocks = [];

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
            4000.,
            List.flatten([
              List.mapWithIndex(demoTags, (i, tag) =>
                Graphic.translate(
                  50.,
                  float_of_int(i + 1) *. 65.,
                  Render.renderTag(tag),
                )
              ),
              List.mapWithIndex(demoBlocks, (i, tag) =>
                Graphic.translate(
                  50.,
                  float_of_int(i + 2 + List.length(demoTags)) *. 65.,
                  Render.renderTag(tag),
                )
              ),
            ]),
          ),
        ],
      ),
    ],
  );

let update = (_i: int, _j: int) => 0;
let main = beginnerProgram({model: 0, update, view});