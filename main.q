\l fireq.q

a:neg[1]+1000000?2e;

// Abs
// \ts b:abs a;
// \ts c:.af.abs a;
// b~c

// Accum
// \ts:10 b:sums a;
// \ts:10 c:.af.accum a;
// b~c

// Acos
// \ts:10 b:acos a;
// \ts:10 c:.af.acos a;
// b~c // just handling of nulls

// All
\ts:10 b:all a;
\ts:10 c:.af.all_true a;
b~c
