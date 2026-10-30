// 4066. 至多一次替换后的最大相邻相等元素对数  Maximum Equal Adjacent Pairs After at Most One Replacement
// 核心思路：先统计原本就相等的相邻对数，再把出现次数最多的一种“不等相邻数对”整体变成相等（一次替换即可全部生效）。
// 复杂度：时间 O(n)，空间 O(n)。

class Solution {
public:
    int maxEqualAdjacentPairs(vector<int>& nums) {  // 返回至多一次替换后相邻相等元素对的最大数量
        unordered_map<long long, int> cnt;  // 统计每种无序相邻数对出现的次数
        int ans = 0, mx = 0;  // ans 为原有相等对数，mx 为某数对出现次数的最大值

        for (int i = 0; i + 1 < nums.size(); i++) {  // 遍历所有相邻数对
            int x = nums[i], y = nums[i + 1];  // 取出相邻的两个元素
            if (x == y) {  // 二者已经相等
                ans++;  // 直接计入答案
            } else {  // 二者不相等，记录下来以便替换后合并
                if (x > y) {  // 统一成 (小, 大) 的有序形式
                    swap(x, y);  // 交换两数
                }
                long long key = ((long long) x << 30) | y;  // 用位运算把数对压成一个整数键
                mx = max(mx, ++cnt[key]);  // 该数对计数加一，并维护计数最大值
            }
        }
        ans += mx;  // 替换一个元素可让出现最多的那种数对全部变得相等
        return ans;  // 返回最大相邻相等对数
    }
};