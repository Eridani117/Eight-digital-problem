#include <bits/stdc++.h>

using namespace std;

vector<string> blankMove(int i, const string &pos);

int main() {

  string beginPosition, endPosition;

  while (true) {
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
    int beginInversions = 0, endInversions = 0;

    for (int i = 0; i < beginPosition.length(); i++) {
      for (int j = i + 1; j < beginPosition.length(); j++) {
//        cout << i << "  " << j << endl;
        if (beginPosition[i] > beginPosition[j] && beginPosition[i] != '0' && beginPosition[j] != '0') {

          beginInversions++;
        }
        if (endPosition[i] > endPosition[j] && endPosition[i] != '0' && endPosition[j] != '0') {
          endInversions++;
        }
      }
    }

    //check Inversions
    if (beginInversions % 2 == endInversions % 2) {
//      cout << beginInversions << endl << endInversions << endl;
      break;
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

//  endPosition = "123804765";
//  beginPosition = "203184765";
  queue<string> queue;
  int num = 1;
  int depth = 1;
  map<string, pair<int, int>> map;
  map[beginPosition] = {num, depth};
  string cur = beginPosition;
  vector<string> retMove;

  queue.push(beginPosition);
  while (true) {
//    if (queue.size() % 100 == 0) {
//      cout << queue.size() << endl;
//    }
    if (queue.empty()) {
      cout << map[endPosition].first << " " << map[endPosition].second << endl;
      cout << "?????????";
      return -1;
    }
    cur = queue.front();
    depth = map[cur].second;
//    cout << depth << endl;
    queue.pop();

    for (int i = 0; i < cur.length(); i++) {
      if (cur[i] == '0') {
        retMove = blankMove(i, cur);
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
      break;
    }
  }

  cout << "count:" << map[cur].first << endl << "depth:" << map[cur].second << endl;
  return 0;
}
vector<string> blankMove(int i, const string &pos) {
  vector<string> ret;
  string tmp;
  if (i == 0) {
    //move_right
    tmp = pos;
    swap(tmp[0], tmp[1]);
    ret.push_back(tmp);
    //move_down
    tmp = pos;
    swap(tmp[0], tmp[3]);
    ret.push_back(tmp);
  } else if (i == 1) {
    //move_left
    tmp = pos;
    swap(tmp[1], tmp[0]);
    ret.push_back(tmp);
    //move_down
    tmp = pos;
    swap(tmp[1], tmp[4]);
    ret.push_back(tmp);
    //move_right
    tmp = pos;
    swap(tmp[1], tmp[2]);
    ret.push_back(tmp);
  } else if (i == 2) {
    //move_left
    tmp = pos;
    swap(tmp[2], tmp[1]);
    ret.push_back(tmp);
    //move_down
    tmp = pos;
    swap(tmp[2], tmp[5]);
    ret.push_back(tmp);
  } else if (i == 3) {
    //move_up
    tmp = pos;
    swap(tmp[3], tmp[0]);
    ret.push_back(tmp);
    //move_right
    tmp = pos;
    swap(tmp[3], tmp[4]);
    ret.push_back(tmp);
    //move_down
    tmp = pos;
    swap(tmp[3], tmp[6]);
    ret.push_back(tmp);
  } else if (i == 4) {
    //move_up
    tmp = pos;
    swap(tmp[4], tmp[1]);
    ret.push_back(tmp);
    //move_left
    tmp = pos;
    swap(tmp[4], tmp[3]);
    ret.push_back(tmp);
    //move_right
    tmp = pos;
    swap(tmp[4], tmp[5]);
    ret.push_back(tmp);
    //move_down
    tmp = pos;
    swap(tmp[4], tmp[7]);
    ret.push_back(tmp);
  } else if (i == 5) {
    //move_up
    tmp = pos;
    swap(tmp[5], tmp[2]);
    ret.push_back(tmp);
    //move_left
    tmp = pos;
    swap(tmp[5], tmp[4]);
    ret.push_back(tmp);
    //move_down
    tmp = pos;
    swap(tmp[5], tmp[8]);
    ret.push_back(tmp);
  } else if (i == 6) {
    //move_up
    tmp = pos;
    swap(tmp[6], tmp[3]);
    ret.push_back(tmp);
    //move_right
    tmp = pos;
    swap(tmp[6], tmp[7]);
    ret.push_back(tmp);
  } else if (i == 7) {
    //move_up
    tmp = pos;
    swap(tmp[7], tmp[4]);
    ret.push_back(tmp);
    //move_left
    tmp = pos;
    swap(tmp[7], tmp[6]);
    ret.push_back(tmp);
    //move_right
    tmp = pos;
    swap(tmp[7], tmp[8]);
    ret.push_back(tmp);
  } else if (i == 8) {
    //move_up
    tmp = pos;
    swap(tmp[8], tmp[5]);
    ret.push_back(tmp);
    //move_left
    tmp = pos;
    swap(tmp[8], tmp[7]);
    ret.push_back(tmp);
  }

  return ret;
}


