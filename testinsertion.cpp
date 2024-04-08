#include <vector>
#include <iostream>

void printVals( const std::vector<int> & vals);
void insertionSort( std::vector<int> & vec );
void mergeSort( std::vector<int> & ref);
void merge( std::vector<int> & left, std::vector<int> & right, std::vector<int> & ref);

void printVals( const std::vector<int> & vals)
{
    for (size_t i = 0; i < vals.size(); i++) {
        std::cout << vals[i] << " ";
    }
    std::cout << std::endl;
}


void insertionSort( std::vector<int> & vec )
{
    if (vec.size() < 2) return;
    for(size_t i = 1; i < vec.size(); i++)
    {
        int tmp = vec[i];
        size_t backIndex = i - 1;
        for(; backIndex >= 0 && vec[backIndex] > tmp; backIndex--) {
            vec[backIndex + 1] = vec[backIndex];
        }
        vec[backIndex+1] = tmp;
    }
}


void mergeSort( std::vector<int> & ref)
{
    if (ref.size() <= 1) return;
    
    size_t size = ref.size();
    size_t leftBranchSize = size / 2;
    size_t rightBranchSize = size - leftBranchSize;

    std::vector<int> leftBranch(leftBranchSize);
    std::vector<int> rightBranch(rightBranchSize);

    for(size_t i = 0; i < leftBranchSize; i++) { leftBranch[i] = ref[i]; }
    for(size_t i = leftBranchSize; i < size; i++) { rightBranch[i - leftBranchSize] = ref[i]; }

    mergeSort(leftBranch);
    mergeSort(rightBranch);
    merge(leftBranch, rightBranch, ref);
}

void merge( std::vector<int> & left, std::vector<int> & right, std::vector<int> & ref)
{
    size_t leftBranchSize = ref.size() / 2;
    size_t rightBranchSize = ref.size() - leftBranchSize;
    size_t i = 0, l = 0, r = 0;

    while (l < leftBranchSize && r < rightBranchSize) {
        if (left[l] < right[r]) {
            ref[i] = left[l]; i++; l++; continue ;
        }
        ref[i] = right[r]; i++; r++;
    }
    
    while(l < leftBranchSize) { ref[i] = left[l]; i++; l++; }
    while(r < rightBranchSize) { ref[i] = right[r]; i++; r++; }
}

int main() 
{

    std::vector<int> vals = {19, 4, 1, 2, 90};
    printVals(vals);
    mergeSort(vals);
    printVals(vals);

    return 0;

}