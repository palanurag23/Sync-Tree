#include<bits/stdc++.h>
using namespace std;
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

// // using namespace std;
// #define int long long 
#define endl "\n"
#define double long double
#define S second
#define F first
#define pb push_back
#define vi vector<int>
#define vvi vector< vector<int> > 
#define si  set <int>
#define pii  pair <int, int>
#define vpi  vector <pii>
#define mii  map <int, int>
#define sz(x)  ((int) x.size())
#define all(p)  p.begin(), p.end()
#define rall(p)  p.rbegin(), p.rend()
#define que_max   priority_queue <int>
#define que_min   priority_queue <int, vi, greater<int>>
#define print(a)  for(auto x : a) cout << x << " "; cout << endl
#define print1(a) for(auto x : a) cout << x.F << " " << x.S << endl
#define print2(a,x,y)  for(int i = x; i < y; i++) cout<< a[i]<< " "; cout << endl
// #define bug(...) _f (#VA_ARGS, __VA_ARGS_) // can debug multiple variables but only one vector

template <typename Arg1>
void __f (const char* name, vector<Arg1> v) { cout << name << " : " ; for( Arg1 x : v ) cout << x << " "; cout << endl; }
template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
    const char* comma = strchr (names + 1, ',');
    cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}
int power( int a, int b, int m ){
    int result = 1 ;
    while(b){       if(b&1) result = ( (result%m) * (a%m) ) %m ;        a = ( (a%m) * (a%m) )%m ;       b >>=1 ;    }
    return result ;
}

void fill_root( string &root , int n )
{
    root += "(" ;
    for( int i = 0 ;  i < n ; i++ )
    {
        char ch = 'A'+i ;
        root += ch ;
    }
    root += ")" ;
}

bool find_repeaded_non_homo( string &node , map<string,int> &non_homo )
{
    int i = 0 ;
    int n = node.size() ;

    string component = "" ;
    while( i<n )
    {
        component = "" ;
        while( node[i] != ')' and i<n )
        {
            component += node[i] ;
            i++ ;
        }
        component += node[i] ;
        // bug(component) ;
        i++ ;
        if( non_homo[component] > 0 ) return true ;
    }
    return false ;
}

bool find_if_trivial( string &node )
{
    int i = 0 ;
    int n = node.size() ;

    string component = "" ;
    while( i<n )
    {
        component = "" ;
        while( node[i] != ')' and i<n )
        {
            component += node[i] ;
            i++ ;
        }
        component += node[i] ;
        // bug(component) ;
        i++ ;
        if(  component.size() > 3 ) return false ;
    }
    return true ;
}
string find_child_0( string &node , vpi&ns0 )
{
    string child = "" ;
    int i = 0 ;
    int n = node.size() ;

    string component = "" ;
    while( i<n )
    {
        component = "" ;
        while( node[i] != ')' and i<n )
        {
            component += node[i] ;
            i++ ;
        }
        component += node[i] ;
        // bug(component) ;
        i++ ;
        string out0 = "" ;
        string out1 = "" ;

        for( char ch : component )
        {
            if( ch == '(' or ch == ')' ) continue ;
            if( ns0[ ch-'A' ].S == 0) 
            {
                char x = 'A' + ns0[ ch-'A' ].F -1;
                out0 += x ;
            }
            else
            {
                char x =  'A' + ns0[ ch-'A' ].F -1;
                out1 += x ;
            }
        }

        set<char> s ;
        for( char ch : out0 ) s.insert(ch) ;
        for( char ch : out1 ) s.insert(ch) ;
        
        string ans = "" ;
        for( char ch : s )ans += ch ;

        if( ans != "" ) child += "(" + ans + ")" ;

    }

    return child ;
}

void fill_non_homo_components( string node , vector<string> &non_homo_in_this_level )
{
    int i = 0 ;
    int n = node.size() ;

    string component = "" ;
    while( i<n )
    {
        component = "" ;
        while( node[i] != ')' and i<n )
        {
            component += node[i] ;
            i++ ;
        }
        component += node[i] ;
        // bug(component) ;
        i++ ;
        set<char> s ;

        for( char ch : component ) s.insert(ch) ;
        if( s.size() > 3 ) non_homo_in_this_level.pb( component ) ;
    }
}

string convert( string node )
{
    string parent = "" ;
        for( char x : node )
        {
            if( x == '(' or x == ')' ) parent += '_' ;
            else parent += x ;
        }
    return parent ; 
}

string url_encode(const string &value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}

// string int_to_string/

