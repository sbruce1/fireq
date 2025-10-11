\l fireq.q

a:neg[1]+1000000?2e;
a:1000000?1f;

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

// Asc
// \ts:10 b:asc a;
// \ts:10 c:.af.asc a;
// b~c

