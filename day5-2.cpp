import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto parts = split(input, "\n\n"sv) | to<vector<string>>();
    auto rgs = parts.front();
    auto rangeArr = split(rgs, "\n"sv) | to<vector<string>>();
    vector<pair<long,long>>intervals;
    for(const string& s : rangeArr)
    {
        auto ind = s.find('-');
        intervals.emplace_back(stol(s.substr(0, ind)), stol(s.substr(ind+1)));
    }
    ranges::sort(intervals);
    long mini = 0;
    long tot = 0;
    for(const auto& [x, y] : intervals)
    {
        if(x > mini)
        {
            tot += y - x + 1;
        }
        else if(mini <= y)
        {
            tot += y - mini + 1;
        }
        mini = max(y+1, mini);
    }
    return tot;
}
string read_entire_file(std::istream& is)
{
    string s;
    array<char, 1024>buf;
    while(is.read(buf.data(), buf.size()))
        s.append_range(take(buf, is.gcount()));
    s.append_range(take(buf, is.gcount()));
    return s;
}
int main(int argl,char**argv)
{
    string i = read_entire_file(cin);
    println("{}", solve(i));
    return 0;
}
