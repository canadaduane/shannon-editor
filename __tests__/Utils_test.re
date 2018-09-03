open Jest;
open Expect;
open! Expect.Operators;

open Utils;

describe("cumuSum", () => {
  test("empty list", () =>
    expect(cumuSum([])) |> toEqual([])
  );
  test("simple list", () =>
    expect(cumuSum([1., 2., 3., 4.])) |> toEqual([1., 3., 6., 10.])
  );
});