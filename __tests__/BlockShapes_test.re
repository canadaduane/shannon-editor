open Jest;
open Expect;
open! Expect.Operators;

open Shapes;

module S = Tea.Svg;
module SA = Tea.Svg.Attributes;

describe("hexagon", () =>
  test("default shape", () => {
    let hexShape = "M0,0 l15,-15 h20 l15,15 l-15,15 h-20 z";
    expect(hexagon(50., 30., BlockStyle.default))
    |> toEqual(
         S.path(
           [
             SA.d(hexShape),
             SA.fill("#4797ff"),
             SA.stroke("#4280d7"),
             SA.strokeWidth("2px"),
           ],
           [],
         ),
       );
  })
);