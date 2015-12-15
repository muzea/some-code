#ifndef BLOCK_1

namespace P1_1 {
	int recursive(int n);
	int tail_recursive(int n);
	int _tail_recursive(int n, int ret);
	int formula_of_general_term(int n);

	int recursive(int n) {
		if (n == 1)
			return 2;
		return 2 * (n - 1) + recursive(n - 1);
	}
	int tail_recursive(int n) {
		return _tail_recursive(n, 0);
	}
	int _tail_recursive(int n, int ret) {
		if (n == 1)
			return ret + 2;
		return _tail_recursive(n - 1, ret + 2 * (n - 1));
	}
	int formula_of_general_term(int n) {
		return n*(n - 1) + 2;
	}
}

namespace P1_2 {
	unsigned int table[1001] = { 0,3,6,6 };
	unsigned int index = 3;
	int solve(int n) {
		while (index < n) {
			index++;
			table[index] = table[index - 1] + 2 * table[index - 2];
		}
		return table[n];
	}
}
namespace P1_3 {
	template<int N>
	int find(int(&A)[N], int x);
	template<typename T>
	int find(T A, int x);
	int _find(int* A, int x, int len);

	template<int N>
	int find(int(&A)[N], int x) {
		return _find(A, x, N);;
	}

	template<>
	int find<int*>(int* A, int x) {
		return _find(A, x, _msize(A) / sizeof(int));
	}
	int _find(int* A, int x, int len) {
		int i = 0;
		while (i != len && *(A + i) < x) ++i;
		return i != len&& *(A + i) == x ? i : -1;
	}

}
namespace P1_4 {
	void find(int a[], int n, int &i, int &j, int x) {
		int L = i, R = j;
		while (L <= R) {
			int mid = (L + R) / 2;
			if (*(a + mid) == x) {
				i = j = mid;
				return;
			}
			else if (*(a + mid) > x) {
				R = mid - 1;
			}
			else {
				L = mid + 1;
			}
		}
		std::swap(i, j);
	}
}
namespace P1_5 {
	void solve() {
		int GongJi, MuJi;
		cout << setw(10) << "公鸡" << setw(10) << "母鸡" << setw(10) << "小鸡" << endl;
		for (GongJi = 0; GongJi <= 33; GongJi++)
		{
			for (MuJi = 0; MuJi <= (100 - 3 * GongJi) / 2; MuJi++)
			{
				int XiaoJi = (100 - 3 * GongJi - 2 * MuJi) * 3;
				if (XiaoJi + GongJi + MuJi == 100) {
					cout << setw(10) << GongJi << setw(10) << MuJi << setw(10) << XiaoJi << endl;
				}
			}
		}
	}
}
namespace P1_6 {
#define CUBE(i) (i*i*i)
	static const int table[10] = { 0,1,CUBE(2),CUBE(3) ,CUBE(4) ,CUBE(5) ,CUBE(6),CUBE(7),CUBE(8),CUBE(9) };
#undef CUBE
	void solve() {
		for (int i = 100; i < 1000; i++)
		{
			if (i == table[i % 10] + table[i / 10 % 10] + table[i / 100]) {
				cout << i << endl;
			}
		}
	}
	template<int N>
	struct FUCK {
		enum {
			v = N * N * N
		};
	};

	template<int N>
	struct isNarcissistic {
		enum {
			result = N == ((FUCK<(N % 10)>::v) + (FUCK<(N / 10 % 10)>::v) + (FUCK<(N / 100)>::v))
		};
	};

	template<int N, bool IsNarcissistic>
	struct printIfNarcissistic {
		static inline void print() {}
	};
	template<int N>
	struct printIfNarcissistic<N, true> {
		static inline void print() {
			cout << N << endl;
		}
	};

	template<int N, int MAX>
	struct printNarcissistic {
		static inline void print()
		{
			printIfNarcissistic<N, isNarcissistic<N>::result>::print();
			printNarcissistic<N + 1, MAX>::print();
		}
	};
	template<int N>
	struct printNarcissistic<N, N> {
		static inline void print() {
			printIfNarcissistic<N, isNarcissistic<N>::result>::print();
		}
	};
}
namespace P1_7 {
	struct Point;
	struct Cube;
	double D_MAX = double(INT_MAX) + double(INT_MAX);
	vector<Point> vec;
	vector<Cube> store;
	vector<int> index(7, 0);

