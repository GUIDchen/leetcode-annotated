// 题目：2206. 将数组划分成相等数对（Divide Array Into Equal Pairs）
// 核心思路：能划分成相等数对，当且仅当每个数值出现的次数都是偶数；用计数数组统计频次后逐个检查奇偶性。
// 时间复杂度：O(n + U)，n 是数组长度、U = 500 是值域；空间复杂度：O(U)，一张计数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool divideArray(vector<int>& nums) {  // nums 是待划分的数组
        int cnt[510]{};  // 计数数组，值域是 1..500 所以开 510 足够，{} 把全部元素初始化为 0
        for (int x : nums) {  // 遍历数组中的每个元素
            ++cnt[x];  // 累加数值 x 的出现次数
        }
        for (int i = 1; i <= 500; ++i) {  // 按可能的取值逐个检查频次
            if (cnt[i] % 2) {  // 频次是奇数，说明这个值必然剩下一个配不成对
                return false;  // 立即判定无法划分
            }
        }
        return true;  // 所有频次都是偶数，可以两两配对
    }
};
