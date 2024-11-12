/*//Pedro Tobalina & Jorge Polo
#include<iostream>
#include<vector>
using namespace std;

struct activity {
	int start;
	int finish;
	int period;
	bool isIn(activity ac, int t) {
		if (period == -1 && ac.period == -1) {
			if (ac.finish <= start || ac.start >= finish)
				return false;
			else
				return true;
		}
		else if (period == -1 && ac.period > 0) {
			int x = (start - ac.start)/ac.period;

			activity ac2; ac2.start = ac.start+ ac.period * x; ac2.finish = ac.finish + ac.period * x; ac2.period = -1;
			activity ac3; ac3.start = ac.start + ac.period *(1+ x); ac3.finish = ac.finish + ac.period * (x+1); ac3.period = -1;

			if (isIn(ac2, t) || isIn(ac3, t))
				return true;
			else
				return false;
		}
		else if (period > 0 && ac.period == -1) {
			int x = (ac.start - start)/period;

			activity ac2; ac2.start = start + period * x; ac2.finish = finish + period * x; ac2.period = -1;
			activity ac3; ac3.start = start + period * (x+1); ac3.finish = finish + period * (x+1); ac3.period = -1;

			if (ac.isIn(ac2, t) || ac.isIn(ac3, t))
				return true;
			else
				return false;
		}
		else {//hay que jugar con la diferencia del periodo y ver si la diferencia puede hace interseccion en menos de t
			bool correct = false;
			if (period == ac.period) {
				if (ac.start < start) {
					int x = (start - ac.start) / period;
					activity ac2; ac2.start = ac.start + ac.period * x; ac2.finish = ac.finish + ac.period * x; ac2.period = -1;
					if (isIn(ac2, t))
						correct = true;
				}
				else {
					int x = (ac.start - start) / period;
					activity ac2; ac2.start = start + period * x; ac2.finish = finish + period * x; ac2.period = -1;
					if (ac.isIn(ac2, t))
						correct = true;
				}
			}
			else {
				int index = abs(ac.period - period);
			}
		}
	}
};

int main() {
	int n, m, t;
	while (cin >> n >> m >> t) {
		vector<activity> activitys(n + m);
		bool good = true;
		int start, finish;
		for (int i = 0; i < n; i++) {
			cin >> start>> finish;
			if (finish > t)
				finish = t;
			activitys[i].start = start; activitys[i].finish = finish; activitys[i].period = -1;
		}
		int periocity;
		for (int i = 0; i < m; i++) {
			cin >> start >> finish >> periocity;
			activitys[i + n].start = start; activitys[i + n].finish = finish; activitys[i + n].period = periocity;
		}
		for (int i = 0; i < activitys.size() && good; i++) {
			for (int j = i + 1; j < activitys.size() && good; j++) {
				if (activitys[i].isIn(activitys[j], t))
					good = false;
			}
		}
		if (good)
			cout << "NO" << endl;
		else
			cout << "SI" << endl;
	}
	return 0;
}*/