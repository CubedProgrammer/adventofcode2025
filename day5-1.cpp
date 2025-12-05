import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto parts = split(input, "\n\n"sv) | to<vector<string>>();
    auto rgs = parts.front();
    auto ingredients = parts.back();
    auto rangeArr = split(rgs, "\n"sv) | to<vector<string>>();
    auto ingArr = split(ingredients, "\n"sv) | to<vector<string>>();
    vector<pair<long,long>>intervals;
    ingArr.pop_back();
    unsigned tot = 0;
    for(const string& s : rangeArr)
    {
        auto ind = s.find('-');
        intervals.emplace_back(stol(s.substr(0, ind)), stol(s.substr(ind+1)));
    }
    for(const string& s : ingArr)
    {
        long n = stol(s);
        tot += ranges::any_of(intervals, [n](const auto&m){return m.second >= n && n >= m.first;});
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
