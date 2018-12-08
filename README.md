# COL-702, Programming Assignment 1

# Maximal-3D-Points
A point p is said to dominated by point q if p.x ≤ q.x , p.y ≤ q.y , p.z ≤ q.z . Given a set of points P = {p1, p2,...,pn} in 3-dimensoinal space, each represented by its x, y, z integer coordinates, a point is said to be maximal iff it is not dominated by any other point. Here, we are finding all such points.

# Input Format
The first line of input should contain a single integer N denoting the number of 3 dimensional points.
Each of next N lines contain three space-separated integers denoting x, y and z coordinate respectively.

# Output Format
The first line of output contains a single integer M denoting the number of maximal points
Next M lines contain the index of maximal points(in ascending order)

# Example

Input:

5
1218 1619 977
1357 7432 4590
4608 6903 1632
5454 7521 8958
7020 3604 4485

Output for the above input: 2 points are maximal, having index 3 and 4 (Use Zero Indexing)

2
3
4

* All points in input will have integer coordinates and will be unique
* Binary Search Tree must be used to store points.


* In my code, implement an array instead of a vector in 'AVL.h' to get better performance.

* Thanks to Ayush Gupta (Teaching Assistant, for course COL-702) for generating the test cases.
* Test cases given here, were first available on : http://www.cse.iitd.ac.in/~cs5140281/ec.html