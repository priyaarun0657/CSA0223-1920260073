# Memory diagram
`stock`: [40][25][12][8][30][15][9][22]
`p` points to stock[0]. `p+3` points to stock[3]. `*(p+3)` and `p[3]` read 8. `*p++` reads the first value then advances the pointer (post-increment binds to p).
