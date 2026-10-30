// 题目：2857. 统计距离为 k 的点对（Count Pairs of Points With Distance k）
// 思路：把 (x1^x2)+(y1^y2)=k 拆成 a+b=k，枚举 a 反解出 x1=a^x2、y1=b^y2，用 map 统计已经出现过的点。
// 复杂度：时间 O(n·k·log n)，每个点枚举 k+1 个 a 且每次查表 O(log n)；空间 O(n)，map 最多存 n 个不同点。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPairs(vector<vector<int>>& coordinates, int k) {  // coordinates：全部点；k：x、y 两部分异或距离之和
        map<pair<int, int>, int> cnt;  // 统计表：键是点 (x, y)，值是它已经出现的次数
        int ans = 0;  // 记录满足条件的点对数量
        for (auto& c : coordinates) {  // 依次把当前点当作右边的 (x2, y2)
            int x2 = c[0], y2 = c[1];  // 取出当前点的横纵坐标
            for (int a = 0; a <= k; ++a) {  // 枚举 a：分配给 x 方向的异或值，范围 0..k
                int b = k - a;  // b 是 y 方向剩下的异或值，保证 a + b == k
                int x1 = a ^ x2, y1 = b ^ y2;  // 由 x1 ^ x2 == a 反解 x1 = a ^ x2，y1 同理
                ans += cnt[{x1, y1}];  // 之前出现过的 (x1, y1) 每个都能与当前点配成一对
            }
            ++cnt[{x2, y2}];  // 当前点最后才计数，避免自己与自己配对
        }
        return ans;  // 返回合法点对总数
    }
};