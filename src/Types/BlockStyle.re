open TypedSvg.Types;

let white = Color("#f6f6f6");
let gray = Color("#999999");
let black = Color("#666666");

type blockStyle = {
  fill: color,
  outline: color,
  shadow: color,
  text: color,
  stroke: float,
};
type t = blockStyle;

let blockStyleLookup = [
  (
    "blank",
    {
      fill: white,
      outline: Color("#7f7f7f"),
      shadow: Color("#3373cc"),
      text: black,
      stroke: 1.5,
    },
  ),
  (
    "motion",
    {
      fill: Color("#4797ff"),
      outline: Color("#4280d7"),
      shadow: Color("#3373cc"),
      text: white,
      stroke: 1.5,
    },
  ),
  (
    "looks",
    {
      fill: Color("#9966ff"),
      outline: Color("#855cd6"),
      shadow: Color("#774dcb"),
      text: white,
      stroke: 1.5,
    },
  ),
  (
    "sounds",
    {
      fill: Color("#cf63cf"),
      outline: Color("#c94fc9"),
      shadow: Color("#a63fa6"),
      text: white,
      stroke: 1.5,
    },
  ),
  (
    "control",
    {
      fill: Color("#ffab19"),
      outline: Color("#ec9c13"),
      shadow: Color("#cf8b17"),
      text: white,
      stroke: 1.5,
    },
  ),
  (
    "events",
    {
      fill: Color("#ffbf00"),
      outline: Color("#e6ac00"),
      shadow: Color("#cc9900"),
      text: white,
      stroke: 1.5,
    },
  ),
  (
    "sensing",
    {
      fill: Color("#5cb1d6"),
      outline: Color("#47a8d1"),
      shadow: Color("#2e8eb8"),
      text: white,
      stroke: 1.5,
    },
  ),
  (
    "pen",
    {
      fill: Color("#0fbd8c"),
      outline: Color("#0da57a"),
      shadow: Color("#0b8e69"),
      text: white,
      stroke: 1.5,
    },
  ),
  (
    "operators",
    {
      fill: Color("#59c059"),
      outline: Color("#46b946"),
      shadow: Color("#389438"),
      text: white,
      stroke: 1.5,
    },
  ),
  (
    "data",
    {
      fill: Color("#ff8c1a"),
      outline: Color("#ff8000"),
      shadow: Color("#db6e00"),
      text: white,
      stroke: 1.5,
    },
  ),
  (
    "more",
    {
      fill: Color("#ff6680"),
      outline: Color("#ff4d6a"),
      shadow: Color("#ff3355"),
      text: white,
      stroke: 1.5,
    },
  ),
];

let getStyle = (name: string) => List.assoc(name, blockStyleLookup);

let default = getStyle("motion");