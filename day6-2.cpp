import std;
using namespace std;
using namespace literals;
using namespace views;
using ranges::to;
auto solve(const string& input)
{
    size_t length = input.find('\n');
    auto lazy = views::iota(0zu, length) | views::transform([length, &input](const auto&m){return stride(drop(input, m), length + 1);});
    auto columns = to<vector<string>>(lazy);
    long tot = 0;
    function<long(long, long)>func;
    vector<long>nums;
    long id = 0;
    for(string s : columns)
    {
        if(s.back() == '+')
        {
            func = plus<long>();
            id = 0;
        }
        else if(s.back() == '*')
        {
            func = multiplies<long>();
            id = 1;
        }
        if(ranges::count(s, ' ') == s.size())
        {
            tot += ranges::fold_left(nums, id, func);
            nums.clear();
        }
        else
        {
            erase(s, ' ');
            nums.push_back(stol(s));
        }
    }
    tot += ranges::fold_left(nums, id, func);
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
