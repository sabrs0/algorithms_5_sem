#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
int WORD_LEN = 5000;

using namespace std;

double q1_time = 0.0;
double q2_time = 0.0;
double q3_time = 0.0;
static queue<string> q1;
static queue<string> q2;
static queue<string> q3;
static queue<string> q_final;
static queue<string> q_usual;
static queue<string> q_us_final;

std::chrono::time_point<std::chrono::system_clock> start, stop;

static mutex m1, m2, m3, resm;
static int n;
vector<string> text_;

string encrypt_1(string s)
{
	
	for (int i = 0; i < s.length(); i++)
	{
		try
		{

			if (s[i] == 'z')
			{
				s[i] = 'a';
			}
			else if (s[i] == 'Z')
				s[i] = 'A';
			else
				s[i] = s[i] + 1;
		}
		catch(...)
		{
			cout << "ENCRYPT 1" << s << endl;
		}

	}
	return s;
}
string encrypt_2(string s)
{
	

	int sum = 0;
	for (int i = 0; i < s.length(); i++)
	{
		sum += s[i];
	}
	for (int i = 0; i < s.length(); i++)
	{
		try
		{

			if (s[i] >= 'a' && s[i] <= 'z')
			{
				s[i] = (s[i] + sum + i) % ('z' - 'a') + 'a';

			}
			else if (s[i] >= 'A' && s[i] <= 'Z')
			{
				s[i] = (s[i] + sum + i) % ('Z' - 'A') + 'A';
			}
		}
		catch (...)
		{
			cout << "ENCRYPT 2 " << s << endl;
		}
		
	}
	return s;
}
string encrypt_3(string s)
{
	if (s.length() > 0)
	{

		for (int i = 0; i < s.length() - 1; i+= 2)
		{
			try
			{
				char tmp = s[i];
				s[i] = s[i + 1];
				s[i + 1] = tmp;
			}
			catch (...)
			{
				cout << "ENCRYPT 3" << s << endl;
			}
		}
	}
	return s;
}
int random_diap(int min, int max)
{
	int num = min + rand() % (max - min + 1);

	return num;
}
void ft_line()
{
	//std::chrono::time_point<std::chrono::system_clock> start, stop;
	int num = 0;
	//start = std::chrono::system_clock::now();
	while (true) {
		if (num == n)
			break;
		m1.lock();
		stop = chrono::system_clock::now();
		double time_1 = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
		if (q1.empty()) {
			m1.unlock();
			continue;
		}
		string cur_str  = q1.front();
		q1.pop();
		stop = chrono::system_clock::now();
		double time_2 = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
		cout << "\n|LINE - 1|STRING - " << num << "|time_start - " << time_1 << "|time_stop - " << time_2 << "|" << endl;
		m1.unlock();
		string new_str = encrypt_1(cur_str);
		m2.lock();
		
		q2.push(new_str);
		m2.unlock();
		num++;
	}
	//stop = std::chrono::system_clock::now();
	//q1_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
}
void sc_line()
{
	//std::chrono::time_point<std::chrono::system_clock> start, stop;
	int num = 0;
	//start = std::chrono::system_clock::now();
	while (true) {
		if (num == n)
			break;
		m2.lock(); // wait in queue
		stop = chrono::system_clock::now();
		double time_1 = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
		if (q2.empty()) {
			m2.unlock();
			continue;
		}
		string cur_str = q2.front();
		q2.pop();
		stop = chrono::system_clock::now(); 
		double time_2 = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
		cout << "\n|LINE - 2|STRING - " << num << "|time_start - " << time_1 << "|time_stop - " << time_2 << "|" << endl;

		m2.unlock();
		string new_str = encrypt_2(cur_str);
		m3.lock();
		
		q3.push(new_str);
		m3.unlock();
		num++;
	}
	//stop = std::chrono::system_clock::now();
	//q2_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
}
void thd_line()
{
	//std::chrono::time_point<std::chrono::system_clock> start, stop;
	int num = 0;
	//start = std::chrono::system_clock::now();
	while (true) {
		if (num == n)
			break;
		m3.lock(); // wait in queue
		stop = chrono::system_clock::now();
		double time_1 = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
		if (q3.empty()) {
			m3.unlock();
			continue;
		}
		string cur_str = q3.front();
		q3.pop();
		stop = chrono::system_clock::now();
		double time_2 = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
		cout << "\n|LINE - 3|STRING - " << num << "|time_start - " << time_1 << "|time_stop - " << time_2 << "|" << endl;
		m3.unlock();
		string new_str = encrypt_3(cur_str);
		resm.lock();
		
		q_final.push(new_str);
		resm.unlock();
		num++;
	}
	//stop = std::chrono::system_clock::now();
	//q3_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
}


