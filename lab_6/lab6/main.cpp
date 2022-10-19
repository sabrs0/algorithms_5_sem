//НАЙТИ ПРОБЛЕМУ В ПЕРЕДАЧЕ ANT в качестве параметра CUR_ROUTE = ROUTE(Не получается фиксировать маршруты в log)'
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <memory>
#include <ctime>
#define EPS 1e-9
#define VISITED 1
#define NOT_VISITED 0
using namespace std;



int max_int = numeric_limits<int>::max();
/*
 * Author:  David Robert Nadeau
 * Site:    http://NadeauSoftware.com/
 * License: Creative Commons Attribution 3.0 Unported License
 *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 */
#if defined(_WIN32)
#include <Windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>

#else
#error "Unable to define getCPUTime( ) for an unknown OS."
#endif


 /**
  * Returns the amount of CPU time used by the current process,
  * in seconds, or -1.0 if an error occurred.
  */
double getCPUTime() {
#if defined(_WIN32)
	/* Windows -------------------------------------------------- */
	FILETIME createTime;
	FILETIME exitTime;
	FILETIME kernelTime;
	FILETIME userTime;
	if (GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime) != -1) {
		ULARGE_INTEGER li = { {userTime.dwLowDateTime, userTime.dwHighDateTime } };
		return li.QuadPart / 10000000.;
	}

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
	/* AIX, BSD, Cygwin, HP-UX, Linux, OSX, and Solaris --------- */

#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
	/* Prefer high-res POSIX timers, when available. */
	{
		clockid_t id;
		struct timespec ts;
#if _POSIX_CPUTIME > 0
		/* Clock ids vary by OS.  Query the id, if possible. */
		if (clock_getcpuclockid(0, &id) == -1)
#endif
#if defined(CLOCK_PROCESS_CPUTIME_ID)
			/* Use known clock id for AIX, Linux, or Solaris. */
			id = CLOCK_PROCESS_CPUTIME_ID;
#elif defined(CLOCK_VIRTUAL)
			/* Use known clock id for BSD or HP-UX. */
			id = CLOCK_VIRTUAL;
#else
			id = (clockid_t)-1;
#endif
		if (id != (clockid_t)-1 && clock_gettime(id, &ts) != -1)
			return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
	}
#endif

#if defined(RUSAGE_SELF)
	{
		struct rusage rusage;
		if (getrusage(RUSAGE_SELF, &rusage) != -1)
			return (double)rusage.ru_utime.tv_sec + (double)rusage.ru_utime.tv_usec / 1000000.0;
	}
#endif

#if defined(_SC_CLK_TCK)
	{
		const double ticks = (double)sysconf(_SC_CLK_TCK);
		struct tms tms;
		if (times(&tms) != (clock_t)-1)
			return (double)tms.tms_utime / ticks;
	}
#endif

#if defined(CLOCKS_PER_SEC)
	{
		clock_t cl = clock();
		if (cl != (clock_t)-1)
			return (double)cl / (double)CLOCKS_PER_SEC;
	}
#endif

#endif

	return -1;        /* Failed. */
}
typedef struct  
{
	double pheromone;
	double obr_rasst;
} city_t;

typedef struct
{
	vector<int> visited_route;
	double len;
}
final_route_t;

class Route_Tab
{
public:
	vector<vector<int>> table;
	int size;

	void read_table(string file);
	void print_table();


};
void Route_Tab::read_table(string file)
{
	ifstream fin(file);
	if (!fin.is_open())
	{
		cout << "ERROR OPEN FILE\n";
	}
	else
	{
		fin >> this->size;
		this->table.resize(this->size);
		for (int i = 0; i < this->size; i++)
		{
			this->table[i].resize(this->size);
			for (int j = 0; j < this->size; j++)
			{
				fin >> this->table[i][j];
			}
		}
		fin.close();
		cout << "Successfully read" << endl;
	}
}
void Route_Tab::print_table()
{
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			cout << this->table[i][j] << " ";
		}
		cout << endl;
	}
}
class Route_Map
{
public:
	friend class Ant;
	friend class Route_Tab;

