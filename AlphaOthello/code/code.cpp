#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>

int player;
const int SIZE = 8;
const int DEPTH = 5;
int dx[4] = {1, -1, 1, -1};
int dy[4] = {1, 1, -1, -1};

struct Point {
    int x, y;
	Point() : Point(0, 0) {}
	Point(int x, int y) : x(x), y(y) {}
	bool operator==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Point& rhs) const {
		return !operator==(rhs);
	}
	Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
};
class OthelloBoard {
public:
    enum SPOT_STATE {
        EMPTY = 0,
        BLACK = 1,
        WHITE = 2
    };
    static const int SIZE = 8;
    const std::array<Point, 8> directions{{
        Point(-1, -1), Point(-1, 0), Point(-1, 1), //up
        Point(0, -1), /*{0, 0}, */Point(0, 1), //
        Point(1, -1), Point(1, 0), Point(1, 1) //down
    }};
    std::array<std::array<int, SIZE>, SIZE> board_;
    std::vector<Point> next_valid_spots_;
    std::array<int, 3> disc_count;
    int cur_player;
    bool done;
    int winner;
private:
    int get_next_player(int player) const {
        return 3 - player;
    }
    bool is_spot_on_board(Point p) const {
        return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
    }
    int get_disc(Point p) const {
        return board_[p.x][p.y];
    }
    void set_disc(Point p, int disc) {
        board_[p.x][p.y] = disc;
    }
    bool is_disc_at(Point p, int disc) const {
        if (!is_spot_on_board(p))
            return false;
        if (get_disc(p) != disc)
            return false;
        return true;
    }
    bool is_spot_valid(Point center) const {
        if (get_disc(center) != EMPTY)
            return false;
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, cur_player))
                    return true;
                p = p + dir;
            }
        }
        return false;
    }
    void flip_discs(Point center) {
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            std::vector<Point> discs({p});
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, cur_player)) {
                    for (Point s: discs) {
                        set_disc(s, cur_player);
                    }
                    disc_count[cur_player] += discs.size();
                    disc_count[get_next_player(cur_player)] -= discs.size();
                    break;
                }
                discs.push_back(p);
                p = p + dir;
            }
        }
    }
public:
    OthelloBoard() {
        reset();
    }
    void reset() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board_[i][j] = EMPTY;
            }
        }
        board_[3][4] = board_[4][3] = BLACK;
        board_[3][3] = board_[4][4] = WHITE;
        cur_player = BLACK;
        disc_count[EMPTY] = SIZE * SIZE - 4;
        disc_count[BLACK] = 2;
        disc_count[WHITE] = 2;
        next_valid_spots_ = get_valid_spots();
        done = false;
        winner = -1;
    }
    std::vector<Point> get_valid_spots() const {
        std::vector<Point> valid_spots;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                Point p = Point(i, j);
                if (board_[i][j] != EMPTY)
                    continue;
                if (is_spot_valid(p))
                    valid_spots.push_back(p);
            }
        }
        return valid_spots;
    }
    bool put_disc(Point p) {
        if(!is_spot_valid(p)) {
            winner = get_next_player(cur_player);
            done = true;
            return false;
        }
        set_disc(p, cur_player);
        disc_count[cur_player]++;
        disc_count[EMPTY]--;
        flip_discs(p);
        // Give control to the other player.
        cur_player = get_next_player(cur_player);
        next_valid_spots_ = get_valid_spots();
        // Check Win
        if (next_valid_spots_.size() == 0) {
            cur_player = get_next_player(cur_player);
            next_valid_spots_ = get_valid_spots();
            if (next_valid_spots_.size() == 0) {
                // Game ends
                done = true;
                int white_discs = disc_count[WHITE];
                int black_discs = disc_count[BLACK];
                if (white_discs == black_discs) winner = EMPTY;
                else if (black_discs > white_discs) winner = BLACK;
                else winner = WHITE;
            }
        }
        return true;
    }
    int state_value();
};


std::array<std::array<int, SIZE>, SIZE> board;
std::vector<Point> next_valid_spots;