vector<string> generate_rand_text()
{
	vector<string> t1;
	int a_low = 97;
	int z_low = 122;
	t1.resize(n);
	for (int i = 0; i < n; i++)
	{
		string s1;
		s1.resize(WORD_LEN);
		for (int j = 0; j < WORD_LEN; j++)
		{
			s1[j] = (random_diap(a_low, z_low));
		}
		t1[i] = s1;
	}
	return t1;
}
void print_text(vector<string> t)
{
	for (int i = 0; i < t.size(); i++)
	{
		cout << t[i] << endl;
	}
}

void print_text(queue<string> q)
{
	while (!q.empty())
	{
		cout << q.front()<<endl;
		q.pop();
	}
}


void cmp_results(queue<string> q, queue<string> q2)
{
	cout << "CHECKING RESULST PROCESS" << endl;
	if (q.size() != q2.size())
	{
		cout << "ERROR INCORRECT SIZES"<<endl;
	}
	else
	{
		while(!q2.empty())
		{
			if ((q.empty() ^ q2.empty()))
			{
				cout << "SIZES ERROR " << endl;
			}
			if (q.front().compare(q2.front()) != 0)
			{
				cout << "INCORRECT STRINGS"<< endl;
				cout << "Strings are\n" << q.front() << "\n and \n" << q2.front() << endl;
				break;
			}
			q.pop();
			q2.pop();
		}
	}

}
void usual_operation()
{
	int num = 0;
	while (true)
	{
		if (num == n)
			break;
		if (q_usual.empty()) {
			continue;
		}
		string cur_str = q_usual.front();
		q_usual.pop();

		string new_str = encrypt_1(cur_str);
		new_str = encrypt_2(new_str);
		new_str = encrypt_3(new_str);

		q_us_final.push(new_str);
		num++;
	}
}

void count_time()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	double result_time_usual_arr[7], result_time_threads_arr[7];
	int ITERS = 10;
	int sizes[7] = { 100, 500, 1000, 2500, 5000, 10000 };
	for (int j = 0; j < 7; j++)
	{
		n = sizes[j];
		double result_time_threads = 0.0, result_time_usual = 0.0;
		for (int i = 0; i < ITERS; i++)
		{
			while (!q_final.empty())
			{
				q_final.pop();
				q_us_final.pop();
			}
			cout << i << endl;
			text_ = generate_rand_text();

			vector<string> text_save;
			text_save = text_;
			thread t1(ft_line);
			thread t2(sc_line);
			thread t3(thd_line);

			for (int i = 0; i < n; i++)
			{
				m1.lock();
				q1.push(text_[i]);
				m1.unlock();
			}
			start = std::chrono::system_clock::now();
			t1.join();
			t2.join();
			t3.join();
			end = std::chrono::system_clock::now();
			result_time_threads += (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());//= q1_time + q2_time + q3_time
			//cout << "Time for threads is " << result_time << endl;
			for (int i = 0; i < n; i++)
			{
				q_usual.push(text_save[i]);
			}
			start = std::chrono::system_clock::now();
			usual_operation();
			end = std::chrono::system_clock::now();
			result_time_usual += (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
			//cout << "Time for usual is " << result_time << endl;
		}
		result_time_threads /= ITERS;
		result_time_usual /= ITERS;
		cout << "for size " << sizes[j] << " usual time is " << result_time_usual << " thread time is " << result_time_threads << endl;
	}

}
int main()
{
	/*string s1;
	cin >> s1;
	s1 = encrypt_1(s1);
	cout << "ENCRYPT_1 = " << s1 << endl;
	s1 = encrypt_2(s1);
	cout << "ENCRYPT_2 = " << s1 << endl;
	s1 = encrypt_3(s1);
	cout << "ENCRYPT_3 = " << s1 << endl;*/
	//count_time();
	//std::chrono::time_point<std::chrono::system_clock> start, end;
	//double result_time;

	cout << "Input words amount:\n";
	cin >> n;
	text_ = generate_rand_text();

	vector<string> text_save;
	text_save = text_;
	thread t1(ft_line);
	thread t2(sc_line);
	thread t3(thd_line);

	for (int i = 0; i < n; i++)
	{
		m1.lock();
		q1.push(text_[i]);
		m1.unlock();
	}
	start = std::chrono::system_clock::now();
	t1.join();
	t2.join();
	t3.join();
	//end = std::chrono::system_clock::now();
	//result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());//= q1_time + q2_time + q3_time
	//cout << "Time for threads is " << result_time << endl;
	/*for (int i = 0; i < n; i++)
	{
		q_usual.push(text_save[i]);
	}
	start = std::chrono::system_clock::now();
	usual_operation();
	end = std::chrono::system_clock::now();
	result_time = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	cout << "Time for usual is " << result_time << endl;

	cmp_results(q_final, q_us_final);*/
	
	return 0;
}

