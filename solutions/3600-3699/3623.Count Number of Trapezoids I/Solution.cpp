// 3623. Count Number of Trapezoids I（3623. 统计梯形的数目 I）
// 核心思路：按 y 坐标分组，同一水平线上任取两点得到一条水平底边；不同水平线各取一条底边即构成梯形。用前缀和边遍历边累加组合数。
// 复杂度：时间 O(n)（哈希计数 + 一次遍历），空间 O(n)（按 y 的行数）。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    int countTrapezoids(vector<vector<int>>& points) {  // 统计所有水平线组合出的梯形数目
        const int mod = 1e9 + 7;  // 取模常量，防止结果溢出
        unordered_map<int, int> cnt;  // 每条水平线（y 坐标）上的点数
        for (auto& p : points) {  // 遍历所有点
            cnt[p[1]]++;  // 按 y 坐标累加计数
        }
        long long ans = 0, s = 0;  // ans 为答案，s 为之前所有行可选底边数之和
        for (auto& [_, v] : cnt) {  // 遍历每一行的点数
            long long t = 1LL * v * (v - 1) / 2;  // 该行任取两点形成的底边数
            ans = (ans + s * t) % mod;  // 与之前的行两两组合，累加新梯形
            s += t;  // 把当前行计入前缀和，供后续行配对
        }
        return (int) ans;  // 转回 int 返回
    }
};
