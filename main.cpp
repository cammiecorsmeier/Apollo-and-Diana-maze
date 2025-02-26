#include <iostream>
 #include <fstream>
 #include <vector>
 #include <stack>
 #include <map>

 using namespace std;

 // Structure to represent a vertex in the graph
 struct Vertex {
     char color;         // R for red, B for blue, O for bull's-eye
     string direction;   // N, E, S, W, NE, SE, SW, NW
 };

 // Function to read the maze from the input file
 vector<vector<Vertex>> readMaze(const string& filename) {
     ifstream file(filename);
     int rows, cols;
     file >> rows >> cols;

     vector<vector<Vertex>> maze(rows, vector<Vertex>(cols));

     for (int i = 0; i < rows; ++i) {
         for (int j = 0; j < cols; ++j) {
             string arrow;
             file >> arrow;

             // Check if this is the last arrow indicating the bull's-eye
             if (arrow == "O") {
                 maze[i][j].color = 'O';
                 maze[i][j].direction = ""; // No direction for the bull's-eye
             } else {
                 // Find the position of '-' in the arrow string
                 size_t hyphenPos = arrow.find('-');
                 if (hyphenPos != string::npos) {
                     // Extract color and direction from the arrow string
                     maze[i][j].color = arrow[0];
                     maze[i][j].direction = arrow.substr(hyphenPos + 1);
                 } else {
                     // Handle invalid arrow format (no '-')
                     cerr << "Error: Invalid arrow format at position " << i + 1 << ", " << j + 1 << endl;
                     exit(EXIT_FAILURE);
                 }
             }
         }
     }

     return maze;
 }

 // Function to perform iterative DFS and find a path to the bull's-eye
 bool findPathDFS(const vector<vector<Vertex>>& maze, vector<vector<bool>>& visited,
                  vector<pair<int, int>>& resultPath, stack<char>& colorStack) {
     int rows = maze.size();
     int cols = maze[0].size();

     stack<pair<int, int>> dfsStack;
     dfsStack.push({0, 0});  // Start from the upper-left corner

   char prev_color = 'X';
     while (!dfsStack.empty()) {
         auto current = dfsStack.top();
         int row = current.first;
         int col = current.second;
         dfsStack.pop();

         cout << "Exploring: " << row + 1 << " " << col + 1 << " - Color: " << maze[row][col].color << ", Direction: [" << maze[row][col].direction << "]" << endl;  // +1 to convert to 1-based indexing


         // Check if the current position is within the maze boundaries and not visited
         if (row >= 0 && row < rows && col >= 0 && col < cols && !visited[row][col]) {
             // Push the current position to the resultPath and colorStack

           cout << "prev: " << prev_color;
           cout << "cur: " << maze[row][col].color;

           if(prev_color != maze[row][col].color){
             colorStack.push(maze[row][col].color);
             resultPath.push_back({row, col});
           }

             // Check if the bull's-eye is reached
             if (maze[row][col].color == 'O') {
                 cout << "Reached the bull's-eye!" << endl;
                 return true;
             }

           prev_color = colorStack.top();

             // Mark the current position as visited
             visited[row][col] = true;

             // Determine the next position based on the arrow direction
             cout << "Current direction: [" << maze[row][col].direction << "]" << endl;

             int nextRow = row, nextCol = col;
             if (maze[row][col].direction == "N") { nextRow--; }
             else if (maze[row][col].direction == "E") { nextCol++; }
             else if (maze[row][col].direction == "S") { nextRow++; }
             else if (maze[row][col].direction == "W") { nextCol--; }
             else if (maze[row][col].direction == "NE") { nextRow--; nextCol++; }
             else if (maze[row][col].direction == "SE") { nextRow++; nextCol++; }
             else if (maze[row][col].direction == "SW") { nextRow++; nextCol--; }
             else if (maze[row][col].direction == "NW") { nextRow--; nextCol--; }

             cout << "Moving to: " << nextRow + 1 << " " << nextCol + 1 << endl;  // +1 to convert to 1-based indexing

             // Push the next position to the stack for exploration
             dfsStack.push({nextRow, nextCol});
         }
       else{
             // If the current position is out of bounds or already visited, backtrack
             visited[row][col] = false;
             colorStack.pop();
     }
     }

     return false;
 }


 // Function to find a path from the upper left to the bull's-eye
 vector<pair<int, int>> findPath(const vector<vector<Vertex>>& maze) {
     int rows = maze.size();
     int cols = maze[0].size();

     vector<vector<bool>> visited(rows, vector<bool>(cols, false));
     vector<pair<int, int>> resultPath;
     stack<char> colorStack;

     // Start DFS from the upper-left corner (red arrow)
     findPathDFS(maze, visited, resultPath, colorStack);

     return resultPath;
 }

 // Function to write the output to the file
 void writeOutput(const string& filename, const vector<pair<int, int>>& path, const vector<vector<Vertex>>& maze) {
     ofstream file(filename);

     // If the path is empty, print "No solution"
     if (path.empty()) {
         file << "No solution" << endl;
         return;
     }


     // Print the sequence of moves

     int moveCount = 1;
     string moveDirection;

     for (size_t i = 1; i < path.size(); ++i) {
       cout << path[i].first << "," << path[i].second << endl;
         int row = path[i].first;
         int col = path[i].second;

        moveDirection = maze[row][col].direction;

        if(moveDirection != maze[path[i+1].first][path[i+1].second].direction){
           file << moveCount << moveDirection << " ";
        }
         else { 
             // Continue the current move
             moveCount++;

         }
     }
     // Print the last move
     file << moveCount << moveDirection << endl;
 }

 int main() {
     // Read the maze from the input file
     vector<vector<Vertex>> maze = readMaze("input.txt");

     // Find the path to the bull's-eye
     vector<pair<int, int>> path = findPath(maze);

     // Write the path to the output file
     writeOutput("output.txt", path, maze);

     return 0;
 }
