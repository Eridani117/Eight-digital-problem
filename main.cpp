#include <bits/stdc++.h>

using namespace std;

vector<string> blankMovedPosition(int blank_position, const string &position);

pair<string, string> getPosition();

pair<int, int> getInversions(string beginPosition, string endPosition);

void BFS(const pair<string, string> &position);
void aStar(const pair<string, string> &position);
int main() {

  pair<string, string> position = getPosition();
  BFS(position);
  aStar(position);
  return 0;
}
///
/// \param position
void aStar(const pair<string, string> &position) {
  //todo aStar
}
///
/// \param position
void BFS(const pair<string, string> &position) {

  string beginPosition = position.first, endPosition = position.second;
  queue<string> queue;
  int num = 1;
  int depth = 1;
  map<string, pair<int, int>> map;
  map[beginPosition] = {num, depth};
  string cur = beginPosition;
  vector<string> retMove;

  queue.push(beginPosition);
  bool solved = false;
  while (!solved) {
//    if (queue.size() % 100 == 0) {
//      cout << queue.size() << endl;
//    }
    if (queue.empty()) {
      cout << map[endPosition].first << " " << map[endPosition].second << endl;
      cout << "No solution";
    }
    cur = queue.front();
    depth = map[cur].second;
//    cout << depth << endl;
    queue.pop();

    for (int i = 0; i < cur.length(); i++) {
      if (cur[i] == '0') {
        retMove = blankMovedPosition(i, cur);
        break;
      }
    }
    for (const auto &it:retMove) {
      if (map.count(it) == 0) {
        map[it] = {++num, depth + 1};
        queue.push(it);
      }
    }
    if (count(retMove.begin(), retMove.end(), endPosition)) {
      solved = true;
    }
  }

  cout << "count:" << map[cur].first << endl << "depth:" << map[cur].second << endl;

}

///
/// \return position
pair<string, string> getPosition() {
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
  cout << beginPosition[0] << " " << beginPosition[1] << " " << beginPosition[2] << endl;
  cout << beginPosition[3] << " " << beginPosition[4] << " " << beginPosition[5] << endl;
  cout << beginPosition[6] << " " << beginPosition[7] << " " << beginPosition[8] << endl;
  cout << "endPosition" << endl;
  cout << endPosition[0] << " " << endPosition[1] << " " << endPosition[2] << endl;
  cout << endPosition[3] << " " << endPosition[4] << " " << endPosition[5] << endl;
  cout << endPosition[6] << " " << endPosition[7] << " " << endPosition[8] << endl;

  return {beginPosition, endPosition};
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


