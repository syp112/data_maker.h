#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <string>
#include <set>
#include <map>
#include <functional>
#include <cmath>
using namespace std;
namespace color_print
{
	#ifdef _WIN32
		#include <windows.h>
		const int RED=FOREGROUND_RED;
	    const int GREEN=FOREGROUND_GREEN;
	    const int YELLOW=FOREGROUND_RED|FOREGROUND_GREEN;
	    const int BLUE=FOREGROUND_BLUE;
	    const int PURPLE=FOREGROUND_RED|FOREGROUND_BLUE;
	    const int CYAN=FOREGROUND_GREEN|FOREGROUND_BLUE;
	    const int WHITE=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
	#else
		const int RED=1;
	    const int GREEN=2;
	    const int YELLOW=3;
	    const int BLUE=4;
	    const int PURPLE=5;
	    const int CYAN=6;
	    const int WHITE=7;
	#endif
    void print(string s,int c)
    {
    	#ifdef _WIN32
		    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),c);
	    	cerr<<s<<endl;
		    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),WHITE);
		#elif __linux__
			string t="\033[1;"+to_string(30+c)+"m";
			cerr<<t<<s<<"\033[0m"<<endl;
		#endif
	    return;
	}
}
namespace data_maker
{
	mt19937_64 rand_int(time(0));
	uniform_real_distribution<double> rand_real(0,1);
	#define int long long
	int rnd(int l,int r)
	{
		return rand_int()%(r-l+1)+l;
	}
	double rnd_real(double l=0,double r=1)
	{
		return rand_real(rand_int)*(r-l)+l;
	}
	template<typename T>
	T random_choice(vector<T> a)
	{
		return a[rnd(0,a.size()-1)];
	}
	template<typename T>
	void shuffle(T st,T ed)
	{
		shuffle(st,ed,rand_int);
		return;
	}
	template<typename T>
	void random_map(T* st,T* ed,T inf,T sup)
	{
		set<T>q;
		map<T,T>b;
		for(T *i=st;i<ed;i++)
		{
			if(!b.count(*i))
			{
				for(b[*i]=rnd(inf,sup);q.count(b[*i]);b[*i]=rnd(inf,sup));
			}
			*i=b[*i];
		}
		return;
	}
	template<typename T>
	void random_map(T* st,T* ed,T n)
	{
		set<T>q;
		map<T,T>b;
		for(T *i=st;i<ed;i++)
		{
			if(!b.count(*i))
			{
				for(b[*i]=rnd(1,n);q.count(b[*i]);b[*i]=rnd(1,n));
			}
			*i=b[*i];
		}
		return;
	}
	template<typename T>
	void random_map(T* st,T* ed)
	{
		T n=ed-st;
		T p[n];
		for(T i=0;i<n;i++)
		{
			p[i]=i;
		}
		shuffle(p,p+n);
		for(T *i=st;i<ed;i++)
		{
			*i=p[i-st];
		}
		return;
	}
	template<typename T>
	void random_fill(T* st,T *ed)
	{
		int n=ed-st;
		for(T *i=st;i<ed;i++)
		{
			*i=rnd(1,n);
		}
		return;
	}
	template<typename T>
	void random_fill(T* st,T *ed,T inf,T sup)
	{
		for(T *i=st;i<ed;i++)
		{
			*i=rnd(inf,sup);
		}
		return;
	}
	template<typename T>
	void random_fill(T* st,T *ed,T inf,function<T(int)> sup)
	{
		for(T *i=st;i<ed;i++)
		{
			*i=rnd(inf,sup(i-st+1));
		}
		return;
	}
	template<typename T>
	void random_fill(T* st,T *ed,function<T(int)> inf,T sup)
	{
		for(T *i=st;i<ed;i++)
		{
			*i=rnd(inf(i-st+1),sup);
		}
		return;
	}
	template<typename T>
	void random_fill(T* st,T *ed,function<T(int)> inf,function<T(int)> sup)
	{
		for(T *i=st;i<ed;i++)
		{
			*i=rnd(inf(i-st+1),sup(i-st+1));
		}
		return;
	}
	template<typename T>
	void random_permutation(T* st,T *ed)
	{
		for(T *i=st;i<ed;i++)
		{
			*i=i-st+1;
		}
		shuffle(st,ed);
		return;
	}
	template<typename T>
	void list_fill(T* st,T *ed,double *pst,double *ped)
	{
		for(double *i=pst+1;i<ped;i++)
		{
			*i+=i[-1];
		}
		for(T *i=st;i<ed;i++)
		{
			*i=lower_bound(pst,ped,rnd_real())-pst+1;
		}
		for(double *i=ped-1;i>pst;i--)
		{
			*i-=i[-1];
		}
		return;
	}
	template<typename T>
	void list_fill(T* st,T *ed,vector<double> a)
	{
		double p[a.size()];
		for(int i=0;i<(int)a.size();i++)
		{
			p[i]=a[i];
		}
		list_fill(st,ed,p,p+a.size());
		return;
	}
	template<typename T>
	void multiple_fill(T* st,T *ed,double p,T n)
	{
		for(T *i=st;i<ed;i++)
		{
			if(i!=st&&rnd_real()<p)
			{
				*i=st[rnd(1,i-st)];
			}
			else
			{
				*i=rnd(1,n);
			}
		}
		return;
	}
	template<typename T>
	void multiple_fill(T* st,T *ed,double p)
	{
		int n=ed-st;
		for(T *i=st;i<ed;i++)
		{
			if(i!=st&&rnd_real()<p)
			{
				*i=st[rnd(0,i-st)];
			}
			else
			{
				*i=rnd(1,n);
			}
		}
		return;
	}
	template<typename T>
	void sum_limit_fill(T* st,T *ed,T s)
	{
		for(T* i=st;i<ed-1;i++)
		{
			*i=rnd(0,s*(i-st)/2/(ed-st));
			s-=*i;
		}
		ed[-1]=s;
		shuffle(st,ed);
		return;
	}
	template<typename T>
	void sum_smooth_fill(T* st,T* ed,T s)
	{
		for(T i=min(s,s/(ed-st)+1);s;s-=i,i=max(s,s/(ed-st)+1))
		{
			st[rnd(0,ed-st)]+=i;
		}
		return;
	}
	template<typename T>
	void output(T* st,T* ed)
	{
		for(auto i=st;i<ed;i++)
		{
			cout<<*i<<' ';
		}
		cout<<'\n';
		return;
	}
	struct tree
	{
		vector<pair<int,int>> e;
		void output()
		{
			for(auto [x,y]:e)
			{
				cout<<x<<' '<<y<<'\n';
			}
			return;
		}
		void push_back(int x,int y)
		{
			e.push_back({x,y});
			return;
		}
		tree& operator =(const tree &b)
		{
			e=b.e;
			return *this;
		}
	};
	tree get_tree(int n,int k)
	{
		if(k<2||k>n)
		{
			throw runtime_error("Invalid parameter");
		}
		vector<pair<int,int>> r;
		for(int i=1;i<k;i++)
		{
			r.push_back({i,i+1});
		}
		for(int i=k+1;i<=n;i++)
		{
			r.push_back({rnd(1,k-1),i});
		}
		vector<int> p(n+1);
		for(int i=1;i<=n;i++)
		{
			p[i]=i;
		}
		shuffle(p.begin()+2,p.end());
		for(auto &[x,y]:r)
		{
			x=p[x];
			y=p[y];
			if(rnd(0,1))
			{
				swap(x,y);
			}
		}
		shuffle(r.begin(),r.end());
		return {r};
	}
	tree get_dandelion(int n,int p1,int p2)
	{
		p1++;
		if(p1<1||p2<0||p1+p2>n)
		{
			throw runtime_error("Invalid parameter");
		}
		vector<pair<int,int>> r;
		for(int i=2;i<=p1;i++)
		{
			r.push_back({i-1,i});
		}
		for(int i=p1+1;i<=p1+p2;i++)
		{
			r.push_back({1,i});
		}
		for(int i=p2+1;i<=n;i++)
		{
			r.push_back({rnd(1,i-1),i});
		}
		vector<int> p(n+1);
		for(int i=1;i<=n;i++)
		{
			p[i]=i;
		}
		shuffle(p.begin()+1,p.end());
		for(auto &[x,y]:r)
		{
			x=p[x];
			y=p[y];
			if(rnd(0,1))
			{
				swap(x,y);
			}
		}
		shuffle(r.begin(),r.end());
		return {r};
	}
	template<typename T>
	struct weighed_tree
	{
		vector<tuple<int,int,T>>e;
		void output()
		{
			for(auto [x,y,w]:e)
			{
				cout<<x<<' '<<y<<' '<<w<<'\n';
			}
			return;
		}
		void output(function<void(T)> f)
		{
			for(auto [x,y,w]:e)
			{
				cout<<x<<' '<<y<<' ';
				f(w);
				cout<<'\n';
			}
			return;
		}
		void push_back(int x,int y,T w)
		{
			e.push_back({x,y,w});
			return;
		}
		weighed_tree& operator =(const weighed_tree &b)
		{
			e=b.e;
			return *this;
		}
	};
	template<typename T>
	weighed_tree<T> get_tree(int n,int k,T sup,T inf)
	{
		if(k<2||k>n)
		{
			throw runtime_error("Invalid parameter");
		}
		vector<pair<int,int>> r;
		for(int i=1;i<k;i++)
		{
			r.push_back({i,i+1,rnd(sup,inf)});
		}
		for(int i=k+1;i<=n;i++)
		{
			r.push_back({rnd(1,k-1),i,rnd(sup,inf)});
		}
		vector<int> p(n+1);
		for(int i=1;i<=n;i++)
		{
			p[i]=i;
		}
		shuffle(p.begin()+2,p.end());
		for(auto &[x,y]:r)
		{
			x=p[x];
			y=p[y];
			if(rnd(0,1))
			{
				swap(x,y);
			}
		}
		shuffle(r.begin(),r.end());
		return {r};
	}
	template<typename T>
	weighed_tree<T> get_dandelion(int n,int p1,int p2,T sup,T inf)
	{
		p1++;
		if(p1<1||p2<0||p1+p2>n)
		{
			throw runtime_error("Invalid parameter");
		}
		vector<pair<int,int>> r;
		for(int i=2;i<=p1;i++)
		{
			r.push_back({i-1,i,rnd(sup,inf)});
		}
		for(int i=p1+1;i<=p1+p2;i++)
		{
			r.push_back({1,i,rnd(sup,inf)});
		}
		for(int i=p2+1;i<=n;i++)
		{
			r.push_back({rnd(1,i-1),i,rnd(sup,inf)});
		}
		vector<int> p(n+1);
		for(int i=1;i<=n;i++)
		{
			p[i]=i;
		}
		shuffle(p.begin()+1,p.end());
		for(auto &[x,y]:r)
		{
			x=p[x];
			y=p[y];
			if(rnd(0,1))
			{
				swap(x,y);
			}
		}
		shuffle(r.begin(),r.end());
		return {r};
	}
	template<typename T>
	weighed_tree<T> get_tree(int n,int k,function<T(void)> f)
	{
		if(k<2||k>n)
		{
			throw runtime_error("Invalid parameter");
		}
		vector<pair<int,int>> r;
		for(int i=1;i<k;i++)
		{
			r.push_back({i,i+1,f()});
		}
		for(int i=k+1;i<=n;i++)
		{
			r.push_back({rnd(1,k-1),i,f()});
		}
		vector<int> p(n+1);
		for(int i=1;i<=n;i++)
		{
			p[i]=i;
		}
		shuffle(p.begin()+2,p.end());
		for(auto &[x,y]:r)
		{
			x=p[x];
			y=p[y];
			if(rnd(0,1))
			{
				swap(x,y);
			}
		}
		shuffle(r.begin(),r.end());
		return {r};
	}
	template<typename T>
	weighed_tree<T> get_dandelion(int n,int p1,int p2,function<T(void)> f)
	{
		p1++;
		if(p1<1||p2<0||p1+p2>n)
		{
			throw runtime_error("Invalid parameter");
		}
		vector<pair<int,int>> r;
		for(int i=2;i<=p1;i++)
		{
			r.push_back({i-1,i,f()});
		}
		for(int i=p1+1;i<=p1+p2;i++)
		{
			r.push_back({1,i,f()});
		}
		for(int i=p2+1;i<=n;i++)
		{
			r.push_back({rnd(1,i-1),i,f()});
		}
		vector<int> p(n+1);
		for(int i=1;i<=n;i++)
		{
			p[i]=i;
		}
		shuffle(p.begin()+1,p.end());
		for(auto &[x,y]:r)
		{
			x=p[x];
			y=p[y];
			if(rnd(0,1))
			{
				swap(x,y);
			}
		}
		shuffle(r.begin(),r.end());
		return {r};
	}
	struct graph
	{
		vector<pair<int,int>>e;
		void output()
		{
			for(auto [x,y]:e)
			{
				cout<<x<<' '<<y<<'\n';
			}
			return;
		}
		graph& operator =(const tree &b)
		{
			e=b.e;
			return *this;
		}
		graph& operator =(const graph &b)
		{
			e=b.e;
			return *this;
		}
		void push_back(int x,int y)
		{
			e.push_back({x,y});
			return;
		}
	};
	graph get_graph(int n,int m,vector<string>opt={})
	{
		for(auto s:opt)
		{
			if(s=="null")
			{
				continue;
			}
			if(s=="no_warning")
			{
				break;
			}
			if(s!="self_loop"&&s!="repeated_edges"&&s!="connected")
			{
				cerr<<"Warning. Invalid parameters : \""<<s<<"\"\n";
			}
		}
		set<string>q(opt.begin(),opt.end());
		bool self_loop=q.count("self_loop");
		bool repeated_edges=q.count("repeated_edges");
		bool connected=q.count("connected");
		graph r;
		if(m<0||(m>n*(n-1)/2&&!repeated_edges))
		{
			throw runtime_error("Invalid parameter");
		}
		if(connected)
		{
			if(m<n-1)
			{
				throw runtime_error("Invalid parameter");
			}
			m-=n-1;
			r=get_tree(n,rnd(2,n));
		}
		if(repeated_edges)
		{
			while(m--)
			{
				int x=rnd(1,n),y=rnd(1,n);
				if(x==y&&!self_loop)
				{
					m++;
					continue;
				}
				r.push_back(x,y);
			}
		}
		else
		{
			set<pair<int,int>>e;
			for(auto [x,y]:r.e)
			{
				e.insert({x,y});
			}
			while(m--)
			{
				int x=rnd(1,n),y=rnd(1,n);
				if(e.count({x,y})||(x==y&&!self_loop))
				{
					m++;
					continue;
				}
				r.push_back(x,y);
			}
		}
		vector<int>p(n+1);
		for(int i=1;i<=n;i++)
		{
			p[i]=i;
		}
		shuffle(p.begin()+1,p.end());
		for(auto &[x,y]:r.e)
		{
			x=p[x];
			y=p[y];
			if(rnd(0,1))
			{
				swap(x,y);
			}
		}
		return r;
	}
	template<typename T>
	struct weighed_graph
	{
		vector<tuple<int,int,T>>e;
		void output()
		{
			for(auto [x,y,z]:e)
			{
				cout<<x<<' '<<y<<' '<<z<<'\n';
			}
			return;
		}
		void output(function<void(T)> f)
		{
			for(auto [x,y,z]:e)
			{
				cout<<x<<' '<<y<<' ';
				f(z);
				cout<<'\n';
			}
		}
		weighed_graph& operator =(const weighed_tree<T> &b)
		{
			e=b.e;
			return *this;
		}
		weighed_graph& operator =(const weighed_graph &b)
		{
			e=b.e;
			return *this;
		}
		void push_back(int x,int y,T w)
		{
			e.push_back({x,y,w});
			return;
		}
	};
	template<typename T>
	weighed_graph<T> get_graph(int n,int m,T sup,T inf,vector<string>opt={})
	{
		for(auto s:opt)
		{
			if(s=="null")
			{
				continue;
			}
			if(s=="no_warning")
			{
				break;
			}
			if(s!="self_loop"&&s!="repeated_edges"&&s!="connected")
			{
				cerr<<"Warning. Invalid parameters : \""<<s<<"\"\n";
			}
		}
		set<string>q(opt.begin(),opt.end());
		bool self_loop=q.count("self_loop");
		bool repeated_edges=q.count("repeated_edges");
		bool connected=q.count("connected");
		weighed_graph<T> r;
		if(m<0||(m>n*(n-1)/2&&!repeated_edges))
		{
			throw runtime_error("Invalid parameter");
		}
		if(connected)
		{
			if(m<n-1)
			{
				throw runtime_error("Invalid parameter");
			}
			m-=n-1;
			r=get_tree(n,rnd(2,n),inf,sup);
		}
		if(repeated_edges)
		{
			while(m--)
			{
				int x=rnd(1,n),y=rnd(1,n);
				if(x==y&&!self_loop)
				{
					m++;
					continue;
				}
				r.push_back(x,y,rnd(inf,sup));
			}
		}
		else
		{
			set<pair<int,int>>e;
			for(auto [x,y]:r.e)
			{
				e.insert({x,y});
			}
			while(m--)
			{
				int x=rnd(1,n),y=rnd(1,n);
				if(e.count({x,y})||(x==y&&!self_loop))
				{
					m++;
					continue;
				}
				r.push_back(x,y,rnd(inf,sup));
			}
		}
		vector<int>p(n+1);
		for(int i=1;i<=n;i++)
		{
			p[i]=i;
		}
		shuffle(p.begin()+1,p.end());
		for(auto &[x,y,z]:r.e)
		{
			x=p[x];
			y=p[y];
			if(rnd(0,1))
			{
				swap(x,y);
			}
		}
		return r;
	}
	template<typename T>
	weighed_graph<T> get_graph(int n,int m,function<T(void)> f,vector<string>opt={})
	{
		for(auto s:opt)
		{
			if(s=="null")
			{
				continue;
			}
			if(s=="no_warning")
			{
				break;
			}
			if(s!="self_loop"&&s!="repeated_edges"&&s!="connected")
			{
				cerr<<"Warning. Invalid parameters : \""<<s<<"\"\n";
			}
		}
		set<string>q(opt.begin(),opt.end());
		bool self_loop=q.count("self_loop");
		bool repeated_edges=q.count("repeated_edges");
		bool connected=q.count("connected");
		weighed_graph<T> r;
		if(m<0||(m>n*(n-1)/2&&!repeated_edges))
		{
			throw runtime_error("Invalid parameter");
		}
		if(connected)
		{
			if(m<n-1)
			{
				throw runtime_error("Invalid parameter");
			}
			m-=n-1;
			r=get_tree(n,rnd(2,n),f);
		}
		if(repeated_edges)
		{
			while(m--)
			{
				int x=rnd(1,n),y=rnd(1,n);
				if(x==y&&!self_loop)
				{
					m++;
					continue;
				}
				r.push_back(x,y,f());
			}
		}
		else
		{
			set<pair<int,int>>e;
			for(auto [x,y]:r.e)
			{
				e.insert({x,y});
			}
			while(m--)
			{
				int x=rnd(1,n),y=rnd(1,n);
				if(e.count({x,y})||(x==y&&!self_loop))
				{
					m++;
					continue;
				}
				r.push_back(x,y,f());
			}
		}
		vector<int>p(n+1);
		for(int i=1;i<=n;i++)
		{
			p[i]=i;
		}
		shuffle(p.begin()+1,p.end());
		for(auto &[x,y,z]:r.e)
		{
			x=p[x];
			y=p[y];
			if(rnd(0,1))
			{
				swap(x,y);
			}
		}
		return r;
	}
	#define int long long
	template<typename T=int>
	struct range_taking
	{
		vector<pair<pair<int,int>,T>>q;
		void operator ()(int l,int r,T v)
		{
			q.push_back({{l,r},v});
			return;
		}
		template<typename... Val>
		void operator ()(int l,int r,T v,Val... val)
		{
			(*this)(l,r,v);
			(*this)(val...);
			return;
		}
		void list(int id,T v)
		{
			(*this)(id,id,v);
			return;
		}
		template<typename... Val>
		void list(int id,T v,Val... val)
		{
			list(id,v);
			list(id+1,val...);
			return;
		}
		T operator [](int s)
		{
			for(auto i=q.rbegin();i!=q.rend();i++)
			{
				auto [t,v]=*i;
				auto [l,r]=t;
				if(l<=s&&s<=r)
				{
					return v;
				}
			}
			throw runtime_error("range_taking not found "+to_string(s));
		}
	};
	/*#define int long long
	struct range_taking
	{
		struct node
		{
			int l,r;
			mutable int v;
			bool operator <(const node &b)const
			{
				return l<b.l;
			}
		};
		set<node>q;
		auto split(int x)
		{
			auto p=q.lower_bound({x,0,0});
			if(p!=q.end()&&p->l==x)
			{
				return p;
			}
			p--;
			int l=p->l,r=p->r,v=p->v;
			q.erase(p);
			q.insert({l,x-1,v});
			return q.insert({x,r,v}).first;
		}
		int& operator ()(int l,int r)
		{
			auto pr=split(r+1),pl=split(l);
			q.erase(pl,pr);
			return q.insert({l,r,0}).first->v;
		}
		void operator ()(int l,int r,int v)
		{
			auto pr=split(r+1),pl=split(l);
			q.erase(pl,pr);
			q.insert({l,r,v});
			return;
		}
		template<typename... Val>
		void operator ()(int l,int r,int v,Val... val)
		{
			(*this)(l,r,v);
			(*this)(val...);
			return;
		}
		void list(int id,int v)
		{
			(*this)(id,id,v);
			return;
		}
		template<typename... Val>
		void list(int id,int v,Val... val)
		{
			list(id,v);
			list(id+1,val...);
			return;
		}
		int operator [](int x)
		{
			auto p=--q.upper_bound({x,0,0});
			return p->v;
		}
		range_taking()
		{
			q.insert({-1000000000000000,1000000000000000,-2147483647});
		}
	};
	#undef int*/
}
namespace file_operator
{
	using namespace color_print;
	string title;
	void open_file(int s,string h=".in")
	{
		freopen((title+to_string(s)+h).c_str(),"w",stdout);
		return;
	}
	void open_file(int s,int t,string h=".in")
	{
		freopen((title+to_string(s)+"-"+to_string(t)+h).c_str(),"w",stdout);
		return;
	}
	void getans(int s,string h=".ans")
	{
		cerr<<"RUNNING ON Task "<<title<<s<<"\n";
		cout<<flush;
		freopen((title+to_string(s)+".in").c_str(),"r",stdin);
		freopen((title+to_string(s)+h).c_str(),"w",stdout);
		bool res;
		#ifdef __linux__
			res=system(("./"+title).c_str());
		#elif _WIN32
			res=system((title+".exe").c_str());
		#else
			throw runtime_error("Unknown operations.");
			exit(0);
		#endif
		if(res)
		{
			print("Task #"+to_string(s)+":\nRUNTIME_ERROR\nreturn "+to_string(res)+"\n",RED);
		}
		else
		{
			print("Done\n",GREEN);
		}
		return;
	}
	void getans(int s,int t,string h=".ans")
	{
		cerr<<"RUNNING ON Task "<<title<<s<<"-"<<t<<"\n";
		cout<<flush;
		freopen((title+to_string(s)+"-"+to_string(t)+".in").c_str(),"r",stdin);
		freopen((title+to_string(s)+"-"+to_string(t)+h).c_str(),"w",stdout);
		bool res;
		#ifdef __linux__
			res=system(("./"+title).c_str());
		#elif _WIN32
			res=system((title+".exe").c_str());
		#else
			throw runtime_error("Unknown operations.");
			exit(0);
		#endif
		if(res)
		{
			print("Task #"+to_string(s)+"-"+to_string(t)+":\nRUNTIME_ERROR\nreturn "+to_string(res)+"\n",RED);
		}
		else
		{
			print("Done\n",GREEN);
		}
		return;
	}
}
