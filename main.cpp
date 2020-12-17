#include <bits/stdc++.h>

using namespace std;

struct positions {
  string begin_position;
  string end_position;
};
struct info{
  int num;
  int depth;
  string father;
};
vector<string> blankMovedPosition(int blank_position, const string &position);
positions getPositions();
pair<int, int> getInversions(string beginPosition, string endPosition);
void BFS(const positions &positions);
void aStar_diff(const positions &positions);
void showPosition(string position);
void showPath(string &end_position, map<string, info> &map);
map<string, info> BFS_map;
map<string, info> a_star_map;

int BFS_NUM;
int BFS_DEPTH;
int A_STAR_NUM;
int A_STAR_DEPTH;
int main() {

  positions positions = getPositions();
  BFS(positions);
  aStar_diff(positions);

  cout << "\nBFS PATH:================================\n" << endl;
  showPath(positions.end_position, BFS_map);
  cout << "\na_star_diff PATH:================================\n" << endl;
  showPath(positions.end_position, a_star_map);


  cout << "BFS_num:" << BFS_NUM << endl << "BFS_depth:" << BFS_DEPTH << endl;
  cout << "A_STAR_num:" << A_STAR_NUM << endl << "A_STAR_depth:" << A_STAR_DEPTH << endl;
  return 0;
}

void showPath(string &end_position, map<string, info> &map) {

  string cur = end_position;
  vector<string> path;
  while (cur != "END") {
    path.push_back(cur);
    cur = map[cur].father;
  }

  for (int i = (int) path.size() - 1; i >= 0; i--) {
    cout << "num:" << map[path[i]].num   << "  depth:" << map[path[i]].depth << endl;
    showPosition(path[i]);
    cout << endl;
  }

}

string CMP_POSITION;

struct cmp {

  bool operator()(string a, string b) {
    int dif_a = 0;
    for (int i = 0; i < a.length(); i++) {
      if (a[i] != CMP_POSITION[i]) {
        dif_a++;
      }
    }
    int dif_b = 0;
    for (int i = 0; i < b.length(); i++) {
      if (b[i] != CMP_POSITION[i]) {
        dif_b++;
      }
    }

    int g_a = a_star_map[a].depth;
    int g_b = a_star_map[b].depth;
    if (g_a + dif_a > g_b + dif_b) {
      return true;
    } else {
      return false;
    }

  }
};

///
/// \param positions
void aStar_diff(const positions &positions) {
  string beginPosition = positions.begin_position, endPosition = positions.end_position;
  CMP_POSITION = endPosition;
  priority_queue<string, vector<string>, cmp> queue;
  int num = 1;
  int depth = 1;
  a_star_map[beginPosition] = {num, depth, "END"};
  string cur = beginPosition;
  vector<string> retMove;

  queue.push(beginPosition);
  bool solved = false;
  while (!solved) {
    if (queue.empty()) {
      cout << "No solution" << endl;
    }
    cur = queue.top();
    depth = a_star_map[cur].depth;
//    cout << depth << endl;
    queue.pop();

    for (int i = 0; i < cur.length(); i++) {
      if (cur[i] == '0') {
        retMove = blankMovedPosition(i, cur);
        break;
      }
    }
    for (const auto &it:retMove) {
      if (a_star_map.count(it) == 0) {
        a_star_map[it] = {++num, depth + 1, cur};
        queue.push(it);
      }
    }
    if (count(retMove.begin(), retMove.end(), endPosition)) {
      solved = true;
    }
  }
  A_STAR_NUM = a_star_map[cur].num;
  A_STAR_DEPTH = a_star_map[cur].depth;
  cout << "num:" << A_STAR_NUM << endl << "depth:" << A_STAR_DEPTH << endl;
}

///
/// \param positions
void BFS(const positions &positions) {

  string beginPosition = positions.begin_position, endPosition = positions.end_position;
  queue<string> queue;
  int num = 1;
  int depth = 1;

  BFS_map[beginPosition] = {num, depth, "END"};
  string cur = beginPosition;
  vector<string> retMove;

  queue.push(beginPosition);
  bool solved = false;
  while (!solved) {
//    if (queue.size() % 100 == 0) {
//      cout << queue.size() << endl;
//    }
    if (queue.empty()) {
      cout << BFS_map[endPosition].num << " " << BFS_map[endPosition].depth << endl;
      cout << "No solution" << endl;
    }
    cur = queue.front();
    depth = BFS_map[cur].depth;
//    cout << depth << endl;
    queue.pop();

    for (int i = 0; i < cur.length(); i++) {
      if (cur[i] == '0') {
        retMove = blankMovedPosition(i, cur);
        break;
      }
    }
    for (const auto &it:retMove) {
      if (BFS_map.count(it) == 0) {
        BFS_map[it] = {++num, depth + 1, cur};
        queue.push(it);
      }
    }
    if (count(retMove.begin(), retMove.end(), endPosition)) {
      solved = true;
    }
  }
  BFS_NUM = BFS_map[cur].num;
  BFS_DEPTH = BFS_map[cur].depth;
  cout << "count:" << BFS_NUM << endl << "depth:" << BFS_DEPTH << endl;

}

