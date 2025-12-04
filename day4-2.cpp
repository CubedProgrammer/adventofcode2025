import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto lines = split(input, "\n"sv) | to<vector<string>>();
    lines.pop_back();
    auto directions = cartesian_product(views::iota(-1, 2), views::iota(-1, 2));
    int count = 0;
    int removed = 1;
    while(removed > 0)
    {
        removed = 0;
        for(const auto& [i, r] : enumerate(lines))
        {
            for(const auto& [j, v] : enumerate(r))
            {
                if(v == '@')
                {
                    int adjacent = 0;
                    for(auto[x, y] : directions)
                    {
                        size_t ni = i + y;
                        size_t nj = j + x;
                        adjacent += ni < lines.size() && nj < r.size() && lines[ni][nj] == '@';
                    }
                    if(adjacent <= 4)
                    {
                        ++removed;
                        v = '.';
                    }
                }
            }
        }
        count += removed;
    }
    return count;
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
