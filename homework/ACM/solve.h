namespace P1_1{
	int recursive(int n);
	int tail_recursive(int n);
	int _tail_recursive(int n, int ret);
	int formula_of_general_term(int n);

	int recursive(int n){
		if (n == 1)
			return 2;
		return 2 * (n - 1) + recursive(n - 1);
	}
	int tail_recursive(int n){
		return _tail_recursive(n, 0);
	}
	int _tail_recursive(int n, int ret){
		if (n == 1)
			return ret + 2;
		return _tail_recursive(n - 1, ret + 2 * (n - 1));
	}
	int formula_of_general_term(int n){
		return n*(n - 1) + 2;
	}
}

namespace P1_2{
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
namespace P1_3{
	template<int N>
	int find(int(&A)[N], int x);
	template<typename T>
	int find(T A, int x);
	int _find(int* A, int x, int len);

	template<int N>
	int find(int (&A)[N], int x){
		return _find(A, x, N);;
	}

	template<>
	int find<int*>(int* A, int x){
		return _find(A, x, _msize(A) / sizeof(int));
	}
	int _find(int* A, int x, int len){
		int i = 0;
		while (i != len && *(A + i) < x) ++i;
		return i != len&& *(A + i) == x ? i : -1;
	}

}
namespace P1_4{
	void find(int a[], int n, int &i, int &j, int x){
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
		std::swap(i,j);
	}
}
namespace P1_5{
	void solve() {
		int GongJi, MuJi;
		cout << setw(10) << "公鸡" << setw(10) << "母鸡" << setw(10) << "小鸡" << endl;
		for ( GongJi = 0; GongJi <= 33; GongJi++)
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
			result = N == ( (FUCK<(N % 10)>::v) + (FUCK<(N / 10 % 10)>::v) + (FUCK<(N / 100)>::v))
		};
	};

	template<int N,bool IsNarcissistic>
	struct printIfNarcissistic {
		static inline void print(){}
	};
	template<int N>
	struct printIfNarcissistic<N,true> {
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
namespace P1_7{
	struct Point;
	struct Cube;
	double D_MAX = double(INT_MAX) + double(INT_MAX);
	vector<Point> vec;
	vector<Cube> store;
	vector<int> index(7,0);
	
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
		generate_n(index.begin(), n, []() ->int{
			static int i = 0;
			return (i++);
		});
		int x, y, z, i = 0;
		cin >> x >> y >> z;
		P1 = Point(x,y,z);
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
namespace P1_8{
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
			if ( cnt[i] > (N / 2) )
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
			memset(cnt , 0,sizeof cnt);
			while (i!= N)
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
	inline void C_cnt(bool(&row)[9] ,int (&cnt)[9]) {
		int i = 0;
		while (i != 9) {
			cnt[i] += row[i];
			++i;
		}
	}
}
namespace P1_9{
	const int  MAX_N = 1000;
	pair<int, int> pre[MAX_N] = { {0,1} }, MAX(0, 1);
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
namespace P1_10{
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
		pair<int, int> a =find(vec, begin, div)
			, b = find(vec, begin + div, len - div);
		return make_pair(max(a.first, b.first), min(a.second, b.second));
	}
	void solve() {
		vector<int> vec;
		int n, i = 0;
		cin >> n;
		while (i!=n){
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
		double i,V, W;
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
		vector<pair<int,int>> vec;
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
		cin >> (res+1);
		int s;
		cin >> s;
		char *slow = res + 1, *fast = res + 2;
		while (s && *fast)
		{

			while (s && *fast && *slow && *fast < *slow ) {
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
