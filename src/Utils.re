let cumuSum = (nums: list(float)): list(float) => {
  let rec loop = (remainingNums: list(float), accumNum: float): list(float) =>
    switch (remainingNums) {
    | [] => []
    | [head, ...remaining] =>
      let sum = head +. accumNum;
      [sum, ...loop(remaining, sum)];
    };
  loop(nums, 0.);
};