	struct Point {
		int x, y, z;
		Point(int _x = 0, int _y = 0, int _z = 0) : x(_x), y(_y), z(_z) {}
		Point operator-(const Point& p2) { return Point(this->x - p2.x, this->y - p2.y, this->z - p2.z); }
	};
	struct Cube {
		double r;
		Point p;
		Cube(double& _r, Point& _p) :r(_r), p(_p) {}
	};
	Point P1, P2;
	inline int GetV(Point& p) {
		return (p.x*p.y*p.z);
	}
	inline double GetLen(Point& p) {
		return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
	}
	double GetR(int i) {
		double ret = D_MAX;
		for (const Cube& S : store)
		{
			double r = GetLen(vec[i] - S.p) - S.r;
			if (r > 0) {
				ret = min(ret, r);
			}
		}
		if (ret == D_MAX && !store.empty()) {
			return 0;
		}
		else {
			ret = min(ret, double(abs(vec[i].x - P1.x)));
			ret = min(ret, double(abs(vec[i].y - P1.y)));
			ret = min(ret, double(abs(vec[i].z - P1.z)));
			ret = min(ret, double(abs(vec[i].x - P2.x)));
			ret = min(ret, double(abs(vec[i].y - P2.y)));
			ret = min(ret, double(abs(vec[i].z - P2.z)));
			return ret;
		}

	}
	const double C_PI = 1.3333333 * 3.141592653;
	void solve() {
		double G_sum = 0;
		vec.clear();
		store.clear();
		int n;
		cin >> n;
		index.resize(n);
		generate_n(index.begin(), n, []() ->int {
			static int i = 0;
			return (i++);
		});
		int x, y, z, i = 0;
		cin >> x >> y >> z;
		P1 = Point(x, y, z);
		cin >> x >> y >> z;
		P2 = Point(x, y, z);
		while (i != n) {
			cin >> x >> y >> z;
			vec.push_back(Point(x, y, z));
			++i;
		}
		double V_sum = 0;
		do {
			for (const int& i : index) {
				double r = GetR(i);
				store.push_back(Cube(r, vec[i]));
				V_sum = C_PI * r * r * r;
			}
			G_sum = max(G_sum, V_sum);
			store.clear();
		} while (next_permutation(index.begin(), index.end()));
		int T_V = abs(GetV(P1 - P2));
		T_V -= int(G_sum + 0.5);
		cout << T_V << endl;
	}
}
namespace P1_8 {
	inline int check(bool(&row)[9]);
	inline void C_cnt(bool(&row)[9], int(&cnt)[9]);
	bool table[10000][9] = { 0 };
	void solve() {
		int N;
		int cnt[9] = { 0 };
		cin >> N;
		int i = 0;
		int MAX = 0;
		while (i != N) {
			cin >> table[i][0] >> table[i][1] >> table[i][2] >> table[i][3] >> table[i][4]
				>> table[i][5] >> table[i][6] >> table[i][7] >> table[i][8];
			check(table[i]);
			C_cnt(table[i], cnt);
			++i;
		}
		int sum = 0;
		i = 0;
		while (i != 9)
		{
			if (cnt[i] > (N / 2))
			{
				sum += cnt[i];
			}
			else {
				int j = 0;
				while (j != N)
				{
					table[j][i] ^= 1;
					++j;
				}
				sum += N - cnt[i];
			}
			++i;
		}
		while (MAX < sum) {
			MAX = sum;
			i = 0;
			sum = 0;
			memset(cnt, 0, sizeof cnt);
			while (i != N)
			{
				sum += check(table[i]);
				C_cnt(table[i], cnt);
				++i;
			}
			if (MAX < sum)
			{
				MAX = sum;
				sum = 0;
				i = 0;
				while (i != 9)
				{
					if (cnt[i] >(N / 2))
					{
						sum += cnt[i];
					}
					else {
						int j = 0;
						while (j != N)
						{
							table[j][i] ^= 1;
							++j;
						}
						sum += N - cnt[i];
					}
					++i;
				}
			}
		}
		cout << sum << endl;
	}
	inline int check(bool(&row)[9]) {
		int cnt = 0;
		int i = 0;
		while (i != 9) {
			cnt += row[i];
			++i;
		}
		if (cnt < 5) {
			i = 0;
			while (i != 9)
			{
				row[i] ^= 1;
				++i;
			}
			cnt = 9 - cnt;
		}
		return cnt;
	}
	inline void C_cnt(bool(&row)[9], int(&cnt)[9]) {
		int i = 0;
		while (i != 9) {
			cnt[i] += row[i];
			++i;
		}
	}
}
namespace P1_9 {
	const int  MAX_N = 1000;
	pair<int, int> pre[MAX_N] = { { 0,1 } }, MAX(0, 1);
	int	B[MAX_N] = { 0 },
		E[MAX_N] = { 0 };
	void solve() {

		int N, i = 0, j;
		cin >> N;
		while (i != N)
		{
			cin >> B[i] >> E[i];
			++i;
		}
		i = 0;
		while (i != N)
		{
			j = 0;
			while (j != i)
			{
				if (E[j] <= B[i] && pre[j].second + 1 > pre[i].second) {
					if (pre[j].second + 1 > MAX.second) {
						MAX.second = pre[j].second + 1;
						MAX.first = i;
					}
					pre[i].first = j;
					pre[i].second = pre[j].second + 1;
				}
				++j;
			}
			++i;
		}

		stack<int> result;
		int index = MAX.first;
		while (index)
		{
			result.push(index);
			index = pre[index].first;
		}
		string output_buffer = "0";
		char itoa_buffer[10];

		while (!result.empty())
		{
			sprintf(itoa_buffer, " %d", result.top());
			output_buffer.append(itoa_buffer);
			result.pop();
		}
		cout << output_buffer << endl;
	}

}
namespace P1_10 {
	void solve() {
		int K = 0, M, N;
		while (cin >> K  && K)
		{
			cin >> M >> N;
			vector<int> range;
			int i = 1, num;
			cin >> num;
			while (i != M)
			{
				int temp;
				cin >> temp;
				if (temp - num - 1 > 0) {
					range.push_back(temp - num - 1);
				}
				num = temp;
				++i;
			}
			if (K - num - 1 > 0) {
				range.push_back(K - num - 1);
			}
			sort(range.begin(), range.end(), [](int a, int b) {return a > b; });
			int result = K;
			int cnt = 1;
			while (cnt != N) {
				result -= range[cnt - 1];
				++cnt;
			}
			cout << result << endl;
		}
	}
}

