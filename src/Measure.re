let estimateTextWidth = (text: string): float =>
  float_of_int(String.length(text) * 16);

let mkBox =
    (~margin=BlockConfig.defaultMargin, width: float, height: float): Box.t => {
  width,
  height,
  margin,
};
let mkBoxFromDim = (~margin=BlockConfig.defaultMargin, dim: Dim.t): Box.t =>
  mkBox(~margin, dim.width, dim.height);

let defaultBlockBox =
  mkBox(BlockConfig.defaultBlockWidth, BlockConfig.defaultBlockHeight);
let defaultTagBox =
  mkBox(BlockConfig.defaultTagWidth, BlockConfig.defaultTagHeight);

type tagType =
  | Hex
  | Pil
  | Txt;

type tagPosition =
  | Only
  | First
  | Middle
  | Last;

let adjustPadding =
    (parent: tagType, child: tagType, position: tagPosition): Margin.t => {
  let u = BlockConfig.unit;
  let (left, right) =
    switch (parent, child, position) {
    | (Hex, Hex, Only) => (u, u)
    | (Hex, Pil, Only) => (u, u)
    | (Hex, Txt, Only) => (u, u)
    | (Hex, Hex, First) => (u, u)
    | (Hex, Pil, First) => (u, u)
    | (Hex, Txt, First) => (u, u)
    | (Hex, Hex, Middle) => (u, u)
    | (Hex, Pil, Middle) => (u, u)
    | (Hex, Txt, Middle) => (u, u)
    | (Hex, Hex, Last) => (u, u)
    | (Hex, Pil, Last) => (u, u)
    | (Hex, Txt, Last) => (u, u)
    | (Pil, Hex, Only) => (u, u)
    | (Pil, Pil, Only) => (u, u)
    | (Pil, Txt, Only) => (u, u)
    | (Pil, Hex, First) => (u, u)
    | (Pil, Pil, First) => (u, u)
    | (Pil, Txt, First) => (u, u)
    | (Pil, Hex, Middle) => (u, u)
    | (Pil, Pil, Middle) => (u, u)
    | (Pil, Txt, Middle) => (u, u)
    | (Pil, Hex, Last) => (u, u)
    | (Pil, Pil, Last) => (u, u)
    | (Pil, Txt, Last) => (u, u)
    | (Txt, _, _) => (u, u)
    };
  let margin = {
    ...BlockConfig.defaultMargin,
    left: BlockConfig.defaultMargin.left,
  };
  /* Js.Console.log2("margin", margin); */
  margin;
};

module Tag = {
  /* Given an unmeasured badge, measure it & return a measured badge */
  let rec measure = (tag: BlockU.tag): BlockM.tag =>
    switch (tag) {
    | Text(str) =>
      let width = estimateTextWidth(str);
      let height = BlockConfig.defaultTextHeight;
      Text(str, ref(mkBox(width, height)));
    | Hexagon([]) => Hexagon([], ref(defaultTagBox))
    | Hexagon(tags) =>
      let (mtags, dim) = measureList(tags);
      /* let adjustedBadges = adjustPadding(Hex, badges); */
      Hexagon(mtags, ref(mkBoxFromDim(dim)));
    | Pill([]) => Pill([], ref(defaultTagBox))
    | Pill(tags) =>
      let (mtags, dim) = measureList(tags);
      Pill(mtags, ref(mkBoxFromDim(dim)));
    }
  and measureList = (tags: list(BlockU.tag)): (list(BlockM.tag), Dim.t) => {
    let mtags = tags->Belt.List.map(measure);
    let combinedDimensions =
      mtags
      ->Belt.List.map(BlockM.Tag.getDim)
      ->Belt.List.reduce(Dim.zero, Dim.sumWidthMaxHeight);
    (mtags, combinedDimensions);
  };
};

module First = {
  /* Given an unmeasured blockFirst (blockFirst), build a measured mblockFirst */
  let measure = (first: BlockU.first): BlockM.first =>
    switch (first) {
    | First([]) => First([], ref(defaultBlockBox))
    | First(tags) =>
      let (tags, dim) = Tag.measureList(tags);
      First(tags, ref(mkBoxFromDim(dim)));
    };
};

module Last = {
  /* Given an unmeasured blockLast (blockLast), build a measured blockLast */
  let measure = (last: BlockU.last): BlockM.last =>
    switch (last) {
    | Last([]) => Last([], ref(defaultBlockBox))
    | Last(tags) =>
      let (mtags, dim) = Tag.measureList(tags);
      Last(mtags, ref(mkBoxFromDim(dim)));
    };
};

module Middle = {
  /* Given an unmeasured blockMiddle (blockMiddle), build a measured blockMiddle */
  let rec measure = (middle: BlockU.middle): BlockM.middle =>
    switch (middle) {
    | Middle([], []) => Middle([], [], ref(defaultBlockBox))
    | Middle(tags, sections) =>
      let (mtags, mtagsDim) = Tag.measureList(tags);
      let (msections, msectionsDim) = measureSectionList(sections);
      let dim = Dim.maxWidthSumHeight(mtagsDim, msectionsDim);
      Middle(mtags, msections, ref(mkBoxFromDim(mtagsDim)));
    }
  /* Given an unmeasured blockMiddleSection (blockMiddleSection), build a measured blockMiddleSection */
  and measureSection = (usection: BlockU.section): BlockM.section =>
    switch (usection) {
    | Section([], [], None) => Section([], [], None, ref(defaultBlockBox))
    | Section(tags, middles, None) =>
      let (mtags, mtagsDim) = Tag.measureList(tags);
      let (mmiddles, mmiddlesDim) = measureList(middles);
      let dim = Dim.maxWidthSumHeight(mtagsDim, mmiddlesDim);
      Section(mtags, mmiddles, None, ref(mkBoxFromDim(dim)));
    | Section(tags, middles, Some(last)) =>
      let (mtags, mtagsDim) = Tag.measureList(tags);
      let (mmiddles, mmiddlesDim) = measureList(middles);
      let mlast = Last.measure(last);
      let mlastDim = BlockM.Last.getDim(mlast);
      let dim =
        Dim.maxWidthSumHeight(
          mtagsDim,
          Dim.maxWidthSumHeight(mmiddlesDim, mlastDim),
        );
      Section(mtags, mmiddles, None, ref(mkBoxFromDim(dim)));
    }
  and measureList =
      (middles: list(BlockU.middle)): (list(BlockM.middle), Dim.t) => {
    let mmiddles = middles->Belt.List.map(measure);
    let dim =
      mmiddles
      ->Belt.List.map(BlockM.Middle.getDim)
      ->Belt.List.reduce(Dim.zero, Dim.sumWidthMaxHeight);
    (mmiddles, dim);
  }
  and measureSectionList =
      (sections: list(BlockU.section)): (list(BlockM.section), Dim.t) => {
    let msections = sections->Belt.List.map(measureSection);
    let dim =
      msections
      ->Belt.List.map(BlockM.Middle.getSectionDim)
      ->Belt.List.reduce(Dim.zero, Dim.sumWidthMaxHeight);
    (msections, dim);
  };
};