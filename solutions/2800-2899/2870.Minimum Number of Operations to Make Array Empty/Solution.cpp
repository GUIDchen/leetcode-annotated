// 题目：2870. 使数组为空的最少操作次数（Minimum Number of Operations to Make Array Empty）
// 思路：先统计每个值的出现次数，次数为 1 则无解；否则尽量每次删 3 个，最少操作数为 ceil(c / 3) = (c + 2) / 3。
// 时间复杂度：O(n)，统计词频与遍历哈希表各 O(n)；空间复杂度：O(n)，哈希表存不同数值的计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums) {  // nums 为输入数组，返回最少操作次数（无解返回 -1）
        unordered_map<int, int> count;  // 哈希表：键是元素值，值是它出现的次数
        for (int num : nums) {  // 遍历数组做词频统计
            ++count[num];  // 当前值的计数加一
        }  // 统计结束
        int ans = 0;  // 累计最少操作次数
        for (auto& [_, c] : count) {  // 结构化绑定逐个取出「值（不重要，用 _ 忽略）→ 次数 c」
            if (c < 2) {  // 只剩 1 个该值：既不能一次删 2 个也不能一次删 3 个，无解
                return -1;  // 直接返回 -1 表示无法清空数组
            }  // 无解判断结束
            ans += (c + 2) / 3;  // ceil(c / 3)：整数除法补上 2 即实现向上取整，删 3 个最优
        }  // 所有数值处理完毕
        return ans;  // 返回最少操作次数
    }  // 方法结束
};  // 类定义结束