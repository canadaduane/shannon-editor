
type shape =
  | Text(string)
  | Hexagon(list(shape))
  | Pill(list(shape));

type firstBlock = {
  headline: list(shape),
  body: list(middleBlock),
  tail: option(lastBlock),
}
and middleBlock = {
  headline: list(shape),
  sections: list(section),
}
and lastBlock = {headline: list(shape)}
and section = {
  body: list(middleBlock),
  tail: option(lastBlock),
  footline: list(shape),
};

type layout = (option(firstBlock), list(middleBlock), option(lastBlock));

let sampleLayout: layout = (
  Some({headline: [Text("start")], body: [], tail: None}),
  [
    {
      headline: [
        Text("if"),
        Hexagon([Pill([Text("x")]), Text("="), Pill([Text("1")])]),
      ],
      sections: [
        {
          body: [
            {
              headline: [Text("move forward"), Pill([Text("10")])],
              sections: [],
            },
          ],
          tail: Some({headline: [Text("done")]}),
          footline: [Text("else")],
        },
        {
          body: [
            {
              headline: [Text("move backward"), Pill([Text("10")])],
              sections: [],
            },
          ],
          tail: None,
          footline: [],
        },
      ],
    },
  ],
  Some({headline: [Text("Exit")]}),
);