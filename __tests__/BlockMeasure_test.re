open Jest;
open Expect;
open! Expect.Operators;

open Measure;

module C = BlockConfig;

let defaultTagBox: Box.t = {
  width: 20.,
  height: 20.,
  margin: {
    top: C.unit,
    right: C.unit,
    bottom: C.unit,
    left: C.unit,
  },
};

describe("measuretag", () => {
  test("one hexagon", () => {
    let tag: BlockU.tag = Hexagon([]);
    let tag: BlockM.tag = Tag.measure(tag);
    let expectedtag: BlockM.tag = Hexagon([], ref(defaultTagBox));
    expect(tag) |> toEqual(expectedtag);
  });

  test("two hexagons in a hexagon", () => {
    let tag: BlockU.tag = Hexagon([Hexagon([]), Hexagon([])]);
    let tag: BlockM.tag = Tag.measure(tag);
    let expectedBox: Box.t = {
      width: C.defaultTagWidth *. 2. +. C.defaultMarginLeftRight *. 4.,
      height: C.defaultTagHeight +. C.defaultMarginTopBottom *. 2.,
      margin: defaultTagBox.margin,
    };
    let expectedTag: BlockM.tag =
      Hexagon(
        [
          Hexagon([], ref(defaultTagBox)),
          Hexagon([], ref(defaultTagBox)),
        ],
        ref(expectedBox),
      );
    expect(tag) |> toEqual(expectedTag);
  });
});