///
/// \return position
positions getPositions() {
  string beginPosition, endPosition;
  bool getResolvedPosition = false;

  while (!getResolvedPosition) {
    vector<int> tmp_array = {1, 2, 3, 4, 5, 6, 7, 8};
    //get random seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    stringstream ss;
    //shuffle to string without 0
    shuffle(tmp_array.begin(), tmp_array.end(), std::default_random_engine(seed));
    copy(tmp_array.begin(), tmp_array.end(), ostream_iterator<int>(ss, ""));
    endPosition = ss.str();
    endPosition.insert(endPosition.begin() + 4, '0');

    //shuffle to string with 0
    ss.str("");
    tmp_array.push_back(0);
    shuffle(tmp_array.begin(), tmp_array.end(), std::default_random_engine(seed));
    copy(tmp_array.begin(), tmp_array.end(), ostream_iterator<int>(ss, ""));
    beginPosition = ss.str();

    //get Inversions
    pair<int, int> inversions = getInversions(beginPosition, endPosition);
    int beginInversions = inversions.first, endInversions = inversions.second;

    //check Inversions
    if (beginInversions % 2 == endInversions % 2) {
      getResolvedPosition = true;
    }
  }

  cout << "beginPosition:" << endl;
  showPosition(beginPosition);
  cout << "endPosition" << endl;
  showPosition(endPosition);

  return {beginPosition, endPosition};
}

void showPosition(string position) {
  cout << position[0] << " " << position[1] << " " << position[2] << endl;
  cout << position[3] << " " << position[4] << " " << position[5] << endl;
  cout << position[6] << " " << position[7] << " " << position[8] << endl;
}

///
/// \param beginPosition
/// \param endPosition
/// \return Inversions 逆序数
pair<int, int> getInversions(string beginPosition, string endPosition) {
  int beginInversions = 0, endInversions = 0;

  for (int i = 0; i < beginPosition.length(); i++) {
    for (int j = i + 1; j < beginPosition.length(); j++) {

      if (beginPosition[i] > beginPosition[j] && beginPosition[i] != '0' && beginPosition[j] != '0') {
        beginInversions++;
      }

      if (endPosition[i] > endPosition[j] && endPosition[i] != '0' && endPosition[j] != '0') {
        endInversions++;
      }
    }
  }
  return {beginInversions, endInversions};
}

///
/// \param blank_position
/// \param position
/// \return blankMovedPositions
vector<string> blankMovedPosition(int blank_position, const string &position) {
  int i = blank_position;
  vector<string> ret;
  string pos;
  if (i == 0) {
    //move_right
    pos = position;
    swap(pos[0], pos[1]);
    ret.push_back(pos);
    //move_down
    pos = position;
    swap(pos[0], pos[3]);
    ret.push_back(pos);
  } else if (i == 1) {
    //move_left
    pos = position;
    swap(pos[1], pos[0]);
    ret.push_back(pos);
    //move_down
    pos = position;
    swap(pos[1], pos[4]);
    ret.push_back(pos);
    //move_right
    pos = position;
    swap(pos[1], pos[2]);
    ret.push_back(pos);
  } else if (i == 2) {
    //move_left
    pos = position;
    swap(pos[2], pos[1]);
    ret.push_back(pos);
    //move_down
    pos = position;
    swap(pos[2], pos[5]);
    ret.push_back(pos);
  } else if (i == 3) {
    //move_up
    pos = position;
    swap(pos[3], pos[0]);
    ret.push_back(pos);
    //move_right
    pos = position;
    swap(pos[3], pos[4]);
    ret.push_back(pos);
    //move_down
    pos = position;
    swap(pos[3], pos[6]);
    ret.push_back(pos);
  } else if (i == 4) {
    //move_up
    pos = position;
    swap(pos[4], pos[1]);
    ret.push_back(pos);
    //move_left
    pos = position;
    swap(pos[4], pos[3]);
    ret.push_back(pos);
    //move_right
    pos = position;
    swap(pos[4], pos[5]);
    ret.push_back(pos);
    //move_down
    pos = position;
    swap(pos[4], pos[7]);
    ret.push_back(pos);
  } else if (i == 5) {
    //move_up
    pos = position;
    swap(pos[5], pos[2]);
    ret.push_back(pos);
    //move_left
    pos = position;
    swap(pos[5], pos[4]);
    ret.push_back(pos);
    //move_down
    pos = position;
    swap(pos[5], pos[8]);
    ret.push_back(pos);
  } else if (i == 6) {
    //move_up
    pos = position;
    swap(pos[6], pos[3]);
    ret.push_back(pos);
    //move_right
    pos = position;
    swap(pos[6], pos[7]);
    ret.push_back(pos);
  } else if (i == 7) {
    //move_up
    pos = position;
    swap(pos[7], pos[4]);
    ret.push_back(pos);
    //move_left
    pos = position;
    swap(pos[7], pos[6]);
    ret.push_back(pos);
    //move_right
    pos = position;
    swap(pos[7], pos[8]);
    ret.push_back(pos);
  } else if (i == 8) {
    //move_up
    pos = position;
    swap(pos[8], pos[5]);
    ret.push_back(pos);
    //move_left
    pos = position;
    swap(pos[8], pos[7]);
    ret.push_back(pos);
  }

  return ret;
}


