/** Oral Questions
1. Process vs Threads - Didn't prep OS. 
Asked "So, you're not aware of Paging, Virual Memory,etc. "
2. Hash Map - explain what are they (explaination could've been better)
3. Favorite Search - Binary Search (Very versatile)
*/


//4. BST - construct using given numbers
//5. DFS in grid

/**
 Optimisations I meed out in interview-
 1. Use dx = [1,-1,0,0] and dy = [0,0,1,-1] and loop through i+dx[k], j+dy[k] insted
 2. Only need to tranverse right and bottom edges to cover grid
 3. use bool 'ans' and at each iteration do ans = ans || dfs(...)
*/

#include<bits/stdc++.h>
using namespace std;

bool isValid(int i, int j, vector<vector<int>> &grid){
    if(0<=i && i<grid.size() && 0<=j && j<grid[0].size())
        return true;
    
    return false;
}

int dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int val, int i, int j){
    visited[i][j] = true;
    if (grid[i][j] == val)
        return 1;

    int ans = 0;

    if(isValid(i+1, j, grid) && !visited[i+1][j])
        ans += dfs(grid, visited, val, i+1, j);
    if(isValid(i-1, j, grid) && !visited[i-1][j])
        ans += dfs(grid, visited, val, i-1, j);
    if(isValid(i, j+1, grid) && !visited[i][j+1])
        ans += dfs(grid, visited, val, i, j+1);
    if(isValid(i, j-1, grid) && !visited[i][j-1])
        ans += dfs(grid, visited, val, i, j-1);
        
    return ans;
}
