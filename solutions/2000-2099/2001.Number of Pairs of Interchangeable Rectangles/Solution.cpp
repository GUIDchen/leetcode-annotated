// 题目：2001. 可互换矩形的组数（Number of Pairs of Interchangeable Rectangles）
// 思路：把每个矩形的宽高比约分成最简分数，用哈希表统计相同比例出现的次数，每遇到一个就与之前所有同比例矩形配对。
// 时间复杂度：O(n log C)，每次求一次 gcd；空间复杂度：O(n)，哈希表存放不同比例的计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {  // rectangles：每个元素是 [宽, 高]
        long long ans = 0;  // ans 统计可互换矩形对数，可能超过 int 范围
        unordered_map<long long, int> cnt;  // 键是约分后比例的编码，值是这种比例已出现的次数
        for (auto& e : rectangles) {  // 逐个枚举矩形
            int w = e[0], h = e[1];  // 取出宽与高
            int g = gcd(w, h);  // 求宽高的最大公因数，用于约分
            w /= g;  // 把宽化为最简形式
            h /= g;  // 把高化为最简形式，宽高比保持不变
            long long x = 1LL * w * 100001 + h;  // 用基数 100001 把最简分数对 (w, h) 编码成一个 long long 键
            ans += cnt[x];  // 当前矩形能与之前所有同比例的矩形配对，累加对数
            cnt[x]++;  // 把当前矩形计入该比例的出现次数
        }
        return ans;  // 返回可互换矩形的总组数
    }
};