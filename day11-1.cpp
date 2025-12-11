import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto ilines = split(input, "\n"sv) | to<vector<string>>();
    unordered_map<string, vector<string>>graph;
    unordered_map<string, long>mem;
    string start = "you";
    ilines.pop_back();
    for(const string& line : ilines)
    {
        size_t ind = line.find(':');
        string from = line.substr(0, ind);
        string toStr = line.substr(ind+2);
        auto toArr = split(toStr, " "sv) | to<vector<string>>();
        graph.insert({std::move(from), std::move(toArr)});
    }
    mem.insert({start, 1});
    queue<string>q;
    q.push(start);
    while(q.size())
    {
        string s = q.front();
        q.pop();
        long& cnt = mem[s];
        for(const string& dest : graph[s])
        {
            mem[dest] += cnt;
            q.push(dest);
        }
        if(s != "out")
        {
            cnt = 0;
        }
    }
    return mem["out"];
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
