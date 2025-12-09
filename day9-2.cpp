import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
void floodfill(vector<vector<int>>& shape, size_t x, size_t y, int v)
{
    queue<pair<size_t, size_t>>q;
    int old = shape[y][x];
    q.emplace(x, y);
    while(q.size())
    {
        auto[nx, ny] = q.front();
        q.pop();
        if(ny < shape.size() && nx < shape[ny].size())
        {
            if(shape[ny][nx] == old)
            {
                shape[ny][nx] = v;
                q.emplace(nx - 1, ny);
                q.emplace(nx, ny - 1);
                q.emplace(nx + 1, ny);
                q.emplace(nx, ny + 1);
            }
        }
    }
}
auto solve(const string& input)
{
    auto reds = split(input, "\n"sv) | to<vector<string>>();
    reds.pop_back();
    vector<valarray<long>>coords;
    vector<long>xs, ys;
    xs.push_back(0);
    ys.push_back(0);
    for(const string& s : reds)
    {
        size_t ind = s.find(',');
        long x = stol(s.substr(0, ind));
        long y = stol(s.substr(ind + 1));
        coords.push_back({x, y});
        xs.push_back(x);
        ys.push_back(y);
    }
    ranges::sort(xs);
    ranges::sort(ys);
    auto rmx = ranges::unique(xs);
    auto rmy = ranges::unique(ys);
    xs.erase(rmx.begin(), rmx.end());
    ys.erase(rmy.begin(), rmy.end());
    xs.push_back(999999);
    ys.push_back(999999);
    coords.push_back(coords.front());
    vector<vector<int>>grid(ys.size(), vector<int>(xs.size(), 1));
    long maxi = 0;
    for(const auto& [u, v] : pairwise(coords))
    {
        if(u[0] == v[0])
        {
            auto[small, large] = minmax(u[1], v[1]);
            auto smallIt = ranges::lower_bound(ys, small);
            auto largeIt = ranges::upper_bound(ys, large);
            auto currentIt = ranges::lower_bound(xs, v[0]);
            for(auto it : views::iota(smallIt, largeIt))
            {
                grid[it - ys.begin()][currentIt - xs.begin()] = 2;
            }
        }
        else
        {
            auto[small, large] = minmax(u[0], v[0]);
            auto smallIt = ranges::lower_bound(xs, small);
            auto largeIt = ranges::upper_bound(xs, large);
            auto currentIt = ranges::lower_bound(ys, v[1]);
            for(auto it : views::iota(smallIt, largeIt))
            {
                grid[currentIt - ys.begin()][it - xs.begin()] = 2;
            }
        }
    }
    floodfill(grid, ys.size() - 1, xs.size() - 1, 3);
    for(long unsigned i : views::iota(0zu, coords.size()))
    {
        for(long unsigned j : views::iota(i + 1, coords.size()))
        {
            valarray<long>diff = abs(coords[i] - coords[j]) + 1;
            long area = diff[0] * diff[1];
            auto [smallX, largeX] = minmax(coords[i][0], coords[j][0]);
            auto [smallY, largeY] = minmax(coords[i][1], coords[j][1]);
            auto smallXIt = ranges::lower_bound(xs, smallX);
            auto largeXIt = ranges::upper_bound(xs, largeX);
            auto smallYIt = ranges::lower_bound(ys, smallY);
            auto largeYIt = ranges::upper_bound(ys, largeY);
            bool allin = true;
            for(auto yIt : views::iota(smallYIt, largeYIt))
            {
                for(auto xIt : views::iota(smallXIt, largeXIt))
                {
                    allin = allin && grid[yIt - ys.begin()][xIt - xs.begin()] <= 2;
                }
            }
            if(allin)
            {
                maxi = max(maxi, area);
            }
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
