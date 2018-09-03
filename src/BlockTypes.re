type dim = (float, float);
type size = ref(dim);

/* Measured Abstract Block Components */
type badge =
  | Hexagon(list(badge), size)
  | Pill(list(badge), size)
  | Text(string, size);

type blockLast =
  | BlockLast(list(badge), size);

type blockMiddle =
  | BlockMiddle(list(badge), list(blockMiddleSection), size)
and blockMiddleSection =
  | BlockMiddleSection(
      list(badge),
      list(blockMiddle),
      option(blockLast),
      size,
    );

type blockFirst =
  | BlockFirst(list(badge), size);

type layout =
  | Layout(option(blockFirst), list(blockMiddle), option(blockLast), size);

/* Unmeasured Abstract Block Components */
type ubadge =
  | Hexagon(list(ubadge))
  | Pill(list(ubadge))
  | Text(string);

type ublockLast =
  | BlockLast(list(ubadge));

type ublockMiddle =
  | BlockMiddle(list(ubadge), list(ublockMiddleSection))
and ublockMiddleSection =
  | BlockMiddleSection(
      list(ubadge),
      list(ublockMiddle),
      option(ublockLast),
    );

type ublockFirst =
  | BlockFirst(list(ubadge));

type ulayout =
  | Layout(option(ublockFirst), list(ublockMiddle), option(ublockLast));

/* Sample Layout (unmeasured) */
let sampleLayout: ulayout =
  Layout(
    Some(BlockFirst([Text("start")])),
    [
      BlockMiddle(
        [
          Text("if"),
          Hexagon([Pill([Text("x")]), Text("="), Pill([Text("1")])]),
        ],
        [
          BlockMiddleSection(
            [Text("else")],
            [
              BlockMiddle([Text("move forward"), Pill([Text("10")])], []),
              BlockMiddle(
                [Text("move backward"), Pill([Text("10")])],
                [],
              ),
            ],
            Some(BlockLast([Text("done")])),
          ),
        ],
      ),
    ],
    Some(BlockLast([Text("Exit")])),
  );

let dimOfBadge = (badge: badge): dim => {
  let size =
    switch (badge) {
    | Hexagon(_, size) => size
    | Pill(_, size) => size
    | Text(_, size) => size
    };
  size^;
};

let dimOfBlockLast = (block: blockLast): dim => {
  let size =
    switch (block) {
    | BlockLast(_, size) => size
    };
  size^;
};

let dimOfBlockMiddle = (block: blockMiddle): dim => {
  let size =
    switch (block) {
    | BlockMiddle(_, _, size) => size
    };
  size^;
};

let dimOfBlockMiddleSection = (block: blockMiddleSection): dim => {
  let size =
    switch (block) {
    | BlockMiddleSection(_, _, _, size) => size
    };
  size^;
};

let dimOfBlockFirst = (block: blockFirst): dim => {
  let size =
    switch (block) {
    | BlockFirst(_, size) => size
    };
  size^;
};