open Jest;
open Expect;
open! Expect.Operators;

open BlockTypes;
open BlockMeasure;

module C = BlockConfig;

describe("measureBadge", () => {
  test("one hexagon", () => {
    let ubadge: ubadge = Hexagon([]);
    let badge: badge = measureBadge(ubadge);
    let expectedBadge: badge = Hexagon([], ref(C.defaultBadgeBox));
    expect(badge) |> toEqual(expectedBadge);
  });

  test("two hexagons in a hexagon", () => {
    let ubadge: ubadge = Hexagon([Hexagon([]), Hexagon([])]);
    let badge: badge = measureBadge(ubadge);
    let expectedBadge: badge =
      Hexagon(
        [
          Hexagon([], ref(C.defaultBadgeBox)),
          Hexagon([], ref(C.defaultBadgeBox)),
        ],
        ref(
          C.mkBox(
            C.defaultBadgeWidth *. 2. +. C.defaultPadWidth *. 4.,
            C.defaultBadgeHeight +. C.defaultPadHeight *. 2.,
          ),
        ),
      );
    expect(badge) |> toEqual(expectedBadge);
  });
});