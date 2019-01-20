let textCharWidths = [|
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  17,
  26,
  46,
  63,
  42,
  105,
  45,
  20,
  25,
  25,
  47,
  39,
  21,
  34,
  26,
  36,
  36,
  28,
  36,
  36,
  36,
  36,
  36,
  36,
  36,
  36,
  27,
  27,
  36,
  35,
  36,
  35,
  65,
  42,
  43,
  42,
  44,
  35,
  34,
  43,
  46,
  25,
  39,
  40,
  31,
  59,
  47,
  43,
  41,
  43,
  44,
  39,
  28,
  44,
  43,
  65,
  37,
  39,
  34,
  37,
  42,
  37,
  50,
  37,
  32,
  43,
  43,
  39,
  43,
  40,
  30,
  42,
  45,
  23,
  25,
  39,
  23,
  67,
  45,
  41,
  43,
  42,
  30,
  40,
  28,
  45,
  33,
  52,
  33,
  36,
  31,
  39,
  26,
  39,
  55,
|];

let estimate = (~fontSize=25.2, text: string) => {
  let width: ref(int) = ref(0);
  String.iter(
    char => width := width^ + textCharWidths[int_of_char(char)],
    text,
  );

  float_of_int(width^) *. fontSize /. 100.;
};