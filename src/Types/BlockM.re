/* BlockM is the "measured" variant of a block--in addition to type information,
   it also has a size (box) */

type box = Box.t;

type style = BlockStyle.t;

type tag =
  | Text(string, ref(box))
  | Pill(list(tag), ref(box))
  | Hexagon(list(tag), ref(box));
module Tag = {
  /* Measured Abstract Block Components */
  type t = tag;

  let setBox = (tag: t, newBox: box): unit => {
    let boxRef =
      switch (tag) {
      | Hexagon(_, box) => box
      | Pill(_, box) => box
      | Text(_, box) => box
      };
    boxRef := newBox;
  };

  let getBox = (tag: t): box => {
    let boxRef =
      switch (tag) {
      | Hexagon(_, box) => box
      | Pill(_, box) => box
      | Text(_, box) => box
      };
    boxRef^;
  };

  let getDim = (tag: t): Dim.t => {
    let box = getBox(tag);
    {width: Box.outerWidth(box), height: Box.outerHeight(box)};
  };
};

type first =
  | First(list(Tag.t), ref(box));
module First = {
  type t = first;

  let getBox = (first: t): box => {
    let First(_, boxRef) = first;
    boxRef^;
  };

  let getDim = (first: t): Dim.t => first->getBox->Box.innerDim;
};

type last =
  | Last(list(Tag.t), ref(box));
module Last = {
  type t = last;

  let getBox = (last: t): box => {
    let Last(_, boxRef) = last;
    boxRef^;
  };

  let getDim = (last: t): Dim.t => last->getBox->Box.innerDim;
};

type middle =
  | Middle(list(tag), list(section), ref(box))
and section =
  | Section(list(tag), list(middle), option(last), ref(box));
module Middle = {
  type t = middle;

  let getBox = (middle: t): box => {
    let Middle(_, _, boxRef) = middle;
    boxRef^;
  };

  let getSectionBox = (section: section): box => {
    let Section(_, _, _, boxRef) = section;
    boxRef^;
  };

  let getDim = (middle: t): Dim.t => middle->getBox->Box.innerDim;

  let getSectionDim = (section: section): Dim.t =>
    section->getSectionBox->Box.innerDim;
};

type layout =
  | Layout(option(First.t), list(Middle.t), option(Last.t), ref(box));
module Layout = {
  type t = layout;
};