#endif

#ifndef BLOCK_2

namespace P2_1 {
	pair<int, int> find(vector<int>& vec, int begin, int len) {
		if (len == 2) {
			return make_pair(
				max(vec[begin], vec[begin + 1]),
				min(vec[begin], vec[begin + 1])
				);
		}
		if (len == 1) {
			return make_pair(
				vec[begin],
				vec[begin]
				);
		}
		int div = len / 2;
		pair<int, int> a = find(vec, begin, div)
			, b = find(vec, begin + div, len - div);
		return make_pair(max(a.first, b.first), min(a.second, b.second));
	}
	void solve() {
		vector<int> vec;
		int n, i = 0;
		cin >> n;
		while (i != n) {
			int value;
			cin >> value;
			vec.push_back(value);
			++i;
		}
		if (vec.size())
		{
			pair<int, int> ret = find(vec, 0, vec.size());
			cout << ret.first << ' ' << ret.second << endl;
		}
	}
}

namespace P2_2 {
	struct object {
		double i, V, W;
	};
	bool cmp(object& obj1, object& obj2) {
		return ((double(obj1.V) / double(obj1.W)) > (double(obj2.V) / double(obj2.W)));
	}
	bool cmp2(pair<int, int>& obj1, pair<int, int>& obj2) {
		return obj1.first < obj2.first;
	}
	void solve() {
		const int MAX_LEN = 1000;
		int w, n, i = 0;
		object obj[MAX_LEN];
		cin >> n >> w;
		while (i != n)
		{
			cin >> obj[i].V >> obj[i].W;
			obj[i].i = i + 1;
			++i;
		}
		i = 0;
		sort(obj, obj + n, cmp);
		vector<pair<int, int>> vec;
		while (w && i < n)
		{
			if (obj[i].W <= w) {
				w -= obj[i].W;
				vec.push_back(make_pair(int(obj[i].i), int(obj[i].W)));
				++i;
			}
			else {
				vec.push_back(make_pair(int(obj[i].i), w));
				w = 0;
			}
		}
		sort(vec.begin(), vec.end(), cmp2);
		for (auto& obj : vec)
		{
			cout << obj.first << ' ' << obj.second << endl;
		}
	}

}

