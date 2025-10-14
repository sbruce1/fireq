\l fireq.q

// Abs
// \ts b:abs a;
// \ts c:.af.abs a;
// b~c

// Accum
// \ts:10 b:sums a;
// \ts:10 c:.af.accum a;
// b~c

// Acos
// \ts:10 b:{x*x} deltas a;
// \ts:10 c:.af.diff2 a;
// b~c // just handling of nulls

// Solve
a:(0.1 3.1 6.1;1.1 4.1 7.0;2.0 5.0 8.0);
b:(enlist[21.9];enlist[30.7];enlist[39.0]);
// b:enlist 9 8;
.af.solve[a;b]

//A [3 3 1 1]
    //0.1000     3.1000     6.1000
    //1.1000     4.1000     7.0000
    //2.0000     5.0000     8.0000
 //
//B0 [3 1 1 1]
   //21.9000
   //30.7000
   //39.0000
 //
