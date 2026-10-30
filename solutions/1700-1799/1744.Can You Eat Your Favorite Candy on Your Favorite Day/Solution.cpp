// 题目：1744. 你能在你最喜欢的那天吃到你最喜欢的糖果吗？（Can You Eat Your Favorite Candy on Your Favorite Day）
// 思路：对糖果数做前缀和得到第 t 类糖果的下标区间 [s[t], s[t+1])；前 day 天必吃的数量范围是 [day, (day+1)*mx]，两个区间有交集即可行。
// 时间复杂度：O(n + q)，预处理前缀和 O(n)、每条询问 O(1)；空间复杂度：O(n)，前缀和数组。
using ll = long long;  // 给长整型起别名，避免 (day+1)*mx 这类乘法在 int 上溢出

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {  // 逐条回答询问
        int n = candiesCount.size();  // 糖果的种类数
        vector<ll> s(n + 1);  // 前缀和：s[i] 表示第 0 类到第 i-1 类糖果的累计数量
        for (int i = 0; i < n; ++i) s[i + 1] = s[i] + candiesCount[i];  // 递推求前缀和，写成一行更紧凑
        vector<bool> ans;  // 按询问顺序保存每条询问的答案
        for (auto& q : queries) {  // 逐条处理询问
            int t = q[0], day = q[1], mx = q[2];  // t：最喜欢的糖果种类；day：最喜欢的第几天（从 0 起）；mx：每天最多吃几颗
            ll least = day, most = 1ll * (day + 1) * mx;  // 前 day 天最少吃 day 颗（每天至少 1 颗），最多吃 (day+1)*mx 颗
            ans.emplace_back(least < s[t + 1] && most > s[t]);  // 必须吃到的最少颗数还没越过该种类末位、且最多颗数已越过该种类首位，才存在交集
        }
        return ans;  // 返回所有询问的答案
    }
};