namespace P2_3 {
	void solve() {
		char res[242] = { 0 };
		cin >> (res + 1);
		int s;
		cin >> s;
		char *slow = res + 1, *fast = res + 2;
		while (s && *fast)
		{

			while (s && *fast && *slow && *fast < *slow) {
				--s;
				--slow;
			}
			++slow;
			while (*fast == '0') ++fast;
			*slow = *fast;
			++fast;
		}
		while (s)
		{
			--slow;
			--s;
		}
		while (*fast)
		{
			++slow;
			*slow = *fast;
			++fast;
		}
		if (slow == res) {
			++slow;
			*slow = '0';
		}
		*(slow + 1) = 0;
		cout << (res + 1) << endl;
	}
}

#endif

#ifndef BLOCK_3
namespace P3_1 {
	enum {
		lose,
		win
	};
	int MAX = 10000;
	bool* dp = NULL;
	void solve() {
		dp = new bool[10001];
		fill(dp, dp + 10001, lose);
		int i = 1, end;
		cin >> end;
		while (i != end)
		{
			if (dp[i] == lose) {
				int j = i + 1, j_end = 2 * i;
				while (j <= j_end)
				{
					dp[j] = win;
					++j;
				}
			}
			++i;
		}
		cout << (dp[end] == win ? "win" : "lose") << endl;
		delete[] dp;
		dp = NULL;
	}
}

namespace P3_2 {
	int num_1, num_2, num_5;
	bool CanUse5() {
		if (num_2 > 1)
			return (num_1);
		else if (num_2)
			return (num_1 > 1);
		else
			return (num_1 > 3);
	}
	bool CanUse2() {
		return num_1;
	}
	void solve() {
		cin >> num_1 >> num_2 >> num_5;
		int ans = 0;
		if (CanUse5()) ans += num_5 * 5;
		if (CanUse2()) ans += num_2 * 2;
		ans += num_1;
		cout << ans << endl;
	}
}

namespace P3_3 {
	int* partition(int *first, int *last) {
		int pivot = *first;
		while (first < last) {
			while (first < last && pivot < *(--last));
			*first = *last;
			while (first < last && pivot > *(--first));
			*last = *first;
		}
		*first = pivot;
		return first;
	}
	void qsort(int *first, int *last) {
		if ((last - first) > 1) {
			int *mid = partition(first, last);
			qsort(first, mid);
			qsort(mid, last);
		}
	}
	bool binary_search(int *first, int *last, int val) {
		int *left = first, *right = last, *mid = first + (last - first) / 2;
		while (right >= left)
		{
			if (*mid > val) {
				right = mid - 1;
			}
			else if (*mid < val) {
				left = mid + 1;
			}
			else {
				return true;
			}
			mid = left + (right - left) / 2;
		}
		return false;
	}
}


namespace P3_4 {
	const int Max(105);

	char data[Max][Max];
	char Temp_Data[Max];

	int Check_Data(int a, int b)
	{
		for (int i = 0; i<a; i++)
			if (i != b&&!strstr(data[i], Temp_Data))
				return 0;
		return 1;
	}
	void solve() {
		int num;
		cin >> num;
		int n;
		while (num--&&cin >> n)
		{
			int state = 0, length = -1, i, a;
			for (i = 0; i<n; i++)
			{
				cin >> data[i];
				if (length == -1 || strlen(data[i])<length)
				{
					length = strlen(data[i]);
					state = i;
				}
			}
			int temp = length, flag = 0, j;
			while (temp)
			{
				for (i = 0; i + temp <= length; i++)
				{
					for (j = i, a = 0; a<temp; j++, a++)
						Temp_Data[a] = data[state][j];
					Temp_Data[a] = '\0';
					if (Check_Data(n, state))
					{
						flag = 1;
						break;
					}
				}
				if (flag)
					break;
				for (i = length - 1; i - temp >= -1; i--)
				{
					for (int j = i, a = 0; a<temp; j--, a++)
						Temp_Data[a] = data[state][j];
					Temp_Data[a] = '\0';
					if (Check_Data(n, state))
					{
						flag = 1;
						break;
					}
				}
				if (flag)
					break;
				temp--;
			}
			cout << temp << endl;
		}
	}
}

