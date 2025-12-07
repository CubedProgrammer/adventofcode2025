import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto grid = split(input, "\n"sv) | to<vector<string>>();
    size_t start = grid.front().find('S');
    set<size_t>indices{start};
    long tot = 0;
    grid.pop_back();
    for(const auto& r : grid)
    {
        unordered_set<size_t>splits;
        for(auto ind : indices)
        {
            if(r[ind] == '^')
            {
                splits.insert(ind);
                ++tot;
            }
        }
        for(auto ind : splits)
        {
            indices.erase(ind);
            indices.insert(ind-1);
            indices.insert(ind+1);
        }
        erase_if(indices, bind_back(greater_equal<>(), r.size()));
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
