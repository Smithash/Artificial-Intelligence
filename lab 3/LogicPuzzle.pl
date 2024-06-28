% [shirt color, name, superhero, drink, pet, position]

rule1(C1,C2,C3,C4,C5):- C = [red,ntokozo,_,_,_,_], member(C, [C1,C2,C3,C4,C5]).
rule2(C1,C2,C3,C4,C5):- C = [_,saul,_,_,dog,_], member(C, [C1,C2,C3,C4,C5]).
rule3(C1,C2,C3,C4,C5):- C = [green,_,coffee,_,_,_], member(C, [C1,C2,C3,C4,C5]).
rule4(C1,C2,C3,C4,C5):- C = [_,kgosi,tea,_,_,_], member(C, [C1,C2,C3,C4,C5]).

rule5(C1, C2, C3, C4, C5) :-
    WhiteC = [white, _, _, _, _, WhitePos],
    member(WhiteC, [C1, C2, C3, C4, C5]),
    GreenC = [green, _, _, _, _, GreenPos],
    member(GreenC, [C1, C2, C3, C4, C5]),
    GreenPos is WhitePos + 1.

rule6(C1,C2,C3,C4,C5):- C = [_,_,_,superman,snails,_], member(C, [C1,C2,C3,C4,C5]).
rule7(C1,C2,C3,C4,C5):- C = [yellow,_,_,hulk,_,_], member(C, [C1,C2,C3,C4,C5]).
rule8(C1,C2,C3,C4,C5):- C = [_,_,milk,_,_,3], member(C, [C1,C2,C3,C4,C5]).
rule9(C1,C2,C3,C4,C5):- C = [_,jay,_,_,_,1], member(C, [C1,C2,C3,C4,C5]).

rule10(C1,C2,C3,C4,C5):- 
    IronmanC = [_, _, _, ironman, _, IronmanPos],
    member(IronmanC, [C1,C2,C3,C4,C5]),
    ParrotC = [_, _, _, _, parrot, ParrotPos],
    member(ParrotC, [C1,C2,C3,C4,C5]),
    PosDiff is abs(IronmanPos - ParrotPos),
    PosDiff =:= 1.


rule11(C1,C2,C3,C4,C5):- 
    HulkC = [_, _,_,hulk, _, HulkPos],
    member(HulkC, [C1,C2,C3,C4,C5]),
    HorseC = [_, _, _, _, horse, HorsePos],
    member(HorseC, [C1,C2,C3,C4,C5]),
    PosDiff is abs(HulkPos - HorsePos),
    PosDiff =:= 1.


rule12(C1,C2,C3,C4,C5):- C = [_, _, orange, spiderman, _, _], member(C, [C1,C2,C3,C4,C5]).
rule13(C1,C2,C3,C4,C5):- C = [_, john,_, batman, _, _], member(C, [C1,C2,C3,C4,C5]).

%Since Jay is pos 1 and is next to blue shirt, then blue shirt is pos 2
rule14(C1,C2,C3,C4,C5):- C= [blue,_,_,_,_,2], member(C, [C1,C2,C3,C4,C5]).

members([], _).
members([X|Xs], List) :-
    member(X, List),
    members(Xs, List).

solve(C1,C2,C3,C4,C5) :-
C1 = [C1_col,C1_name,C1_drink,C1_superhero,C1_pet,1],
C2 = [C2_col,C2_name,C2_drink,C2_superhero,C2_pet,2],
C3 = [C3_col,C3_name,C3_drink,C3_superhero,C3_pet,3],
C4 = [C4_col,C4_name,C4_drink,C4_superhero,C4_pet,4],
C5 = [C5_col,C5_name,C5_drink,C5_superhero,C5_pet,5],
    
rule1(C1,C2,C3,C4,C5),
rule2(C1,C2,C3,C4,C5),
rule3(C1,C2,C3,C4,C5),
rule4(C1,C2,C3,C4,C5),
rule5(C1,C2,C3,C4,C5),
rule6(C1,C2,C3,C4,C5),
rule7(C1,C2,C3,C4,C5),
rule8(C1,C2,C3,C4,C5),
rule9(C1,C2,C3,C4,C5),
rule10(C1,C2,C3,C4,C5),
rule11(C1,C2,C3,C4,C5),
rule12(C1,C2,C3,C4,C5),
rule13(C1,C2,C3,C4,C5),
rule14(C1,C2,C3,C4,C5),
    
members([white, green, red, blue, yellow],
[C1_col,C2_col,C3_col,C4_col,C5_col]),
members([saul, john, ntokozo, kgosi, jay],
[C1_name,C2_name,C3_name,C4_name,C5_name]),
members([orange, coffee, milk, tea, water],
[C1_drink,C2_drink,C3_drink,C4_drink,C5_drink]),
members([spiderman, batman, superman, ironman, hulk],
[C1_superhero,C2_superhero,C3_superhero,C4_superhero,C5_superhero]),
members([dog, cat, snails, horse, parrot],
[C1_pet,C2_pet,C3_pet,C4_pet,C5_pet]).

