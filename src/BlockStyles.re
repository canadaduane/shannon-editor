open TypedSvg.Types;

type blockStyle = {
  fill: color,
  outline: color,
  shadow: color,
  stroke: float,
};

let styles = [
  (
    "motion",
    {
      fill: Color("#4797ff"),
      outline: Color("#4280d7"),
      shadow: Color("#3373cc"),
      stroke: 2.0,
    },
  ),
  (
    "looks",
    {
      fill: Color("#9966ff"),
      outline: Color("#855cd6"),
      shadow: Color("#774dcb"),
      stroke: 2.0,
    },
  ),
  (
    "sounds",
    {
      fill: Color("#cf63cf"),
      outline: Color("#c94fc9"),
      shadow: Color("#a63fa6"),
      stroke: 2.0,
    },
  ),
  (
    "control",
    {
      fill: Color("#ffab19"),
      outline: Color("#ec9c13"),
      shadow: Color("#cf8b17"),
      stroke: 2.0,
    },
  ),
  (
    "events",
    {
      fill: Color("#ffbf00"),
      outline: Color("#e6ac00"),
      shadow: Color("#cc9900"),
      stroke: 2.0,
    },
  ),
  (
    "sensing",
    {
      fill: Color("#5cb1d6"),
      outline: Color("#47a8d1"),
      shadow: Color("#2e8eb8"),
      stroke: 2.0,
    },
  ),
  (
    "pen",
    {
      fill: Color("#0fbd8c"),
      outline: Color("#0da57a"),
      shadow: Color("#0b8e69"),
      stroke: 2.0,
    },
  ),
  (
    "operators",
    {
      fill: Color("#59c059"),
      outline: Color("#46b946"),
      shadow: Color("#389438"),
      stroke: 2.0,
    },
  ),
  (
    "data",
    {
      fill: Color("#ff8c1a"),
      outline: Color("#ff8000"),
      shadow: Color("#db6e00"),
      stroke: 2.0,
    },
  ),
  (
    "more",
    {
      fill: Color("#ff6680"),
      outline: Color("#ff4d6a"),
      shadow: Color("#ff3355"),
      stroke: 2.0,
    },
  ),
];

let default = List.assoc("motion", styles);