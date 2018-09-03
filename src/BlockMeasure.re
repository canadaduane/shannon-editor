open BlockTypes;

let defaultPadding = (5., 5.);

let estimateTextWidth = (text: string): float =>
  float_of_int(String.length(text) * 16);

let getSizeRef = (r: size): (float, float) => r^;

let sumWidthMaxHeight = ((pw, ph), (w1, h1), (w2, h2)) => (
  w1 +. w2 +. pw,
  max(h1, h2) +. ph,
);
let maxWidthSumHeight = ((pw, ph), (w1, h1), (w2, h2)) => (
  max(w1, w2) +. pw,
  h1 +. h2 +. ph,
);

/* Given an unmeasured badge (ubadge), build a measured badge tree */
let rec measureBadge = (ubadge: ubadge): badge =>
  switch (ubadge) {
  | Text(str) =>
    Text(str, ref((estimateTextWidth(str), BlockConfig.defaultTextHeight)))
  | Hexagon([]) => Hexagon([], ref(BlockConfig.defaultBadgeDim))
  | Hexagon(ubadges) =>
    let (badges, sumSize) = measureBadgeList(ubadges);
    Hexagon(badges, ref(sumSize));
  | Pill([]) => Pill([], ref(BlockConfig.defaultBadgeDim))
  | Pill(ubadges) =>
    let (badges, sumSize) = measureBadgeList(ubadges);
    Pill(badges, ref(sumSize));
  }
and measureBadgeList = (ubadges: list(ubadge)): (list(badge), dim) => {
  let badges = ubadges->Belt.List.map(measureBadge);
  let sumSize =
    badges
    ->Belt.List.map(dimOfBadge)
    ->Belt.List.reduce((0., 0.), sumWidthMaxHeight(defaultPadding));
  (badges, sumSize);
};

/* Given an unmeasured blockLast (ublockLast), build a measured blockLast */
let measureBlockLast = (ublock: ublockLast): blockLast =>
  switch (ublock) {
  | BlockLast([]) => BlockLast([], ref(BlockConfig.defaultBlockDim))
  | BlockLast(ubadges) =>
    let (badges, sumSize) = measureBadgeList(ubadges);
    BlockLast(badges, ref(sumSize));
  };

/* Given an unmeasured blockFirst (ublockFirst), build a measured blockFirst */
let measureBlockFirst = (ublock: ublockFirst): blockFirst =>
  switch (ublock) {
  | BlockFirst([]) => BlockFirst([], ref(BlockConfig.defaultBlockDim))
  | BlockFirst(ubadges) =>
    let (badges, sumSize) = measureBadgeList(ubadges);
    BlockFirst(badges, ref(sumSize));
  };

/* Given an unmeasured blockMiddle (ublockMiddle), build a measured blockMiddle */
let rec measureBlockMiddle = (ublock: ublockMiddle): blockMiddle =>
  switch (ublock) {
  | BlockMiddle([], []) =>
    BlockMiddle([], [], ref(BlockConfig.defaultBlockDim))
  | BlockMiddle(ubadges, usections) =>
    let (badges, badgesSumSize) = measureBadgeList(ubadges);
    let (sections, sectionsSumSize) =
      measureBlockMiddleSectionList(usections);
    BlockMiddle(
      badges,
      sections,
      ref(maxWidthSumHeight(defaultPadding, badgesSumSize, sectionsSumSize)),
    );
  }
/* Given an unmeasured blockMiddleSection (ublockMiddleSection), build a measured blockMiddleSection */
and measureBlockMiddleSection =
    (usection: ublockMiddleSection): blockMiddleSection =>
  switch (usection) {
  | BlockMiddleSection([], [], None) =>
    BlockMiddleSection([], [], None, ref(BlockConfig.defaultBlockDim))
  | BlockMiddleSection(ubadges, ublockMiddles, None) =>
    let (badges, badgesSumSize) = measureBadgeList(ubadges);
    let (blockMiddles, middleSumSize) =
      measureBlockMiddleList(ublockMiddles);
    let sumSize =
      maxWidthSumHeight(defaultPadding, badgesSumSize, middleSumSize);
    BlockMiddleSection(badges, blockMiddles, None, ref(sumSize));
  | BlockMiddleSection(ubadges, ublockMiddles, Some(ublockLast)) =>
    let (badges, badgesSumSize) = measureBadgeList(ubadges);
    let (blockMiddles, middleSumSize) =
      measureBlockMiddleList(ublockMiddles);
    let blockLast = measureBlockLast(ublockLast);
    let blockLastSumSize = dimOfBlockLast(blockLast);
    let sumSize =
      maxWidthSumHeight(
        defaultPadding,
        badgesSumSize,
        maxWidthSumHeight(defaultPadding, middleSumSize, blockLastSumSize),
      );
    BlockMiddleSection(badges, blockMiddles, None, ref(sumSize));
  }
and measureBlockMiddleList =
    (ublocks: list(ublockMiddle)): (list(blockMiddle), dim) => {
  let blocks = ublocks->Belt.List.map(measureBlockMiddle);
  let sumSize =
    blocks
    ->Belt.List.map(dimOfBlockMiddle)
    ->Belt.List.reduce((0., 0.), sumWidthMaxHeight(defaultPadding));
  (blocks, sumSize);
}
and measureBlockMiddleSectionList =
    (usections: list(ublockMiddleSection)): (list(blockMiddleSection), dim) => {
  let sections = usections->Belt.List.map(measureBlockMiddleSection);
  let sumSize =
    sections
    ->Belt.List.map(dimOfBlockMiddleSection)
    ->Belt.List.reduce((0., 0.), sumWidthMaxHeight(defaultPadding));
  (sections, sumSize);
};