\l fireq.q

0N!"MMU Speed Test";
a:1000 1000#1000000?1f;
b:1000 1000#"f"$til 1000000;
0N!"Q";
\ts:10 mmu[;b] peach a
0N!"AF";
\ts:10 .af.mmu[a;b]

-1 "\n";

0N!"INV Speed Test";
0N!"Q";
\ts inv a;
0N!"AF";
\ts .af.inv a;

-1 "\n";
