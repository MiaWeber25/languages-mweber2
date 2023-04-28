  let rec is_sorted lst =
  match lst with
  | [] | [_] -> true
  | x :: y :: xs -> x <= y && is_sorted (y :: xs)