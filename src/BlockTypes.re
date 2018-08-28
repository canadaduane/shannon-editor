/* A "shape" is a thing that can be visually rendered */
type shape =
  | Text(string)
  | Hexagon(list(shape))
  | Pill(list(shape));
/* firstBlock, middleBlock, and lastBlock are generic snap-together blocks that can be visually rendered */
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
/* A section is used by "middleBlock" to keep track of the attributes of its
   "mouths" (e.g. for if/else blocks) */
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
  | MText(dim, string)
  | MHexagon(dim, list(measuredShape))
  | MPill(dim, list(measuredShape));

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
    headline: ((50., 20.), [MText((50., 20.), "start")]),
    body: ((0., 0.), []),
    tail: ((0., 0.), None),
  }),
  [
    {
      headline: (
        (50., 20.),
        [
          MText((20., 20.), "if"),
          MHexagon(
            (30., 20.),
            [
              MPill((10., 20.), [MText((10., 20.), "x")]),
              MText((10., 20.), "="),
              MPill((10., 20.), [MText((10., 20.), "1")]),
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
                      MText((120., 20.), "move forward"),
                      MPill((20., 20.), [MText((20., 20.), "10")]),
                    ],
                  ),
                  sections: ((0., 0.), []),
                },
              ],
            ),
            tail: (
              (40., 20.),
              Some({
                headline: ((40., 20.), [MText((40., 20.), "done")]),
              }),
            ),
            footline: ((40., 20.), [MText((40., 20.), "else")]),
          },
          {
            body: (
              (170., 20.),
              [
                {
                  headline: (
                    (170., 20.),
                    [
                      MText((150., 20.), "move backward"),
                      MPill((20., 20.), [MText((20., 20.), "10")]),
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
  Some({headline: ((40., 20.), [MText((40., 20.), "Exit")])}),
);

/* BasicShape.startBlock()
   BasicShape.block(w, headingHeight, mouths: list(mouth), style) */