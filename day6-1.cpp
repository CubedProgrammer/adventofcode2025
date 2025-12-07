import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto linesRawLazy = split(input, "\n"sv) | views::transform([](const auto&m){return filter(split(m, " "sv), [](const auto&m){return m.size();});});
    auto linesRaw = to<vector<vector<string>>>(linesRawLazy);
    linesRaw.pop_back();
    long tot = 0;
    for(const auto& [index, op]: enumerate(linesRaw.back()))
    {
        if(op.front() == '+')
        {
            tot += ranges::fold_left(views::transform(take(linesRaw, linesRaw.size()-1), [index](const auto&m){return stol(m[index]);}), 0l, plus<>());
        }
        else
        {
            tot += ranges::fold_left(views::transform(take(linesRaw, linesRaw.size()-1), [index](const auto&m){return stol(m[index]);}), 1l, multiplies<>());
        }
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