namespace P3_5 {
	int solve(int k, int m) {
		int END = m;
		static int Data[51][51] = { { 0, 1 },{ 0, 1 } };
		static int  i = 2;
		if (END == 1) {
			return 1;
		}
		while (i < END) {
			Data[i][1] = 1;
			int k = 1;
			while (i - k)
			{
				++k;
				int sum = 0;
				int j = 1;
				while (j <= k)
				{
					sum += Data[i - k][j];
					++j;
				}
				Data[i][k] = sum;
			}
			++i;
		}
		Data[END][1] = 1;
		return Data[END][k];
	}
}namespace P3_6 {
	inline int find_first_zero_bit(int& mask, int num) {
		int pos = 11;
		while ((pos - num) > 0)
		{
			if (((mask & (1 << pos)) || (mask & (1 << (pos - num - 1)))) == 0) {
				return pos;
			}
			--pos;
		}
		return -1;
	}
	void solve() {
		int mask,
			pos[8] = { 0 },
			data[5] = { 1,2,3,5,6 };
		pos[4] = 12;
		pos[7] = 13;
		int i;
		do {
			mask = 0;
			mask |= (((1 << (7 + 1)) + 1) << (pos[7] - 7 - 1));
			mask |= (((1 << (4 + 1)) + 1) << (pos[4] - 4 - 1));
			i = 0;
			while (i != 5)
			{
				int bit_pos = find_first_zero_bit(mask, data[i]);
				if (bit_pos == -1) break;
				mask |= (1 << bit_pos);
				mask |= (1 << (bit_pos - data[i] - 1));
				pos[data[i]] = bit_pos;
				++i;
			}
			if (i == 5) {
				break;
			}
		} while (next_permutation(data, data + 5));

		char buff[20] = "00000000000000";
		i = 1;
		while (i <= 7)
		{
			buff[13 - (pos[i])] += i;
			buff[13 - (pos[i] - i - 1)] += i;
			++i;
		}
		cout << buff << endl;
	}
}

namespace P3_7 {
	int end = 81;
	struct Node
	{
		int x, y, chooseInt;
		Node(int _x, int _y, int _chooseInt) :x(_x), y(_y), chooseInt(_chooseInt) {}
	};

	int guess(int i, int j, int(&table)[9][9], int(&chooseIndex)[9][9], int min = 0) {
		bool numMask[10] = { 0 };
		int x = 0;
		for (x = 0; x < 9; x++)
		{
			numMask[table[x][j] | chooseIndex[x][j]] = true;
		}
		int y = 0;
		for (y = 0; y < 9; y++)
		{
			numMask[table[i][y] | chooseIndex[i][y]] = true;
		}

		int R = i / 3, C = j / 3;
		R *= 3;
		C *= 3;

		for (x = 0; x < 3; x++)
		{
			for (y = 0; y < 3; y++)
			{
				numMask[table[R + x][C + y] | chooseIndex[R + x][C + y]] = true;
			}
		}

		++min;
		while (min < 10 && numMask[min]) ++min;
		return min;
	}
	void preGuess(stack<Node>& S, int(&table)[9][9], int(&chooseIndex)[9][9]) {
		if (S.empty()) return;
		chooseIndex[S.top().x][S.top().y] = 0;
		++end;
		S.pop();
		if (!S.empty()) {
			int num = guess(S.top().x, S.top().y, table, chooseIndex, S.top().chooseInt);
			if (num == 10)
			{
				preGuess(S, table, chooseIndex);
			}
			else
			{
				S.top().chooseInt = num;
				chooseIndex[S.top().x][S.top().y] = num;
			}
		}
	}

