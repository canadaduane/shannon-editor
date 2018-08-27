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

type dim = (float, float);

type measuredShape =
  | Text(dim, string)
  | Hexagon(dim, list(measuredShape))
  | Pill(dim, list(measuredShape));

type measuredFirstBlock = {
  headline: (dim, list(measuredShape)),
  body: (dim, list(measuredMiddleBlock)),
  tail: (dim, option(measuredLastBlock)),
}
and measuredMiddleBlock = {
  headline: (dim, list(measuredShape)),
  sections: (dim, list(measuredSection)),
}
and measuredLastBlock = {headline: (dim, list(measuredShape))}
and measuredSection = {
  body: (dim, list(measuredMiddleBlock)),
  tail: (dim, option(measuredLastBlock)),
  footline: (dim, list(measuredShape)),
};

type measuredLayout = (
  option(measuredFirstBlock),
  list(measuredMiddleBlock),
  option(measuredLastBlock),
);

let sampleMeasuredLayout: measuredLayout = (
  Some({
    headline: ((50., 20.), [Text((50., 20.), "start")]),
    body: ((0., 0.), []),
    tail: ((0., 0.), None),
  }),
  [
    {
      headline: (
        (50., 20.),
        [
          Text((20., 20.), "if"),
          Hexagon(
            (30., 20.),
            [
              Pill((10., 20.), [Text((10., 20.), "x")]),
              Text((10., 20.), "="),
              Pill((10., 20.), [Text((10., 20.), "1")]),
            ],
          ),
        ],
      ),
      sections: (
        (170., 100.),
        [
          {
            body: (
              (140., 60.),
              [
                {
                  headline: (
                    (140., 20.),
                    [
                      Text((120., 20.), "move forward"),
                      Pill((20., 20.), [Text((20., 20.), "10")]),
                    ],
                  ),
                  sections: ((0., 0.), []),
                },
              ],
            ),
            tail: (
              (40., 20.),
              Some({headline: ((40., 20.), [Text((40., 20.), "done")])}),
            ),
            footline: ((40., 20.), [Text((40., 20.), "else")]),
          },
          {
            body: (
              (170., 20.),
              [
                {
                  headline: (
                    (170., 20.),
                    [
                      Text((150., 20.), "move backward"),
                      Pill((20., 20.), [Text((20., 20.), "10")]),
                    ],
                  ),
                  sections: ((0., 0.), []),
                },
              ],
            ),
            tail: ((0., 0.), None),
            footline: ((0., 0.), []),
          },
        ],
      ),
    },
  ],
  Some({headline: ((40., 20.), [Text((40., 20.), "Exit")])}),
);

/* BasicShape.startBlock()
   BasicShape.block(w, headingHeight, mouths: list(mouth), style) */