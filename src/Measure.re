module List = Belt.List;

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

module Tag = {
  type tagType =
    | Hex
    | Pil
    | Txt;

  type tagPosition =
    | Only
    | First
    | Middle
    | Last;

  let tag2tagType = (tag: BlockU.tag): tagType =>
    switch (tag) {
    | Text(_) => Txt
    | Pill(_) => Pil
    | Hexagon(_) => Hex
    };

  /* Child tags need custom margins, depending on their shape and what surrounds them. */
  let computeVisuallyAppealingMarginDelta =
      (parent: tagType, child: tagType, childPosition: tagPosition): Margin.t => {
    let u = BlockConfig.unit;
    let (left, right) =
      switch (parent, child, childPosition) {
      | (Hex, Txt, Only) => (u *. 2., u *. 2.)
      | (Hex, Pil, Only) => (u *. 2.5, u *. 2.5)
      | (Hex, Hex, Only) => (u *. 1.5, u *. 1.5)
      | (Hex, Pil, First) => (u *. 3., u)
      | (Hex, Pil, First) => (u *. 3., 0.)
      | (Hex, Pil, Last) => (0., u *. 2.5)
      | (Hex, Hex, First) => (u *. 1.5, u)
      | (Hex, Hex, Last) => (0., u *. 1.5)
      | (Pil, Txt, First) => (u *. 2., 0.)
      | (_, _, Middle) => (0., u)
      | (_, _, _) => (u, u)
      };
    {top: 0., bottom: 0., left, right};
  };

  let idx2tagPosition = (i, total) =>
    switch (i, total) {
    | (_, 1) => Only
    | (0, _) => First
    | (p, l) when p == l - 1 => Last
    | (_, _) => Middle
    };

  let computeMarginDeltas = (tag, childTags) =>
    List.mapWithIndex(childTags, (i, childTag) =>
      computeVisuallyAppealingMarginDelta(
        tag2tagType(tag),
        tag2tagType(childTag),
        idx2tagPosition(i, List.length(childTags)),
      )
    );

  /* Given an unmeasured badge, measure it & return a measured badge */
  let rec measure = (tag: BlockU.tag): BlockM.tag =>
    switch (tag) {
    | Text(str) =>
      let width = TextWidth.estimate(str);
      let height = BlockConfig.defaultTextHeight;
      /* let margin = adjustedMargin(); */
      Text(str, ref(mkBox(width, height)));
    | Hexagon([]) => Hexagon([], ref(defaultTagBox))
    | Hexagon(childTags) =>
      let marginDeltas = computeMarginDeltas(tag, childTags);
      let (mtags, dim) = measureList(~marginDeltas, childTags);
      Hexagon(mtags, ref(mkBoxFromDim(dim)));
    | Pill([]) => Pill([], ref(defaultTagBox))
    | Pill(childTags) =>
      let marginDeltas = computeMarginDeltas(tag, childTags);
      let (mtags, dim) = measureList(~marginDeltas, childTags);
      Pill(mtags, ref(mkBoxFromDim(dim)));
    }
  and measureList =
      (~marginDeltas=[], tags: list(BlockU.tag)): (list(BlockM.tag), Dim.t) => {
    let mtags =
      if (List.length(marginDeltas) == 0) {
        tags->List.map(measure);
      } else {
        tags
        ->List.zip(marginDeltas)
        ->List.map(((m, marginDelta)) => {
            let mtag = measure(m);
            let box = BlockM.Tag.getBox(mtag);
            let newBox = {
              ...box,
              margin: Margin.add(box.margin, marginDelta),
            };
            BlockM.Tag.setBox(mtag, newBox);
            mtag;
          });
      };
    let combinedDimensions =
      mtags
      ->List.map(BlockM.Tag.getDim)
      ->List.reduce(Dim.zero, Dim.sumWidthMaxHeight);
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
      Middle(mtags, msections, ref(mkBoxFromDim(dim)));
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
    let mmiddles = middles->List.map(measure);
    let dim =
      mmiddles
      ->List.map(BlockM.Middle.getDim)
      ->List.reduce(Dim.zero, Dim.sumWidthMaxHeight);
    (mmiddles, dim);
  }
  and measureSectionList =
      (sections: list(BlockU.section)): (list(BlockM.section), Dim.t) => {
    let msections = sections->List.map(measureSection);
    let dim =
      msections
      ->List.map(BlockM.Middle.getSectionDim)
      ->List.reduce(Dim.zero, Dim.sumWidthMaxHeight);
    (msections, dim);
  };
};