	void solve() {
		int table[9][9] = { 0 },
			chooseIndex[9][9] = { 0 };
		int R, C;
		for (R = 0; R < 9; R++)
		{
			for (C = 0; C < 9; C++)
			{
				char temp;
				cin >> temp;
				table[R][C] = temp - '0';
				if (table[R][C]) --end;
			}
		}
		stack<Node> S;
		int i, j, index;
		for (i = 0; i < 9 && S.empty(); i++)
		{
			for (j = 0; j < 9 && S.empty(); j++)
			{
				if ((table[i][j] | chooseIndex[i][j]) == 0) {
					--end;
					int num = guess(i, j, table, chooseIndex);
					S.push(Node(i, j, num));
					chooseIndex[i][j] = num;
				}
			}
		}
		while (true)
		{
			if (S.empty()) {
				cout << "error" << endl;
				return;
			}
			else {
				int x = 0, y;
				while (x < 9 && !S.empty())
				{
					y = 0;
					while (y < 9 && !S.empty())
					{
						if ((table[x][y] | chooseIndex[x][y]) == 0) {
							int num = guess(x, y, table, chooseIndex);
							if (num != 10) {
								--end;
								S.push(Node(x, y, num));
								chooseIndex[x][y] = num;
							}
							else {
								int num = guess(S.top().x, S.top().y, table, chooseIndex, S.top().chooseInt);
								if (num == 10)
								{
									preGuess(S, table, chooseIndex);
									x = 0;
									y = 0;
									continue;
								}
								else
								{
									S.top().chooseInt = num;
									chooseIndex[S.top().x][S.top().y] = num;
								}
							}
						}
						++y;
					}
					++x;
				}
				if (end == 0) {
					break;
				}
				else {
					preGuess(S, table, chooseIndex);
				}
			}
		}
		cout << end << endl;
		int x = 0, y = 0;
		while (x < 9 && !S.empty())
		{
			y = 0;
			while (y < 9 && !S.empty())
			{
				cout << (table[x][y] | chooseIndex[x][y]);
				++y;
			}
			cout << endl;
			++x;
		}
	}
}

namespace P3_7_2 {
	bool end = false;
	int table[9][9] = { 0 };

	int guess(int i, int j, int min = 0) {
		bool numMask[10] = { 0 };
		int x = 0;
		for (x = 0; x < 9; x++)
		{
			numMask[table[x][j]] = true;
		}
		int y = 0;
		for (y = 0; y < 9; y++)
		{
			numMask[table[i][y]] = true;
		}

		int R = i / 3, C = j / 3;
		R *= 3;
		C *= 3;
		for (x = 0; x < 3; x++)
		{
			for (y = 0; y < 3; y++)
			{
				numMask[table[R + x][C + y]] = true;
			}
		}

		++min;
		while (min < 10 && numMask[min]) ++min;
		return min;
	}

	void deepGuess() {
		int i = 0;
		while (i < 81)
		{
			if (table[i / 9][i % 9] == 0) break;
			++i;
		}
		int x = i / 9, y = i % 9;
		while (!end)
		{
			int num = guess(x, y, table[x][y]);
			if (num == 10) {
				table[x][y] = 0;
				break;
			}
			else {
				table[x][y] = num;
				if (x == 8 && y == 8) {
					end = true;
					break;
				}
				else {
					deepGuess();
				}
			}
		}
	}


	void solve() {
		int R, C;
		for (R = 0; R < 9; R++)
		{
			for (C = 0; C < 9; C++)
			{
				char temp;
				cin >> temp;
				table[R][C] = temp - '0';
			}
		}
		deepGuess();
		int x = 0, y = 0;
		while (x < 9)
		{
			y = 0;
			while (y < 9)
			{
				cout << (table[x][y]);
				++y;
			}
			cout << endl;
			++x;
		}
	}
}
#endif

#ifndef BLOCK_4
namespace P4_1 {
	void solve() {
		int *N = nullptr, *C = nullptr, *F = nullptr;
		int num, i = 2;
		cin >> num;
		N = new int[num + 1];
		C = new int[num + 1];
		F = new int[num + 1];
		fill(N, N + num + 1, 0);
		fill(C, C + num + 1, 0);
		fill(F, F + num + 1, 0);
		while (i <= num)
		{
			cin >> F[i];
			++i;
		}
		--i;
		while (i != 1) {
			int father = F[i], mul = (C[i] + N[i] + 1);
			N[father] = N[father] + N[father] * mul + mul;
			C[father] = C[father] + C[father] * N[i] + N[i];
			--i;
		}
		cout << (C[i] + N[i] + 1) << endl;
		delete[] N; delete[] C; delete[] F;
	}
}

namespace P4_2 {
	void solve() {
		int dp[10][10][10] = { 0 };
		int A[11] = { 2 ,  4 ,  7 , 11,  13 , 15 , 18 , 22 , 18 , 15  ,11 },
			B[11] = { 5 , 10 , 15 , 20 , 24 , 18 , 12 ,  9 ,  5 ,  3  , 1 },
			C[11] = { 8 , 12 , 17 , 22 , 19 , 16 , 14 , 11 ,  9 ,  7  , 4 };
		int x = 0, y = 0, z = 0, N, G_MAX = 0;
		dp[0][0][0] = A[0] + B[0] + C[0];
		cin >> N;
		for (x = 0; x*x <= N; x++)
		{
			for (y = 0; x*x + y*y <= N; y++)
			{
				for (z = 0; x*x + y*y + z*z <= N; z++)
				{
					int MAX = 0;
					if (x != 0) MAX = max(MAX, dp[x - 1][y][z] + A[x] - A[x - 1]);
					if (y != 0) MAX = max(MAX, dp[x][y - 1][z] + A[y] - A[y - 1]);
					if (z != 0) MAX = max(MAX, dp[x][y][z - 1] + A[z] - A[z - 1]);
					dp[x][y][z] = max(MAX, dp[x][y][z]);
					G_MAX = max(G_MAX, dp[x][y][z]);
				}
			}
		}
		cout << G_MAX << endl;
	}
}

