import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto rotates = split(input, "\n"sv) | to<vector<string>>();
    rotates.pop_back();
    int tot = 50;
    int zeros = 0;
    for(auto i : rotates)
    {
        auto q = i.substr(1);
        int count = stoi(q);
        tot += i.front() == 'R' ? count : -count;
        zeros += tot % 100 == 0;
    }
    return zeros;
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
