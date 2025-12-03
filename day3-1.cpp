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
        for(auto i : views::iota(0zu, b.size()))
        {
            for(auto j : views::iota(i+1, b.size()))
            {
                long num = (b[i] - '0') * 10 + (b[j] - '0');
                maxi = max(maxi, num);
            }
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
