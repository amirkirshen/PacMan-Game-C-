//ID_1: 322437815
//ID_2: 208930586
#include "Ghost.h"

Ghost::Ghost(const int x, const int y, const int _dir, const int _color):
	Creature(0, 1, GHOST, x, y, _dir, LIGHTGREEN)
{
    setDir(LEFT);
	original = getPos();
    Creature::setPos(x, y);
}

Ghost::Ghost():
	Creature(2, 2, DOWN, GHOST, WHITE)
{
	original = getPos();
}

bool Ghost::move(Board &board, int dir, position pacPos, bool colorful, bool isSmart)
{
	bool flag;
	int old_x = getPos().getPositionX(), old_y = getPos().getPositionY();
    if (dir == -1) chooseDir(board, pacPos, isSmart);
    //active generic move
	flag = Creature::move(board, colorful);

    //return if succeeded to move
	return flag;
}


//move and draw ghost
//choose dir if not given (dir = -1)
void Ghost::moveAndDraw(Board& board, int dir, position pacPos, bool colorful, bool _isSmart)
{
    bool flag;
    int old_x = getPos().getPositionX(), old_y = getPos().getPositionY();
    isSmart = _isSmart;

    flag = Ghost::move(board, dir, pacPos, colorful, _isSmart);

    //if succeeded - delete the previous place and print on the new one
    if (flag == true)
        draw(old_x, old_y, board, colorful);
}


//the func set new dir accordind to ghost level
void Ghost::chooseDir(Board& board, position pacPos, const bool flag)
{
    bool isSmart = true;
    static int numOfRandomMoves, numOfSmartMoves;
    switch (level)
    {
    case NOVICE:
        numOfRandomMoves++;
        moveRandom(board, numOfRandomMoves, 20);
        break;
    case GOOD:
        numOfSmartMoves++;
        if (numOfSmartMoves >= 20 || !isSmart)
        {
            if (numOfRandomMoves == 0) setDir(rand() % 4 + 1);
            numOfRandomMoves++;
            moveRandom(board, numOfRandomMoves, 6);
            isSmart = false;
        }
        else
            if (flag == true)
                smartDirMove(board, pacPos);
        if (numOfRandomMoves >= 5)
        {
            isSmart = true;
            numOfSmartMoves = 0;
            numOfRandomMoves = 0;
        }
        break;
    case BEST:
        if (flag == true)
            smartDirMove(board, pacPos);
        break;
    default:
        cout << "Ghost level problam - call amir or roni";
        exit(1);
        break;
    }
}


//set direction to catch the pacman
void Ghost::smartDirMove(Board& board, position pacPos)
{

    int xPacPos = pacPos.getPositionX(), yPacPOs = pacPos.getPositionY();
    int xGhostPos = getPos().getPositionX(), yGhostPos = getPos().getPositionY();

    isSmart = false;
    vector<vector<bool>> visit(getNumOfLines() + 1, vector<bool>(getSizeOfLine() + 1, false));
    position newPos = BFS(board, visit, yPacPOs, xPacPos);

    //newPos is to the left
    if (newPos.getPositionX() == xGhostPos - 1) setDir(LEFT);

    //newPos is to the right
    else if (newPos.getPositionX() == xGhostPos + 1) setDir(RIGHT);

    //newPos is to the up
    else if (newPos.getPositionY() == yGhostPos - 1) setDir(UP);

    //newPos is to the down
    else setDir(DOWN);
}

bool Ghost::isValidStep(const vector<vector<bool>> &visit, int &row, int &col, Board& board)
{
    // If cell is bounds
    if (row > getNumOfLines() || row < 0 || col > getSizeOfLine() || col < 0)
        return false;

    // If cell is bounds
    if (board.GetCoordinate(col, row) == BOUNDARY || board.GetCoordinate(col, row) == TUNNEL)
        return false;

    // If cell is already visited
    if (visit[row][col])
        return false;

    // Otherwise
    return true;
}

//Generl valid step test - not based on visit bool table (not BFS!)
bool Ghost::isValidStep(int row, int col, Board& board)
{
    // If cell is bounds
    if (row >= getNumOfLines() || col >= (getSizeOfLine() - 2))
        return false;

    // If cell is bounds
    if (row == 0 || col == 0 || board.GetCoordinate(col, row) == BOUNDARY || board.GetCoordinate(col, row) == TUNNEL)
        return false;


    // Otherwise
    return true;
}


position Ghost::BFS(Board &board, vector<vector<bool>> visit, int row, int col)
{
    int test = 0;
    position ghostPos = getPos();
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };
    // Stores indices of the matrix cells
    queue<position> q;
    int xGhost = getPos().getPositionX();
    int yGhost = getPos().getPositionY();
    // Mark the starting cell as visited and push it into the queue
    q.push(position{ col, row});
    visit[row][col] = true;

    // Iterate while the queue is not empty
    while (!q.empty()) {

        position cell = q.front();
        int x = cell.getPositionX();
        int y = cell.getPositionY();

        q.pop();

        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {
            int adjy = y + dRow[i];
            int adjx = x + dCol[i];
            if (position(adjx, adjy) == ghostPos)
                return position(x, y);
            else if (isValidStep(visit, adjy, adjx, board)) {
                q.push({ adjx, adjy });
                visit[adjy][adjx] = true;
            }
        }
    }

    // if short way has not found - return the curr position
    // the ghost direction will be down
    return getPos();
}

//set the curr position to the original position
void Ghost::reset()
{
    this->setPos(original.getPositionX(), original.getPositionY());
}

//moving the creature in random direction
//change direction after 'num' steps
void Ghost::moveRandom(Board board, int &numOfRandomMoves, int num)
{
    if (numOfRandomMoves >= num)
    {
        setDir(rand() % 4 + 1);
        numOfRandomMoves = 0;
    }
    LegalmoveRandom(board, numOfRandomMoves);
}

void Ghost::LegalmoveRandom(Board board, int &numOfRandomMoves)
//get a direction and update it in object if not legal
{
    bool flag = false;
    position newPos;
    setDir(getDir());
    do
    {
        newPos = nextStep(getDir());
        if (!(flag = isValidStep(newPos.getPositionY(), newPos.getPositionX(), board)))
        {
            setDir(rand() % 4 + 1);
            numOfRandomMoves = 1; //if got stuck in wall - random again and reset counter
        }
    } while (!flag);
}

void Ghost::setLevel(const int num)
{
    level = num;
}

//return the new pos according to curr position and direction
position Ghost::nextStep (int dir)
{
    switch (dir)
    {
    case UP:
        return position(getPos().getPositionX(), getPos().getPositionY() - 1);
        break;
    case DOWN:
        return position(getPos().getPositionX(), getPos().getPositionY() + 1);
        break;
    case LEFT:
        return position(getPos().getPositionX() - 1, getPos().getPositionY());
        break;
    case RIGHT:
        return position(getPos().getPositionX() + 1, getPos().getPositionY());
        break;
    default:
        break;
    }
    //in case of bug (illegal direction) - return curr position
    return position(getPos().getPositionX() , getPos().getPositionY());
}


