open BlockTypes;

module Float = Utils.Float;

let estimateTextWidth = (text: string): float =>
  float_of_int(String.length(text) * 16);

let sumWidthMaxHeight = (dim1: dim, dim2: dim) => {
  width: Float.(dim1.width + dim2.width),
  height: max(dim1.height, dim2.height),
};

let maxWidthSumHeight = (dim1: dim, dim2: dim) => {
  width: max(dim1.width, dim2.width),
  height: Float.(dim1.height + dim2.height),
};

let mkBoxFromDim = (dim: dim): box => {
  width: dim.width,
  height: dim.height,
  padding: BlockConfig.defaultPadding,
};

/* Given an unmeasured badge (ubadge), build a measured badge tree */
let rec measureBadge = (ubadge: ubadge): badge =>
  switch (ubadge) {
  | Text(str) =>
    Text(
      str,
      ref(
        BlockConfig.mkBox(
          estimateTextWidth(str),
          BlockConfig.defaultTextHeight,
        ),
      ),
    )
  | Hexagon([]) => Hexagon([], ref(BlockConfig.defaultBadgeBox))
  | Hexagon(ubadges) =>
    let (badges, dim) = measureBadgeList(ubadges);
    Hexagon(badges, ref(mkBoxFromDim(dim)));
  | Pill([]) => Pill([], ref(BlockConfig.defaultBadgeBox))
  | Pill(ubadges) =>
    let (badges, dim) = measureBadgeList(ubadges);
    Pill(badges, ref(mkBoxFromDim(dim)));
  }
and measureBadgeList = (ubadges: list(ubadge)): (list(badge), dim) => {
  let badges = ubadges->Belt.List.map(measureBadge);
  let dim =
    badges
    ->Belt.List.map(dimOfBadge)
    ->Belt.List.reduce(BlockTypes.zeroDim, sumWidthMaxHeight);
  (badges, dim);
};

/* Given an unmeasured blockLast (ublockLast), build a measured blockLast */
let measureBlockLast = (ublock: ublockLast): blockLast =>
  switch (ublock) {
  | BlockLast([]) => BlockLast([], ref(BlockConfig.defaultBlockBox))
  | BlockLast(ubadges) =>
    let (badges, dim) = measureBadgeList(ubadges);
    BlockLast(badges, ref(mkBoxFromDim(dim)));
  };

/* Given an unmeasured blockFirst (ublockFirst), build a measured blockFirst */
let measureBlockFirst = (ublock: ublockFirst): blockFirst =>
  switch (ublock) {
  | BlockFirst([]) => BlockFirst([], ref(BlockConfig.defaultBlockBox))
  | BlockFirst(ubadges) =>
    let (badges, dim) = measureBadgeList(ubadges);
    BlockFirst(badges, ref(mkBoxFromDim(dim)));
  };

/* Given an unmeasured blockMiddle (ublockMiddle), build a measured blockMiddle */
let rec measureBlockMiddle = (ublock: ublockMiddle): blockMiddle =>
  switch (ublock) {
  | BlockMiddle([], []) =>
    BlockMiddle([], [], ref(BlockConfig.defaultBlockBox))
  | BlockMiddle(ubadges, usections) =>
    let (badges, badgesDim) = measureBadgeList(ubadges);
    let (sections, sectionsDim) = measureBlockMiddleSectionList(usections);
    let dim = maxWidthSumHeight(badgesDim, sectionsDim);
    BlockMiddle(badges, sections, ref(mkBoxFromDim(dim)));
  }
/* Given an unmeasured blockMiddleSection (ublockMiddleSection), build a measured blockMiddleSection */
and measureBlockMiddleSection =
    (usection: ublockMiddleSection): blockMiddleSection =>
  switch (usection) {
  | BlockMiddleSection([], [], None) =>
    BlockMiddleSection([], [], None, ref(BlockConfig.defaultBlockBox))
  | BlockMiddleSection(ubadges, ublockMiddles, None) =>
    let (badges, badgesDim) = measureBadgeList(ubadges);
    let (blockMiddles, blockMiddlesDim) =
      measureBlockMiddleList(ublockMiddles);
    let dim = maxWidthSumHeight(badgesDim, blockMiddlesDim);
    BlockMiddleSection(badges, blockMiddles, None, ref(mkBoxFromDim(dim)));
  | BlockMiddleSection(ubadges, ublockMiddles, Some(ublockLast)) =>
    let (badges, badgesDim) = measureBadgeList(ubadges);
    let (blockMiddles, blockMiddlesDim) =
      measureBlockMiddleList(ublockMiddles);
    let blockLast = measureBlockLast(ublockLast);
    let blockLastDim = dimOfBlockLast(blockLast);
    let dim =
      maxWidthSumHeight(
        badgesDim,
        maxWidthSumHeight(blockMiddlesDim, blockLastDim),
      );
    BlockMiddleSection(badges, blockMiddles, None, ref(mkBoxFromDim(dim)));
  }
and measureBlockMiddleList =
    (ublocks: list(ublockMiddle)): (list(blockMiddle), dim) => {
  let blocks = ublocks->Belt.List.map(measureBlockMiddle);
  let dim =
    blocks
    ->Belt.List.map(dimOfBlockMiddle)
    ->Belt.List.reduce(zeroDim, sumWidthMaxHeight);
  (blocks, dim);
}
and measureBlockMiddleSectionList =
    (usections: list(ublockMiddleSection)): (list(blockMiddleSection), dim) => {
  let sections = usections->Belt.List.map(measureBlockMiddleSection);
  let dim =
    sections
    ->Belt.List.map(dimOfBlockMiddleSection)
    ->Belt.List.reduce(zeroDim, sumWidthMaxHeight);
  (sections, dim);
};