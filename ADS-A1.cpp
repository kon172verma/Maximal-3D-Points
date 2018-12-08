// COL-702 		:	Advances Data Structures and Algorithms.
// Assignment 1 : 	Find all the maximal points in a 3-dimensional space.
// Student name : 	Konark Verma
// Roll number 	: 	2018MCS2025

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<vector>
#include "AVL.h"
using namespace std;

//AVL Tree that is used to find the maximal points.
AVLTree tree;

//Declaration of the Randomized Quick Sort Function for 3-d points.
void RQSort(int **points, int first, int last);
//Declaration of the partition function for Randomized Quick Sort for 3-d points.
int partition(int **points, int first, int last);
//Declaration of the Randomized Single Dimension Quick Sort Function.
void SP_RQSort(int* points, int first, int last);
//Declaration of the partition function for Single Dimension Randomized Quick Sort
int SP_partition(int* points, int first, int last);


int main(int argc, char* argv[]){

	if(argc<3){
		cout<<"Command line arguments not correctly passed.";
		return -1;
	}

	//opening the input file that contains the 3-dimensional points.
	ifstream infile;
	infile.open(argv[1]);
	if(!infile){
		cout<<"Unable to open the input file.";
		return -2;
	}

    //finding the number of points present in the input file.
    int n;
    infile>>n;

	//creating a 2-d dynamic array
	int **points = new int*[n];
	int i=0;
	while(i<n) points[i++] = new int[4];

    //storing the points in that array.
	for(i=0;i<n;i++){
        points[i][0] = i;
        infile >> points[i][1] >> points[i][2] >> points[i][3];
    }

	//sorting all the points.
	RQSort(points, 0, n-1);

    //A dynamic array to store the index of the maximal points.
    int* result = new int[n];
    //A variable count to store the number of the maximal points.
    int count=0;

    //declaring three points to store the points extracted from ladder and the tree.
    int in,a,b,c;
    int li,la,lb,lc;
    int ti,ta,tb,tc;
    int prev_x, prev_y, prev_z, z_val;

    //finding the maximal points for all the planes.

    in = points[n-1][0];
    a = prev_x = points[n-1][1];
    b = prev_y = points[n-1][2];
    c = prev_z = points[n-1][3];
    z_val = c;
    tree.insert(in,a,b,c);
    result[count++] = in;

    for(int i=n-2; i>=0; i--){

        if(points[i][1] != prev_x){
            //point required.
            in = points[i][0];
            a = prev_x = points[i][1];
            b = prev_y = points[i][2];
            c = prev_z = points[i][3];
            z_val = c;
        }
        else{
            if(points[i][2] == prev_y){
                //discard this point.
                prev_x = points[i][1];
                prev_y = points[i][2];
                prev_z = points[i][3];
                continue;
            }
            else{
                if(points[i][3]>z_val){
                    //point required.
                    in = points[i][0];
                    a = prev_x = points[i][1];
                    b = prev_y = points[i][2];
                    c = prev_z = points[i][3];
                    z_val = c;
                }
                else{
                    //discard this point.
                    prev_x = points[i][1];
                    prev_y = points[i][2];
                    prev_z = points[i][3];
                    continue;
                }
            }
        }
        lb = tree.closest_y_greater(b);
        //case 1: if our point lie in the region B.
        if(lb == -1){
            lb = tree.find_max_y();
            lc = tree.find_z(lb);
            tc = tree.closest_z_greater(c);

            // if our point dominates the entire ladder.
            if(tc==-1){
                tc = tree.find_max_z();
                tb = tree.find_y(tc);
                tree.delete_range(tb,lb);
                tree.delete_node(lb);
                tree.delete_node(tb);
            }

            // if our point does not dominate the entire ladder.
            else{
                tb = tree.find_y(tc);
                // if our point dominates some of the points of the ladder.
                if(tb!=lb){
                    tree.delete_range(tb,lb);
                    tree.delete_node(lb);
                }
            }
            //point is inserted in the tree and its index is inserted in the resultant vector.
            tree.insert(in,a,b,c);
            result[count++] = in;
        }
        //case 2: if our point lie inside the ladder.
        else if(b<=lb && c<=tree.find_z(lb)){
            //discard this point.
        }
        //case 3: if our point lie in the region A.
        else{
            tc = tree.closest_z_greater(c);
            // if our point does not have z greater than the maximal value of z in the tree.
            if(tc == -1){
                tc = tree.find_max_z();
                tb = tree.find_y(tc);
                tree.delete_range(tb,lb);
                if(b==lb)
                    tree.delete_node(lb);
                if(tb!=lb)
                    tree.delete_node(tb);
            }
            //if our point has z value greater than the maximum value of z in the tree.
            else{
                tb = tree.find_y(tc);
                tree.delete_range(tb,lb);
                if(b==lb)
                    tree.delete_node(lb);
                if(c==tc)
                    tree.delete_node(tb);
            }
            //point is inserted in the tree and its index is inserted in the resultant vector.
            tree.insert(in,a,b,c);
            result[count++] = in;
        }
    }

    //printing the count and all the maximal points.
    ofstream outfile;
    outfile.open(argv[2]);
    if(!outfile){
    	printf("Unable to open the output file.");
    	return -3;
    }
    outfile<<count<<endl;
    SP_RQSort(result,0,count-1);
    for(i=0;i<count;i++){
        outfile<<result[i]<<endl;
    }
	return 0;
}

