# Notes

instead of array or vector of booleans use vectorbit - [isUniq](./array-and-strings/isUniq.cpp)

When iterating two strings with two indexes use while loop and break.

StringBuilder: without it concatanating strings would take O(n^2) - (n=number of strings) because every append means creating a new string and copying all charachters. StringBuilder works by using a resizable array. another solution is sometimes to figure out the size of the array before initiating it.

When the solution is complex and is a lot of code. break it down to reusable functions so you can first write your skeleton. later you can concentrate on the details

Helps to think how to solve a problem in real life.

in question about finding a successor on binary tree i didn't think about all the cases. skectch an example and run it to the fullest. no shortcuts.

Trust and Focus. Define functions that take care of parts of the solution. then trust that they do it correctly so you can focus on the rest of the solution and implementation

Remeber there is a difference between Binary trees and Binary search trees.

Sum of array. when checking for something in each subarray or subtree we can use hashtable to "cut" the current path.
we use a function like f(current, runningSum, targetSum, table) then to check if the how many sub array we walk the array and for rach current we add the running sum and check if target sum - running sum is in the hash table and how many times.

Pay attention to atithmetic shift vs logical shift. also consider edge cases.

Be more organize input output. try solving edge cases first. varibales names.