import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
long countPaths(const unordered_map<string, vector<string>>&g, const string& from, const string& to)
{
    stack<tuple<unsigned, string, int, long>>mem;
    map<pair<string, int>, long>c;
    long value = 0;
    mem.push({0, from, 0, 0});
    while(mem.size())
    {
        auto[ind, node, seen, cnt] = mem.top();
        auto it = g.find(node);
        if(it == g.end() || ind == it->second.size())
        {
            cnt += node == to && seen == 2;
            if(node != to)
            {
                c.emplace(pair<string, int>{node, seen}, cnt);
            }
            mem.pop();
            if(mem.size())
            {
                auto& [lInd, lNode, lSeen, lCnt] = mem.top();
                lCnt += cnt;
                ++get<0>(mem.top());
            }
            else
            {
                value = cnt;
            }
        }
        else
        {
            seen += it->second[ind] == "dac" || it->second[ind] == "fft";
            if(auto cacheIt = c.find({it->second[ind], seen}); cacheIt != c.end())
            {
                ++get<0>(mem.top());
                get<3>(mem.top()) += cacheIt->second;
            }
            else
            {
                mem.push({0, it->second[ind], seen, 0});
            }
        }
    }
    return value;
}
auto solve(const string& input)
{
    auto ilines = split(input, "\n"sv) | to<vector<string>>();
    unordered_map<string, vector<string>>graph;
    ilines.pop_back();
    for(const string& line : ilines)
    {
        size_t ind = line.find(':');
        string from = line.substr(0, ind);
        string toStr = line.substr(ind+2);
        auto toArr = split(toStr, " "sv) | to<vector<string>>();
        graph.insert({std::move(from), std::move(toArr)});
    }
    return countPaths(graph, "svr", "out");
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