namespace P4_3 {
	//int c_hanbao, c_shutiao, c_yinliao;
	int cost[3], NUM;
	int T[10000];
	bool check(int hanbao, int shutiao, int yinliao) {
		int i = 0, j = 0, cal = 0;
		int _T[10000], N[3];
		N[0] = hanbao;
		N[1] = shutiao;
		N[2] = yinliao;
		while (i < NUM)
		{
			_T[i] = T[i];
			++i;
		}
		i = 0;
		while (i < NUM)
		{
			j = 0;
			while (j < 3)
			{
				if (_T[i] >(N[j] * cost[j])) {
					_T[i] -= (N[j] * cost[j]);
					N[j] = 0;
				}
				else {
					int num = _T[i] / cost[j];
					_T[i] -= (cost[j] * num);
					N[j] -= num;
				}
				++j;
			}
			++i;
		}

		return ((N[0] | N[1] | N[2]) == 0);
	}
	void solve() {
		int a, b, c, ans, left = 0, right = 100;
		cin >> a >> b >> c
			>> cost[0] >> cost[1] >> cost[2]
			>> NUM;
		int i = 0;
		while (i < NUM)
		{
			cin >> T[i];
			++i;
		}
		while (right >= left)
		{
			ans = (right + left) / 2;
			if (check(ans * a, ans*b, ans*c)) {
				left = ans + 1;
			}
			else {
				right = ans - 1;
			}
		}
		cout << right << endl;
	}
}
namespace P4_4 {
	struct Point {
		int x, y;
		Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
		Point operator-(Point p) {
			return Point(this->x - p.x, this->y - p.y);
		}
	};
	int det(Point p1, Point p2) {
		return (p1.x * p2.y - p2.x * p1.y);
	}
	void solve() {
		Point p[4], v[6];
		int i = 0;
		while (i < 4)
		{
			cin >> p[i].x >> p[i].y;
			++i;
		}
		if (p[1].x < p[0].x) { swap(p[1].x, p[0].x); swap(p[1].y, p[0].y); }
		if (p[3].x < p[2].x) { swap(p[2].x, p[3].x); swap(p[2].y, p[3].y); }
		v[0] = p[1] - p[0];
		v[1] = p[1] - p[2];
		v[2] = p[1] - p[3];

		v[3] = p[2] - p[3];
		v[4] = p[2] - p[0];
		v[5] = p[2] - p[1];

		int j[4];
		
		string word[2] = { "不相交","相交" };
		//when you get error in there,you can
		//1  use UTF-16 with BOM or UTF-8 with BOM
		//2  delete all chinese word in this file
		j[0] = det(v[0], v[1]);
		j[1] = det(v[0], v[2]);

		if (j[0] < j[1]) swap(j[0], j[1]);
		if (j[0] > 0 && j[1] < 0) {
			;
		}
		else {
			if (j[0] == 0 && j[1] == 0) {
				if (p[1].x >= p[2].x && p[1].x <= p[3].x)
				{
					;
				}
				else {
					cout << word[0] << endl;
					return;
				}
			}
			else {
				cout << word[0] << endl;
				return;
			}
		}
		j[2] = det(v[3], v[4]);
		j[3] = det(v[3], v[5]);
		if (j[2] < j[3]) swap(j[2], j[3]);
		if (j[2] > 0 && j[3] < 0) {
			;
		}
		else {
			if (j[2] == 0 && j[3] == 0) {
				if (p[2].x >= p[0].x && p[2].x <= p[1].x)
				{
					;
				}
				else {
					cout << word[0] << endl;
					return;
				}
			}
			else {
				cout << word[0] << endl;
				return;
			}
		}
		cout << word[1] << endl;
	}
}

#endif
