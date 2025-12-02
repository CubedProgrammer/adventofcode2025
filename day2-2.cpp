import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    auto check = [](long n)
    {
        string s = format("{}", n);
        for(int i : views::iota(2zu, 1+s.size()))
        {
            if(s.size() % i == 0)
            {
                auto chunks = chunk(s, s.size() / i) | pairwise;
                if(ranges::all_of(chunks, [](const auto& p){return ranges::equal(get<0>(p), get<1>(p));}))
                {
                    return true;
                }
            }
        }
        return false;
    };
    auto partials = split(input, ","sv) | to<vector<string>>() | views::transform([check](const string&s){
        auto ind = s.find('-');
        auto repeats = views::iota(stol(s.substr(0, ind)), 1+stol(s.substr(ind + 1))) | filter(check);
        return ranges::fold_left(repeats, 0l, plus<>());
    });
    return ranges::fold_left(partials, 0l, plus<>());
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
