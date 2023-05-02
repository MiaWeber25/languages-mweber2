class(csci310).
class(csci420).
class(csci225).
class(csci315).

student(john).
student(stacy).
student(matt).
student(cristy).

instructor(cathy).
instructor(jacob).
instructor(nancy).
instructor(stella).

enrolled(john, csci310).
enrolled(stacy, csci420).
enrolled(matt, csci225).
enrolled(cristy, csci315).

instructs(cathy, csci310).
instructs(jacob, csci420).
instructs(nancy, csci225).
instructs(stella, csci315).

semester(fall).
semester(spring).

offered(csci310, fall).
offered(csci225, fall).
offered(csci420, spring).
offered(csci315, spring).

prerec(csci420).
prerec(csci315).

professor(X, Y) :-
instructs(X, C), enrolled(Y, C).
