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
// a:(3 1;1 2);
// b:enlist 9 8;
// .af.solve[a;b]

