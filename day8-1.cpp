import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
struct DSU
{
    vector<long>roots, sizes;
    DSU(long unsigned size)
        :roots(size), sizes(size, 1)
    {
        ranges::copy(views::iota(0l, (long)size), roots.begin());
    }
    long findroot(long n)
        noexcept
    {
        long m = n;
        for(; n != roots[n]; n = roots[n]);
        for(; m != roots[m]; m = exchange(roots[m], n));
        return n;
    }
    bool merge(long x, long y)
        noexcept
    {
        x = findroot(x);
        y = findroot(y);
        bool m = x != y;
        if(m)
        {
            roots[x] = y;
            sizes[y] += sizes[x];
        }
        return m;
    }
    auto getRoots()
        const noexcept
    {
        auto&r = roots;
        return filter(views::iota(0l, (long)roots.size()), [&r](long m){return m == r[m];});
    }
    long getsize(long n)
        noexcept
    {
        return sizes[findroot(n)];
    }
};
auto solve(const string& input)
{
    auto tmp = split(input, "\n"sv) | to<vector<string>>();
    tmp.pop_back();
    vector<valarray<long>>points;
    vector<array<long, 3>>edges;
    points.reserve(tmp.size());
    for(const string& s : tmp)
    {
        auto arr = to<vector<string>>(split(s, ","sv));
        auto parsed = views::transform(arr, [](const auto&m){return stol(m);});
        points.push_back({parsed[0], parsed[1], parsed[2]});
    }
    for(long unsigned i : views::iota(0lu, points.size()))
    {
        for(long unsigned j : views::iota(i+1, points.size()))
        {
            valarray<long>diff = points[i] - points[j];
            edges.push_back({(diff * diff).sum(), (long)i, (long)j});
        }
    }
    ranges::sort(edges);
    unsigned merged = 0;
    DSU dsu(points.size());
    for(const auto& [dist, x, y] : edges)
    {
        dsu.merge(x, y);
        ++merged;
        if(merged == 1000)
        {
            break;
        }
    }
    vector<long>sizes;
    for(long i : dsu.getRoots())
    {
        sizes.push_back(dsu.getsize(i));
    }
    ranges::sort(sizes);
    return ranges::fold_left(take(views::reverse(sizes), 3), 1, multiplies<>());
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