void print_graph( map<string,vector<string>> children, map<string,int>&colors01 , map<string,int> &homo_or_trivial ,map< string, int > &treminated )
{
    string ans = "https://dreampuf.github.io/GraphvizOnline/#" ;
    string str = " digraph G {   subgraph cluster_1 {     label = \" Synchronizing Tree by Anurag Pal \n  \" color=yellow ; \n"  ; 
   // cout << str ;
    ans += url_encode(str) ;
    // cout << endl ;
    set <string> s ;

    for( pair<string, vector<string> > pc : children )
    {
        string ans_temp = "" ;
        string parent = convert(pc.F) ;
        // while( s.find( parent ) != s.end() ) parent+='_' ;
        // s.insert( parent );
        int count = 0 ;
        if( !(pc.S).empty() )
        for( string ch : pc.S )
        {
            string child = "" ;
            for( char x : ch )
            {
                if( x == '(' or x == ')' ) child += '_' ;
                else child += x ;
            }
            ans_temp += parent ;
            ans_temp += " -> " ;
            ans_temp += child ;
            ans_temp += " [taillabel=" ;
            ans_temp += to_string(count) ;
            ans_temp += " , color = pink]" ;
            ans_temp += "\n" ;
            // cout << parent << " -> " << child << " [taillabel=" << count << " , color = pink]"<< endl;
            count ++ ;
        }
        // while( s.find( child ) != s.end() ) child+='_' ;
        // s.insert( child );
            ans += url_encode( ans_temp ) ;
        

    }

    // cout << endl ;

    for( pair< string,int> p : colors01 )
    {
        string ans_temp = "" ;
        string parent = convert(p.F) ;

        if( homo_or_trivial[p.F] > 0 )
        {
            ans_temp += parent ;
            ans_temp += " [style=filled] \n" ;
            // cout << parent << " " << "[style=filled]" << endl ;
        }
        if( p.S )
        {
            ans_temp += parent ;
            ans_temp += " [shape=Mdiamond,color=green, label = \"" ;
            ans_temp += p.F ;
            ans_temp += "\" ] \n " ;
            // cout << parent << " " << "[shape=Mdiamond,color=green, label = \"" << p.F<<"\" ]" << endl ;
        }
        else
        {
            ans_temp += parent ;
            ans_temp += " [shape=oval,color=skyblue, label = \"" ;
            ans_temp += p.F ;
            ans_temp +=  "\" ] \n " ;
            // cout << parent << " " << "[shape=oval,color=skyblue, label = \"" << p.F<<"\" ]" << endl ;
        }
        if( treminated[p.F] > 0 )
        {
            ans_temp += parent ;
            ans_temp += " [color=red,shape=signature] \n " ;
            // cout << parent << " " << "[color=red,shape=signature]" << endl ;
        }

        ans += url_encode( ans_temp ) ;
    }

    ans += url_encode( "}} \n" ) ;
    // cout << "}}" << endl ;

    cout << endl ;
    cout << ans ;

}

/// input format
// 4
// 2 0 4 0
// 1 0 2 0
// 4 1 1 0
// 4 1 3 0

void solve(){ // write your code here
    int n ; // number of states
    cout << " Enter the number of states in your machine : " ;
    cin >> n ;
    cout << " States : " ;
       for( int i = 0 ; i < n ; i ++ ) 
       {
              char x = 'A' ;
              x = 'A'+i;
              cout << x << " " ;
       }
    cout << endl ;       
    vpi ns0(n) ; // next state, output 
    vpi ns1(n) ; // next state, output 

    for( int i = 0 ; i < n ; i++ )
    {
        char x = 'A'+i ;
        cout << "\n" ;
        cout << " For state : "<< x << " :- " << endl ;
        cout << " When INPUT = 0 : " << endl ;
        char nx ;
        cout << " Next state : " ;
        cin >> nx ;
        ns0[i].F = nx - 'A' ;
        ns0[i].F ++ ;
        cout << " Output : " ;
        cin >> ns0[i].S ;
        //>>  >> ns1[i].S ;
        cout << " When INPUT = 1 : " << endl ;
        cout << " Next state : " ;
        cin >> nx ;
        ns1[i].F = nx - 'A' ;
        ns1[i].F ++ ;
        cout << " Output : " ;
        cin >> ns1[i].S ;
    }

    string root = "" ;

    fill_root( root, n ) ;

    // bug( root ) ;

    map<string,int> non_homo ;
    vector<string> non_homo_in_this_level ;

    map<string, vector<string> > children ;

    map<string,int> homo_or_trivial ;
    map< string, int > treminated ;

    queue<string> q ;

    q.push( root ) ;
    q.push( "" ) ;
    // non_homo[ root ]++ ;

    int level = 0 ;

    map< string, int > colors01 ; // blue0 // green1

    while( !q.empty() )
    {
        // find_repeaded_non_homo 
        // find_if_full_homo 
        // find_child_0
        // find_child_1 
        char l = '0' + level ;
        char nl = '0' + level + 1 ;

        string front = q.front() ;
        q.pop() ;

        // cout << ( front ) << " " ;

        if( front == "" )
        {
            level++ ;
             // cout << endl ;
            for( string nh : non_homo_in_this_level ) non_homo[nh]++ ;
            non_homo_in_this_level = {} ;
            if( !q.empty() ) q.push(front) ;
            continue ;
        }

        if( find_repeaded_non_homo(front,non_homo)  )
        {
            
            // cout << "repeaded_non_homo - " << front << endl ;
            front += l ;
            treminated[ front ]++ ;
             continue ;
        }
        if( find_if_trivial( front ) )
        {
            // bug( front ) ;
            // cout << "full_homo - " << front << endl ;
            front += l ;
            homo_or_trivial[ front ]++ ;
            continue ;
        }

        string c0 = find_child_0( front , ns0 ) ;
        string c1 = find_child_0( front , ns1 ) ;

        fill_non_homo_components( front , non_homo_in_this_level) ;

        q.push(c0) ;
        q.push(c1) ;


        // bug( front );
        
        // bug(l);
        front += l ;
        c0 += nl ;
        c1 += nl ;
        children[ front ].pb(c0);
        children[ front ].pb(c1);

        colors01[ c0 ] = 0 ;
        colors01[ c1 ] = 1 ;
        

    }

    cout << endl ;

    print_graph( children, colors01 , homo_or_trivial, treminated ) ;
    
    cout << endl << endl << "Open the above link to view Synchronizing Tree for the given machine. " ;
}