//********************************************************************************//
//********************************************************************************//

//Implementation of the Randomized Quick Sort for the 3-d points.
void RQSort(int **points, int first, int last){

	if(first>=last)
		return;
	int mid = partition(points, first, last);
	RQSort(points, first, mid-1);
	RQSort(points, mid+1, last);
}

// Implementation of the partition function for the randomized quick sort for 3-d points.
int partition(int **points, int first, int last){

    // mid stores the random value generated between first and last.
	int mid = rand()%(last-first+1)+first;
	int pivot_x = points[mid][1];
	int pivot_y = points[mid][2];
	int pivot_z = points[mid][3];
	int i,j,flag;
	int x,y,z, index;

    //points are sorted on the basis of the pivot value.
	for(i=j=first;j<=last;j++){
		if(points[j][1]<=pivot_x || (points[j][1]==pivot_x && (points[j][2]<=pivot_y || (points[j][2]==pivot_y && points[j][3]<=pivot_z) ))){
			if(points[j][1]==pivot_x && points[j][2]==pivot_y && points[j][3]==pivot_z ){
				flag = i;
			}
			index = points[j][0];
			x = points[j][1];
			y = points[j][2];
			z = points[j][3];
			points[j][0] = points[i][0];
			points[j][1] = points[i][1];
			points[j][2] = points[i][2];
			points[j][3] = points[i][3];
			points[i][0] = index;
			points[i][1] = x;
			points[i][2] = y;
			points[i][3] = z;
			i++;
		}
	}

    //pivot element stored at the i-1 location.
    index = points[flag][0];
	x = points[flag][1];
	y = points[flag][2];
	z = points[flag][3];
	points[flag][0] = points[i-1][0];
	points[flag][1] = points[i-1][1];
	points[flag][2] = points[i-1][2];
	points[flag][3] = points[i-1][3];
	points[i-1][0] = index;
	points[i-1][1] = x;
	points[i-1][2] = y;
	points[i-1][3] = z;

    //location of the pivot element returned.
	return i-1;
}

//Implementation of the Randomized Quick Sort for 1-d array.
void SP_RQSort(int* points, int first, int last){

	if(first>=last)
		return;
	int mid = SP_partition(points, first, last);
	SP_RQSort(points, first, mid-1);
	SP_RQSort(points, mid+1, last);
}

// Implementation of the partition function for the randomized quick sort for 1-d array.
int SP_partition(int* points, int first, int last){

    // mid stores the random value generated between first and last.
	int mid = rand()%(last-first+1)+first;
	int pivot = points[mid];
	int i,j,flag;
	int temp;

    //points are sorted on the basis of the pivot value.
	for(i=j=first;j<=last;j++){
		if(points[j]<=pivot){
			if(points[j]==pivot){
				flag = i;
			}
			temp = points[j];
			points[j] = points[i];
			points[i] = temp;
			i++;
		}
	}
	//pivot element stored at the i-1 location.
    temp = points[flag];
    points[flag] = points[i-1];
    points[i-1] = temp;

    //location of the pivot element returned.
	return i-1;
}
