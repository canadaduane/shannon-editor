open BlockU;

/* Sample Layout (unmeasured) */
let sampleLayout: layout =
  Layout(
    Some(First([Text("start")])),
    [
      Middle(
        [
          Text("if"),
          Hexagon([Pill([Text("x")]), Text("="), Pill([Text("1")])]),
        ],
        [
          Section(
            [Text("else")],
            [
              Middle([Text("move forward"), Pill([Text("10")])], []),
              Middle([Text("move backward"), Pill([Text("10")])], []),
            ],
            None,
          ),
        ],
      ),
    ],
    Some(Last([Text("Exit")])),
  );