	Route_Tab table_rassts;
	Route_Map() = default;
	Route_Map(double alpha_, double beta_, double Q_, double K_ispar_, double phero_, double rasst_, int iter_amount, Route_Tab T1) :
		alpha(alpha_), beta(beta_), Q_const(Q_), K_ispar_const(K_ispar_), init_phero(phero_), rasst_const(rasst_), iters(iter_amount)
	{
		routes_log.resize(iter_amount);
		table_rassts = T1;
		min_routes.resize(this->table_rassts.size);
		for (int i = 0; i < min_routes.size(); i++)
		{
			min_routes[i].len = max_int;
		}
	};
	//Route_Map(const Route_Map&) = delete;
	//Route_Map& operator=(const Route_Map&) = delete;
	vector<vector<final_route_t>> routes_log;
	double alpha;
	double beta;
	int iters;
	int current_iter;
	double init_phero;
	double will_sum;
	vector<city_t> map_;
	vector<vector<city_t>> will_table; //таблица желаний перехода между городами
	double Q_const;
	double K_ispar_const;
	double rasst_const;
	vector<final_route_t> min_routes;

	void update_pheros();
	void init_will_table();
	void perebor();
	void push_Ant(int i);
	void print_log();
};
void Route_Map::print_log()
{
	for (int i = 0; i < routes_log.size(); i++)
	{
		cout << "for iter " << i << endl;
		for (int j = 0; j < routes_log[i].size(); j++)
		{
			cout << '\t' << "len = "<< routes_log[i][j].len << " | route is ";
			for (int k = 0; k < routes_log[i][j].visited_route.size(); k++)
			{
				cout << routes_log[i][j].visited_route[k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}
void Route_Map::update_pheros()
{
	for (int i = 0; i < will_table.size(); i++)
	{
		for (int j = 0; j < will_table[i].size(); j++)
		{
			will_table[i][j].pheromone *= K_ispar_const;
		}
	}
	for (int i = 0; i < routes_log[current_iter].size(); i++)
	{
		double delta = Q_const / routes_log[current_iter][i].len;
		for (int j = 0; j < routes_log[current_iter][i].visited_route.size() - 1; j++)
		{
			will_table[routes_log[current_iter][i].visited_route[j]][routes_log[current_iter][i].visited_route[j + 1]].pheromone += delta;
		}
	}
}
void Route_Map::perebor()
{
	for (int i = 0; i < iters; i++)
	{
		//cout << "CURRENT_ITER IS " << i << endl;
		for (int j = 0; j < this->table_rassts.size; j++)
		{
			current_iter = i;
			
			push_Ant(j);
		}
		update_pheros();
	}
}

void Route_Map::init_will_table()
{
	this->will_table.resize(this->table_rassts.size);
	
	for (int i = 0; i < this->table_rassts.size; i++)
	{
		this->will_table[i].resize(this->table_rassts.size);
		for (int j = 0; j < this->table_rassts.size; j++)
		{
			this->will_table[i][j].pheromone = this->init_phero;
			this->will_table[i][j].obr_rasst = this->rasst_const / this->table_rassts.table[i][j];
		}
	}
}
class Ant
{
public:
	friend class Route_Map;
	Ant(/*shared_ptr<Route_Map > route*/Route_Map *route, int from_):from(from_)
	{
		//this->cur_route.reset(new Route_Map);
		this->cur_route = route;
		tabu_list.resize(cur_route->table_rassts.size);
		fill_n(tabu_list.begin(), tabu_list.size(), NOT_VISITED);
		/*for (int i = 0; i < tabu_list.size(); i++)
		{
			tabu_list[i] = i;
		}
		swap(tabu_list[0], from);*/
		route_final.len = 0.0;
		
	}
	int from;
	int to;
	vector<int> tabu_list;
	Route_Map  *cur_route;
	final_route_t route_final;
	void run_();
	vector<double> count_probability(int cur_from);
	int get_next_city(vector<double> prob, double rand_);


};
vector<double> Ant::count_probability(int cur_from)
{
	vector<double> prob(tabu_list.size(), -1.0);
	double sum = 0.0;
	for (int i = 0; i < tabu_list.size(); i++)
	{
		if (tabu_list[i] == NOT_VISITED )
		{
			sum += pow(this->cur_route->will_table[cur_from][i].pheromone, this->cur_route->alpha) *
				pow(this->cur_route->will_table[cur_from][i].obr_rasst, this->cur_route->beta);

		}
	}
	for (int i = 0; i < tabu_list.size(); i++)
	{
		if (tabu_list[i] == NOT_VISITED )
		{
			prob[i] = pow(this->cur_route->will_table[cur_from][i].obr_rasst, this->cur_route->beta) *
				pow(this->cur_route->will_table[cur_from][i].pheromone, this->cur_route->alpha) / sum;
		}
		//cout  << prob[i]<<" ";
	} 
	//cout /*<<"SUM is "<<sum*/<< endl;
	return prob;
}

void Route_Map::push_Ant(int i)
{

	//shared_ptr<Route_Map > ptr(this);
	Ant A(this, i);
	A.run_();
	
}
int Ant::get_next_city(vector<double> prob, double rand_)
{
	vector<double> copy_ = prob;
	sort(copy_.begin(), copy_.end());
	double sum= 0.0;
	for (int i = 0; i < copy_.size(); i++)
	{
			if (copy_[i] >= EPS)
			{
				sum += copy_[i];
				if (rand_ <= sum)
				{
					for (int j = 0; j < copy_.size(); j++)
					{
						if (tabu_list[j] == NOT_VISITED && j != from)
						{
							if (fabs(prob[j] - copy_[i]) < EPS && prob[j] > EPS && copy_[i] > EPS)
							{
								//cout << "DONE" << endl;
								return j;
								break;
							}
						}
					}
				}
			}
	}
}
void Ant::run_()
{
	int cur_from = from;
	route_final.visited_route.push_back(cur_from);
	tabu_list[cur_from] = VISITED;
	int i = 0;
	while(i < tabu_list.size())
	{
		//cout << "VERSH " << i <<" is "<<tabu_list[i] << endl;;
		if (tabu_list[i] == NOT_VISITED )
		{
			vector<double> prob = count_probability(cur_from);
			double next_city = (rand() % 10000) / (10000 * 1.0);

			int cur_from2 = get_next_city(prob, next_city);
			route_final.visited_route.push_back(cur_from2);
			route_final.len += this->cur_route->table_rassts.table[cur_from][cur_from2];
			//cout <<"\t" <<cur_from<<" "<<cur_from2 << " RAND_NUM IS " << next_city<<endl;
			cur_from = cur_from2;
			tabu_list[cur_from] = VISITED;
			i = 0;
		}
		i++;
	}
	if (route_final.visited_route[route_final.visited_route.size() - 1] != route_final.visited_route[0])
	{

		route_final.len += this->cur_route->table_rassts.table[route_final.visited_route[route_final.visited_route.size() - 1]][0];
		route_final.visited_route.push_back(route_final.visited_route[0]);
	}
	this->cur_route->routes_log[this->cur_route->current_iter].push_back(route_final);
	if (route_final.len < this->cur_route->min_routes[from].len)
	{
		this->cur_route->min_routes[from] = route_final;
	}
	

	/*cout << "for iter " << cur_route->current_iter << endl;
	for (int j = 0; j < cur_route->routes_log[this->cur_route->current_iter].size(); j++)
	{
		cout << '\t' << "len = " << cur_route->routes_log[this->cur_route->current_iter][j].len << " | route is ";
		for (int k = 0; k < cur_route->routes_log[this->cur_route->current_iter][j].visited_route.size(); k++)
		{
			cout << cur_route->routes_log[this->cur_route->current_iter][j].visited_route[k] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
}
void swap(vector<int> &a, int i, int j)
{
	int s = a[i];
	a[i] = a[j];
	a[j] = s;
}
bool NextSet(vector<int> &a, int n)
{
	int j = n - 2;
	while (j != -1 && a[j] >= a[j + 1]) j--;
	if (j == -1)
		return false; // больше перестановок нет
	int k = n - 1;
	while (a[j] >= a[k]) k--;
	swap(a, j, k);
	int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
	while (l < r)
		swap(a, l++, r--);
	return true;
}
void Print(vector<int> a, int n)  // вывод перестановки
{
	
	//cout.width(3); // ширина поля вывода номера перестановки
	//cout << num++ << ": ";
}
vector<vector<int>> generate_perestanovki(vector<int> a, int n)
{
	vector<vector<int>> perests;
	while (NextSet(a, n))
	{
		//Print(a, n);
		vector<int> cpy = a;
		perests.push_back(cpy);
	}
	return perests;
}
int count_route(vector<int> cur_route, Route_Tab T)
{
	int sum = 0;
	for (int i = 0; i < cur_route.size() - 1; i++)
	{
		sum += T.table[cur_route[i]][cur_route[i + 1]];
	}
	return sum;
}
final_route_t full_perebor(Route_Tab T, int starter_city)
{
	vector<int> perest;
	for (int i = 1; i < T.size; i++)
	{
		if (i != starter_city)
			perest.push_back(i);
	}
	vector<vector<int>> perestanovki = generate_perestanovki(perest, perest.size());
	int min_route_len = max_int;
	vector<int> min_route;
	for (int i = 0; i < perestanovki.size(); i++)
	{
		if (i % 10000 == 0)
			cout << "CUR i is" << i<<endl;
		vector<int> route_cur; route_cur.push_back(starter_city);
		for (int j = 0; j < perestanovki[i].size(); j++)
		{
			route_cur.push_back(perestanovki[i][j]);
		}
		route_cur.push_back(starter_city);
		int cur_route_len = count_route(route_cur, T);
		if (cur_route_len < min_route_len)
		{
			min_route_len = cur_route_len;
			min_route = route_cur;

		}
		
	}
	final_route_t pereborr;
	pereborr.len = min_route_len;
	pereborr.visited_route = min_route;
	return pereborr;
}
void get_time()
{
	vector<string> files = { "data_2.txt", "data_4.txt", "data_6.txt", "data_8.txt", "data_10.txt" };
	for (int i = 0; i < files.size(); i++)
	{
		double beg, end;


		
		Route_Tab T1;
		T1.read_table(files[i]);
		cout << "FOR LEN  = " << T1.size << endl;
		beg = getCPUTime();//clock();
		final_route_t Ans = full_perebor(T1, 0);
		end = getCPUTime();//clock();
		cout << "\tUSUAL TIME : " << end - beg /*/ CLOCKS_PER_SEC*/ << endl;
		Route_Map M1(1, 4, 4, 0.8, 0.2, 200, 500, T1);
		beg = getCPUTime();//clock();
		M1.init_will_table();
		M1.perebor();
		end = getCPUTime();//clock();
		cout << "\tANT TIME : " << end - beg/* / CLOCKS_PER_SEC */<< endl;

	}
}
int main()
{
	srand(time(0));
	//get_time();
	Route_Tab T1;
	T1.read_table("data_10.txt");
	T1.print_table();
	Route_Map M1(1, 6, 4, 0.9, 0.2, 200, 1000, T1);
	M1.init_will_table();
	M1.perebor();
	//M1.print_log();



	for (int i = 0; i < M1.min_routes.size(); i++)
	{
		cout << "FOR " << i << " min len is " << M1.min_routes[i].len << endl;
		for (int j = 0; j < M1.min_routes[i].visited_route.size(); j++)
		{
			cout << M1.min_routes[i].visited_route[j] << " ";
		}
		cout << endl;
	}
	final_route_t Ans = full_perebor(T1, 0);
	cout << " min len is " << Ans.len << endl;
	for (int j = 0; j < Ans.visited_route.size(); j++)
	{
		cout << Ans.visited_route[j] << " ";
	}
	/*vector<size_t> alphas = { 0, 1, 2, 3, 4, 5};
	vector<size_t> betas = { 0, 1, 2, 3, 4, 5};
	vector<double> qs = { 0.1, 0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.75, 0.8, 0.9 };
	ofstream fout("best.txt");
	fout << "ITER AMOUNT IS 100" << endl;
	for (int i = 0; i < alphas.size(); i++)
	{
		cout << i << endl;
		for (int j = 0; j < betas.size(); j++)
		{
			for (int k = 0; k < qs.size(); k++)
			{
				Route_Map M1(alphas[i], betas[i], 4, qs[k], 0.2, 200, 100, T1);
				M1.init_will_table();
				M1.perebor();
				//cout <<"ALPHA: " <<alphas[i] << " BETA: " << betas[j] << " ISPAR: " << qs[k] << " DIFF: " << abs(M1.min_routes[0].len - Ans.len)<<endl;
				if (abs(M1.min_routes[0].len - Ans.len) == 0)
				{
					fout<< "ALPHA: " << alphas[i] << " BETA: " << betas[j] << " ISPAR: " << qs[k] << " DIFF: " << abs(M1.min_routes[0].len - Ans.len) << endl;
					//cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
				}
			}
		}
	}
	//double alpha_, double beta_, double Q_, double K_ispar_, double phero_, double rasst_, int iter_amount, Route_Tab T1
	return 0;*/
}