/* Unmeasured Abstract Block Components */

type tag =
  | Text(string)
  | Pill(list(tag))
  | Hexagon(list(tag));
module Tag = {
  type t = tag;
};

type first =
  | First(list(tag));
module First = {
  type t = first;
};

type last =
  | Last(list(tag));
module Last = {
  type t = last;
};

type middle =
  | Middle(list(tag), list(section))
and section =
  | Section(list(tag), list(middle), option(last));
module Middle = {
  type t = middle;
};

type layout =
  | Layout(option(first), list(middle), option(last));
module Layout = {
  type t = layout;
};