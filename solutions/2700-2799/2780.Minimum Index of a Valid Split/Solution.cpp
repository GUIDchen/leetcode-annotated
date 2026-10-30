// 题目：2780. 合法分割的最小下标（Minimum Index of a Valid Split）
// 思路：若某个分割合法，两段的主导元素必然相同，所以它只能是全局出现次数最多的元素 x；先统计 x 的总频次，再从前往后枚举分割点，检查两段中 x 都严格过半。
// 时间复杂度：O(n)，两次线性扫描（哈希表均摊 O(1)）；空间复杂度：O(n)，最坏要存 n 个不同元素。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int minimumIndex(vector<int>& nums) {  // nums 是输入数组
        int x = 0, cnt = 0;  // x 记录出现次数最多的元素，cnt 记录它的出现次数
        unordered_map<int, int> freq;  // 哈希表：键是元素值，值是它当前出现的次数
        for (int v : nums) {  // 第一遍扫描：统计频次并找出主导元素
            ++freq[v];  // 当前元素 v 的频次加一
            if (freq[v] > cnt) {  // 该元素频次超过目前记录的最大频次
                cnt = freq[v];  // 更新最大频次
                x = v;  // 同时更新主导元素
            }
        }
        int cur = 0;  // 前缀（左段）中主导元素 x 已经出现的次数
        for (int i = 1; i <= nums.size(); ++i) {  // 枚举左段长度 i，即以 i - 1 为分割下标
            if (nums[i - 1] == x) {  // 当前元素属于主导元素，左段计数才需要增加
                ++cur;  // 左段中 x 的出现次数加一
                if (cur * 2 > i && (cnt - cur) * 2 > nums.size() - i) {  // 左段 x 过半，且右段剩余 x 也过半
                    return i - 1;  // 找到最靠左的合法分割下标，直接返回
                }
            }
        }
        return -1;  // 所有分割都不合法，按题意返回 -1
    }
};