int OthelloBoard::state_value(){
    int state_value = 0;
    //normal + row / col = 1 . 6 (X) + row / col = 0 . 7 (O)
    for(int i = 0 ; i < SIZE ; i ++){
        for(int j = 0 ; j < SIZE ; j ++){
            if(board_[i][j] == player){
                state_value += 3;
                if(i % 5 == 1 || j % 5 == 1) state_value -= 10;
                if(i % 5 == 1 && j % 5 == 1) state_value -= 50;
                if(i % 7 == 0 || j % 7 == 0) state_value += 200;
                if(i % 7 == 0 && j % 7 == 0){
                    state_value += 500;
                    int conner = 2 * (i / 7) + (j / 7);
                    for(int k = 1 ; k < SIZE - 1 ; k++){
                        if(board_[i + k * dy[conner]][j] == board_[i][j])
                            state_value += 20;
                        else break;
                    }
                    for(int k = 1 ; k < SIZE - 1 ; k++){
                        if(board_[i][j + k * dx[conner]] == board_[i][j])
                            state_value += 20;
                        else break;
                    }
                }
            }
            else if(board_[i][j] == 3 - player){
                state_value -= 3;
                if(i % 5 == 1 || j % 5 == 1) state_value += 10;
                if(i % 5 == 1 && j % 5 == 1) state_value += 50;
                if(i % 7 == 0 || j % 7 == 0) state_value -= 200;
                if(i % 7 == 0 && j % 7 == 0){
                    state_value -= 500;
                    int conner = 2 * (i / 7) + (j / 7);
                    for(int k = 1 ; k < SIZE - 1 ; k++){
                        if(board_[i + k * dy[conner]][j] == board_[i][j])
                            state_value -= 20;
                        else break;
                    }
                    for(int k = 1 ; k < SIZE - 1 ; k++){
                        if(board_[i][j + k * dx[conner]] == board_[i][j])
                            state_value -= 20;
                        else break;
                    }
                }
            }
        }
    }
    state_value -= 5 * next_valid_spots_.size();
    return state_value;
}

int choose(OthelloBoard* now, int depth, int alpha, int beta){
    if(depth == 0) return now->state_value();
    if(now->next_valid_spots_.size() == 0){
        if(now->cur_player == player) return now->state_value() - 50;
        else if(now->cur_player == 3 - player) return now->state_value() + 50;
    }

    int n_valid_spots = now->next_valid_spots_.size();
    int index = 0, temp_value, value;

    if(now->cur_player == player){ //max
        value = -2e8;
        for(int i = 0 ; i < n_valid_spots ; i++){
            OthelloBoard next_board;
            next_board.cur_player = now->cur_player;
            next_board.board_ = now->board_;
            next_board.put_disc(now->next_valid_spots_[i]);

            temp_value = choose(&next_board, depth - 1, alpha, beta);
            if(temp_value > value){
                value = temp_value;
                index = i;
            }
            alpha = std::max(alpha, value);
            if(alpha >= beta) break;
        }
        if(depth == DEPTH) return index;  //end
        return value;
    }
    else{  //mini
        value = 2e8;
        for(int i = 0 ; i < n_valid_spots ; i++){
            OthelloBoard next_board;
            next_board.cur_player = now->cur_player;
            next_board.board_ = now->board_;
            next_board.put_disc(now->next_valid_spots_[i]);

            temp_value = choose(&next_board, depth - 1, alpha, beta);
            value = std::min(temp_value, value);
            beta = std::min(beta, value);
            if(beta <= alpha) break;
        }
        return value;
    }
}

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void read_valid_spots(std::ifstream& fin) {
    int n_valid_spots;
    fin >> n_valid_spots;
    int x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        fin >> x >> y;
        next_valid_spots.push_back({x, y});
    }
}

void write_valid_spot(std::ofstream& fout) {
    /*int n_valid_spots = next_valid_spots.size();
    srand(time(NULL));
    // Choose random spot. (Not random uniform here)
    */
    OthelloBoard Board;
    Board.board_ = board;
    Board.cur_player = player;
    Board.next_valid_spots_ = next_valid_spots;
    int index = choose(&Board, DEPTH, -2e8, 2e8);
    Point p = next_valid_spots[index];
    // Remember to flush the output to ensure the last action is written to file.
    fout << p.x << " " << p.y << std::endl;
    fout.flush();
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    read_valid_spots(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}