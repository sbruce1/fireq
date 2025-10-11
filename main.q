\l fireq.q

a:neg[1]+1000000?2e;

// Abs
// \ts b:abs a;
// \ts c:.af.abs a;
// b~c

// Acos
\ts:10 b:acos a;
\ts:10 c:.af.acos a;
b~c // just handling of nulls
