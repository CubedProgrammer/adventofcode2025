import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto banks = split(input, "\n"sv) | to<vector<string>>();
    banks.pop_back();
    long tot = 0;
    for(const string& b : banks)
    {
        long maxi = 0;
        size_t offset = 0;
        auto parts = slide(b, b.size() - 11);
        for(auto p : parts)
        {
            offset = ranges::max_element(drop(p, offset)) - p.begin();
            maxi *= 10;
            maxi += p[offset] - '0';
        }
        tot += maxi;
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
