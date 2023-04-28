open OUnit2
open Sum

let tests =
  "is_sorted" >::: [
    "empty list" >:: (fun _ -> assert_equal true (is_sorted []));
    "one element" >:: (fun _ -> assert_equal true (is_sorted [42]));
    "sorted list" >:: (fun _ -> assert_equal true (is_sorted [1; 2; 3; 4; 5]));
    "unsorted list" >:: (fun _ -> assert_equal false (is_sorted [5; 4; 3; 2; 1]));
    "list with repeated elements" >:: (fun _ -> assert_equal true (is_sorted [1; 2; 2; 3; 4]));
    "list with equal elements" >:: (fun _ -> assert_equal true (is_sorted [1; 1; 1; 1; 1]));
    "list with negative numbers" >:: (fun _ -> assert_equal true (is_sorted [-3; -2; -1; 0; 1; 2; 3]));
  ]

let () = run_test_tt_main tests