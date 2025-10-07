# ArrayFire Wrapper for Q

ArrayFire is a GPU library that operates on Arrays, seems to be perfect for GPU acceleration in Q.

## List of ArrayFire Functions with Q Equivalent

| Function                    | Description                                                                                               | Q Function Equivalent |
|-----------------------------|-----------------------------------------------------------------------------------------------------------|-----------------------|
|  abs                        | Calculate the absolute value                                                                              | abs                   |
|  accum                      | Evaluate the cumulative sum (inclusive) along a given dimension                                           | sums                  |
|  acos                       | Evaluate the inverse cosine function (arc cosine)                                                         | acos                  |
|  add                        | Elementwise addition                                                                                      | +                     |
|  allTrue                    | Check if all values along a given dimension are true                                                      | all                   |
|  and                        | Evaluate the logical AND of two arrays                                                                    | and                   |
|  approx1                    | Interpolation across a single dimension                                                                   | lsq-ish               |
|  approx2                    | Interpolation along two dimensions                                                                        | lsq-ish               |
|  asin                       | Evaluate the inverse sine function (arc sine)                                                             | asin                  |
|  atan/atan2                 | Evaluate the inverse tangent function (arc tangent)                                                       | atan                  |
|  cast                       | Cast an array from one type to another                                                                    | $                     |
|  ceil                       | Rounds up to the least integer greater than or equal to x                                                 | ceiling               |
|  constant                   | Create an array from a scalar input value                                                                 | #                     |
|  cos                        | Evaluate the cosine function                                                                              | cos                   |
|  cov                        | Find the covariance of values in the input                                                                | cov                   |
|  diff1                      | Calculate the first order difference in an array over a given dimension                                   | diff (?)              |
|  diff2                      | Calculate the second order difference in an array over a given dimension                                  | diff (?)              |
|  div                        | Elementwise division                                                                                      | div                   |
|  eq                         | Equal to, an elementwise comparison of two arrays                                                         | =                     |
|  exp                        | Evaluate the exponential function                                                                         | exp                   |
|  flat                       | Flatten an array                                                                                          | raze (docs says noop) |
|  flip                       | Flip the input along a specified dimension                                                                | flip                  |
|  floor                      | Rounds down to the greatest integer less than or equal to x                                               | floor                 |
|  ge                         | Greater than or equal to, an elementwise comparison of two arrays                                         | >=                    |
|  iota                       | Generate an array with [0, n-1] values modified to specified dimensions and tiling                        | til                   |
|  join                       | Join up to 4 arrays along specified dimension                                                             | ,                     |
|  log                        | Evaluate the natural logarithm                                                                            | log                   |
|  log10                      | Evaluate the base 10 logarithm                                                                            | 10 xlog               |
|  log2                       | Evaluate the base 2 logarithm                                                                             | 2 xlog                |
|  lookup                     | Lookup values of an array by indexing with another array                                                  | @                     |
|  lu                         | Perform LU decomposition                                                                                  | inv (inv uses this)   |
|  matmul                     | Matrix multiplication                                                                                     | mmu                   |
|  max                        | Return the maximum along a given dimension                                                                | max                   |
|  mean                       | Find the mean of values in the input                                                                      | mean                  |
|  median                     | Find the median of values in the input                                                                    | med                   |
|  min                        | Return the minimum along a given dimension                                                                | min                   |
|  mod                        | Calculate the modulus                                                                                     | mod                   |
|  nearestNeighbour           | Determine the nearest neighbouring points to a given set of points                                        | ai-libs flat          |
|  neg                        | Negate an array                                                                                           | neg                   |
|  not                        | Evaluate the logical NOT of an array                                                                      | not                   |
|  or                         | Evaluate the logical OR of two arrays                                                                     | or                    |
|  pow                        | Raise a base to a power (or exponent)                                                                     | xexp                  |
|  pow2                       | Raise 2 to a power (or exponent)                                                                          | 2 xexp                |
|  product                    | Multiply array elements over a given dimension                                                            | */                    |
|  rotate                     | Rotate an input image or array                                                                            | rotate                |
|  select                     | Select elements based on a conditional array                                                              | select                |
|  setintersect               | Evaluate the intersection of two arrays                                                                   | inter                 |
|  setunion                   | Evaluate the union of two arrays                                                                          | union                 |
|  setunique                  | Return the unique values in an array                                                                      | distinct              |
|  shift                      | Shift an array                                                                                            | xrotate               |
|  sin                        | Evaluate the sine function                                                                                | sin                   |
|  solve                      | Solve a system of equations                                                                               | lsq                   |
|  solveLU                    | Solve a system of equations                                                                               | lsq                   |
|  sort                       | Sort an array over a given dimension                                                                      | asc/desc              |
|  sortIndex                  | Sort an array over a given dimension and return the original indices                                      | xasc/xdesc            |
|  sqrt                       | Evaluate the square root                                                                                  | sqrt                  |
|  stdev                      | Find the standard deviation of values in the input                                                        | sdev                  |
|  sum                        | Sum array elements over a given dimension                                                                 | sum                   |
|  tan                        | Evaluate the tangent function                                                                             | tan                   |
|  topk                       | This function returns the top k values along a given dimension of the input array                         | ai-libs topk          |
|  var                        | Find the variance of values in the input                                                                  | var                   |
|  where                      | Locate the indices of the non-zero values in an array                                                     | where                 |


## List of Q Functions