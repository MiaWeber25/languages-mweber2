(*let%test "empty list is sorted" =
 * is_sorted []

*let%test "list with one element is sorted" =
 * is_sorted [42]

*let%test "sorted list" =
 * is_sorted [1; 2; 3; 4; 5]

*let%test "unsorted list" =
 * not (is_sorted [5; 4; 3; 2; 1])

*let%test "list with repeated elements" =
 * is_sorted [1; 2; 2; 3; 4]

*let%test "list with equal elements" =
 * is_sorted [1; 1; 1; 1; 1]

*let%test "list with negative numbers" =
*  is_sorted [-3; -2; -1; 0; 1; 2; 3]

*let rec fact n = if n = 1 then 1 else n * fact (n - 1)

*let%test _ = fact 5 = 120*)

open Base

let%test_unit "rev" =
  [%test_eq: int list] (List.rev [ 3; 2; 1 ]) [ 3; 2; 1 ]