import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto reds = split(input, "\n"sv) | to<vector<string>>();
    reds.pop_back();
    vector<valarray<long>>coords;
    for(const string& s : reds)
    {
        size_t ind = s.find(',');
        long x = stol(s.substr(0, ind));
        long y = stol(s.substr(ind + 1));
        coords.push_back({x, y});
    }
    long maxi = 0;
    for(long unsigned i : views::iota(0zu, coords.size()))
    {
        for(long unsigned j : views::iota(i + 1, coords.size()))
        {
            valarray<long>diff = coords[i] - coords[j] + 1;
            maxi = max(maxi, abs(diff[0] * diff[1]));
        }
    }
    return maxi;
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
