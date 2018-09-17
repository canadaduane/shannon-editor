type padding = {
  top: float,
  right: float,
  bottom: float,
  left: float,
};

let zeroPadding = {top: 0., right: 0., bottom: 0., left: 0.};
let plusPadding = (p1: padding, p2: padding) => {
  top: p1.top +. p2.top,
  right: p1.right +. p2.right,
  bottom: p1.bottom +. p2.bottom,
  left: p1.left +. p2.left,
};

type dim = {
  width: float,
  height: float,
};

let zeroDim = {width: 0., height: 0.};

type box = {
  width: float,
  height: float,
  padding /* padding outside the box */
};

let zeroBox = {width: 0., height: 0., padding: zeroPadding};
let boxWidthPadded = box => box.padding.left +. box.width +. box.padding.right;
let boxHeightPadded = box =>
  box.padding.top +. box.height +. box.padding.bottom;

/* Measured Abstract Block Components */
type badge =
  | Hexagon(list(badge), ref(box))
  | Pill(list(badge), ref(box))
  | Text(string, ref(box));

type blockLast =
  | BlockLast(list(badge), ref(box));

type blockMiddle =
  | BlockMiddle(list(badge), list(blockMiddleSection), ref(box))
and blockMiddleSection =
  | BlockMiddleSection(
      list(badge),
      list(blockMiddle),
      option(blockLast),
      ref(box),
    );

type blockFirst =
  | BlockFirst(list(badge), ref(box));

type layout =
  | Layout(
      option(blockFirst),
      list(blockMiddle),
      option(blockLast),
      ref(box),
    );

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

let dimOfBox = (box: box): dim => {width: box.width, height: box.height};

let boxOfBadge = (badge: badge): box => {
  let box =
    switch (badge) {
    | Hexagon(_, box) => box
    | Pill(_, box) => box
    | Text(_, box) => box
    };
  box^;
};

let dimOfBadge = (badge: badge): dim => {
  let box = boxOfBadge(badge);
  {width: boxWidthPadded(box), height: boxHeightPadded(box)};
};

let innerBadgesOfBadge = (badge: badge): list(badge) =>
  switch (badge) {
  | Hexagon(innerBadges, _) => innerBadges
  | Pill(innerBadges, _) => innerBadges
  | Text(_, _) => []
  };

let boxOfBlockLast = (block: blockLast): box => {
  let box =
    switch (block) {
    | BlockLast(_, box) => box
    };
  box^;
};

let dimOfBlockLast = (block: blockLast): dim =>
  block->boxOfBlockLast->dimOfBox;

let boxOfBlockMiddle = (block: blockMiddle): box => {
  let box =
    switch (block) {
    | BlockMiddle(_, _, box) => box
    };
  box^;
};

let dimOfBlockMiddle = (block: blockMiddle): dim =>
  block->boxOfBlockMiddle->dimOfBox;

let boxOfBlockMiddleSection = (block: blockMiddleSection): box => {
  let box =
    switch (block) {
    | BlockMiddleSection(_, _, _, box) => box
    };
  box^;
};

let dimOfBlockMiddleSection = (block: blockMiddleSection): dim =>
  block->boxOfBlockMiddleSection->dimOfBox;

let boxOfBlockFirst = (block: blockFirst): box => {
  let box =
    switch (block) {
    | BlockFirst(_, box) => box
    };
  box^;
};