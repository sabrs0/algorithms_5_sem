#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
int WORD_LEN = 50;
using namespace std;
static queue<string> q1;
static queue<string> q2;
static queue<string> q3;
static queue<string> q_final;
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

        for (int i = 0; i < s.length() - 1; i++)
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
    int num = 0;
    while (true) {
        if (num == n)
            break;
        m1.lock();
        if (q1.empty()) {
            m1.unlock();
            continue;
        }
        cout << "AT FT LINE" << endl;
        cout << "Q1.front() is " << q1.front() << "with len = " << q1.front().length() << endl;
        string cur_str  = q1.front();
        q1.pop();

        m1.unlock();
        string new_str = encrypt_1(cur_str);
        m2.lock();

        q2.push(new_str);
        m2.unlock();
        num++;
    }
}
void sc_line()
{
    int num = 0;
    while (true) {
        if (num == n)
            break;
        m2.lock(); // wait in queue
        if (q2.empty()) {
            m2.unlock();
            continue;
        }
        cout << "AT SC LINE" << endl;
        cout << "Q2.front() is " << q2.front() << "with len = " << q2.front().length() << endl;
        string cur_str = q2.front();
        q2.pop();

        m2.unlock();
        string new_str = encrypt_2(cur_str);
        m3.lock();

        q3.push(new_str);
        m3.unlock();
        num++;
    }
}
void thd_line()
{
    int num = 0;
    while (true) {
        if (num == n)
            break;
        m3.lock(); // wait in queue
        if (q3.empty()) {
            m3.unlock();
            continue;
        }
        cout << "AT THD LINE" << endl;
        cout << "Q3.front() is " << q3.front() << "with len = " << q3.front().length() <<endl;
        string cur_str = q3.front();
        q3.pop();

        m3.unlock();
        string new_str = encrypt_3(cur_str);
        resm.lock();

        q_final.push(new_str);
        resm.unlock();
        num++;
    }
}


vector<string> generate_rand_text()
{
    vector<string> t1;
    int a_low = 97;
    int z_low = 122;
    int A_upper = 65;
    int Z_upper = 90;
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


void cmp_results(queue<string> q, vector<string> t)
{
    cout << "CHECKING RESULST PROCESS" << endl;
    if (q.size() != t.size())
    {
        cout << "ERROR INCORRECT SIZES"<<endl;
    }
    else
    {
        for (int i = 0; i < t.size(); i++)
        {
            if (q.empty() && i < t.size() - 1)
            {
                cout << "SIZES ERROR " << endl;
            }
            if (q.front().compare(t[i]) != 0)
            {
                cout << "INCORRECT STRINGS AT INDEX = " << i << endl;
                cout << "Strings are\n" << q.front() << "\n and \n" << t[i] << endl;
                break;
            }
            q.pop();
        }
    }

}

int main()
{
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
        cout << "i = " << i<<endl;
        m1.lock();
        q1.push(text_[i]);
        m1.unlock();
    }
    t1.join();
    t2.join();
    t3.join();
    for (int i = 0; i < text_save.size(); i ++)
    {
        text_save[i] = encrypt_1(text_save[i]);
        text_save[i] = encrypt_2(text_save[i]);
        text_save[i] = encrypt_3(text_save[i]);
    }


    cmp_results(q_final, text_save);

    return 0;
}

