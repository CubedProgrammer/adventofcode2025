import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto grid = split(input, "\n"sv) | to<vector<string>>();
    size_t start = grid.front().find('S');
    unordered_map<size_t, long>indices{{start, 1}};
    grid.pop_back();
    valarray<valarray<long>>mem(valarray<long>(grid[0].size()), grid.size());
    mem[0][start] = 1;
    for(const auto& [ri, r] : enumerate(grid))
    {
        unordered_set<size_t>splits;
        for(auto [ind, cnt] : indices)
        {
            if(r[ind] == '^')
            {
                splits.insert(ind);
                mem[ri][ind] -= cnt;
            }
        }
        for(auto ind : splits)
        {
            auto it = indices.find(ind);
            if(ind > 0)
            {
                indices[ind-1] += it->second;
                mem[ri][ind-1] += it->second;
            }
            if(ind < mem[ri].size() - 1)
            {
                indices[ind+1] += it->second;
                mem[ri][ind+1] += it->second;
            }
            indices.erase(it);
        }
    }
    return mem.sum().sum();
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
