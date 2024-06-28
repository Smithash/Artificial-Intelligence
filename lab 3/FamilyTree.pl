male(greg).
male(adam).
male(trent).
male(martin).
male(marcus).
male(gabriel).
male(dave).
male(michael).

female(lucy).
female(amy).
female(kgomotso).
female(naledi).
female(karen).
female(michelle).

parent(trent, greg).
parent(naledi, greg).
parent(trent, adam).
parent(trent, kgomotso).
parent(karen, adam).
parent(karen, kgomotso).
parent(gabriel, marcus).
parent(gabriel, michelle).
parent(gabriel, naledi).
parent(amy, marcus).
parent(amy, michelle).
parent(amy, naledi).
parent(dave, trent).
parent(dave, martin).
parent(lucy, trent).
parent(lucy, martin).
parent(martin, michael).

married(amy, gabriel).
married(lucy, dave).
married(naledi, trent).

spouse(X,Y) :- married(X,Y); married(Y,X).
mother(X,Y) :- parent(X,Y), female(X).
father(X,Y) :- parent(X,Y), male(X).

sibling(X,Y) :- mother(Z,X), mother(Z,Y), father(W,X), father(W,Y), X\=Y.
brother(X,Y) :- sibling(X,Y), male(X).
sister(X,Y) :- sibling(X,Y), female(X).

half_sibling(X,Y) :- parent(Z,X) , parent(Z,Y), parent(W,X), parent(V,Y), W\=V, X\=Y.
half_brother(X,Y) :- half_sibling(X,Y), male(X).
half_sister(X,Y) :- half_sibling(X,Y), female(X).

uncle(X,Y) :- parent(Z,Y), brother(X,Z).
aunt(X,Y) :- parent(Z,Y), sister(X,Z).

grandparent(X,Y) :- parent(Z,Y), parent(X,Z).
grandmother(X,Y) :- grandparent(X,Y), female(X).
grandfather(X,Y) :- grandparent(X,Y), male(X).

nephew(X,Y) :- male(X), parent(Z,X), sibling(Z,Y).
niece(X,Y) :- female(X), parent(Z,X), sibling(Z,Y).
cousin(X,Y) :- parent(Z,X), parent(W,Y), sibling(Z,W).

in_law(X,Y) :- (spouse(X,Z)), (sibling(Z,Y);parent(Y,Z)).
brother_in_law(X,Y) :- in_law(X,Y), male(Y).
sister_in_law(X,Y) :- in_law(X,Y), female(Y).

                                                    