int32_t main(){

// #ifndef ONLINE_JUDGE    //if online judge is not defined 
//     freopen("inp.txt","r",stdin);
//     freopen("out.txt","w",stdout);
// #endif  

//     // added the two lines below, this will increase the input speed
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL); 
    
//     clock_t z = clock() ;

    int t = 1 ;
    //cin >> t ;
    while( t-- ) solve();

//     cerr << "Run Time : " << ((double)( clock() - z )/ CLOCKS_PER_SEC ) << " " ;

    return 0;
}





////////// INT_MAX //// INT_MIN //// if answer will be long long /// they won't work



///// NUMBER THEORY TIPS



///////////////////// ////////////////  ABOUT GCD 

                                                                                            // gcd of (a, b, c, d ...) is equal to gcd ( a, b+c+d... ) ;

                                                                                            // so gcd of k segments of  array is just equal to gcd of one segment
                                                                                            // and sum of all other segments ...so only divide array in two.

///////////////////////////////////////////////////////
                                                                                            // vi all_primes ;

                                                                                            // void prime_sieve( int n, vi & sieve ){ //vi sieve(n+1,1) ;
                                                                                            //  for( int i = 2 ; i <= n ; i++ ){//unoptimized
                                                                                            //      if( sieve[i] == 1 ){// to optimize
                                                                                            //          all_prime.pb(i) ;
                                                                                            //          for( int j = 2*i ; j <= n ; j+=i ){// j = i*i
                                                                                            //              sieve[j] = 0 ;
                                                                                            //          }
                                                                                            //      }
                                                                                            //  }
                                                                                            // }

////////////    HOW TO FIND AlL FACTORS OF A NUMBER 

                                                                                        // -> find all prime numbers smaller than that number // or just divide by every number small that sqrt(number)

                                                                                        //  int number ;
                                                                                        //  vi factors ;
                                                                                        //  for( int prime_number : all_primes )
                                                                                        //  {
                                                                                        //      if( prime_number * prime_number > number ) break ;
                                                                                        //      if( number % prime_number == 0 )
                                                                                        //      {
                                                                                        //          factors.pb( prime_number ) ;
                                                                                        //          while( number%prime_number == 0 ) number /= prime_number ; // without this you cant fint all factors
                                                                                        //      }
                                                                                        //  }
                                                                                        //  if( number > 1 ) factors.pb( number ) ; // number will be equal to its last factor now 

///////////     PRIME SIEVE can itself tell you the smallest and largest factor of an number


//////////      HOW TO FIND ALL DIVISORS IN ROOT n TIME

                                                                                        // int sqrt_ = sqrt(num) ;

                                                                                        //  vi divisors ;
                                                                                        //  for( int i = 1 ; i <= sqrt_ ; i++ )
                                                                                        //  {
                                                                                        //      if( num%i == 0 )
                                                                                        //      {
                                                                                        //          divisors.pb(i) ;
                                                                                        //          int other = num/i ;
                                                                                        //          if( other != i ) divisors.pb(other) ;
                                                                                        //      }
                                                                                        //  }

//////////          MAXIMUM NUMBER OF DIVISORS of any n-digit number - https://oeis.org/A066150
//                  1e9 can have no more than 1300 divisors

// 
// 
// 
// 

///////////////////////      points whose SUM OF DISTANCE IS MINIMUM from all other points on a line

                                                                                        // such points lie between 2 medians of all points on line 
                                                                                        //  between ( n+1 )/2 and ( n+2 )/2 points ... of sorted set of points
//                                           CONCEPT OF MEDIAN 
                                                                                        //  EX- x=1, 4, 11, 20 // All points from x==4 to x==11 will give minimum sum of distance 

//                                      GREEDY CONCEPT OF MULTIPLICATION
     
                                                                                        // given N numbers A(N) and a number K ... Divide K into N small numbers and multiply each with one of N numbers
                                                                                        // Do all this in such a way that final answer ( SUM : Xi * ai , where SUM:Xi = K ) in minimum 
                                                                                        // Solution : optimal answer = all Xi = 1 except one Xi which is equal to ( K - (N-1) )
                                                                                        //       : multiply minimum Ai with (K-(N-1)) and multiply rest of Ai with 1
////////////////////// INTERACTIVE PROBLEMS ///////////////////////////////////////////
                                                                                        // use endl not '\n'
                                                                                        // Read the query and Answer format carefully
