# find_dups

Simple routine to find elements of an input array that add up to zero.  So, 5 and -5
would be found as `duplicate` elements.

The algorithm goes through each element in the input array and breaks it up into two
separate arrays, one to hold the positive elements, and one to hold the negative elements.
When inserting new elements into each array, these two arrays are kept sorted by using a 
binary search to find the correct position.  Since there are n elements in the input
array and each insert operation uses a binary search that will take log(n) time.  Creating
these two subarrays will take O(nlogn) time.  If we are lucky and there are approximately
equal numbers of positive and negative elements in the input array, we could get that
this part of the algorithm only takes O(n log(n/2)) time.

Once the two subarrays are built, we just march through them seeing if the elements in each
subarray at the current index add up to zero.  This part of the algorithm adds another O(n)
time to the algorithm.

Note that we find pairs of zeroes in the first pass of the input array.  Every time that
we find a zero we just toggle a flag between 0 and 1, and if the flag is 1 when we find a
zero, we announce that we have found a pair.
