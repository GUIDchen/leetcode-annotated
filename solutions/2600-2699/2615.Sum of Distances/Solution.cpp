// 题目：2615. 等值距离和（Sum of Distances）
// 思路：按值分组记录下标（天然升序），组内用前缀贡献 left 与后缀贡献 right 递推：向右移动一格时，左侧元素贡献增加 gap，右侧元素贡献减少 gap。
// 时间复杂度：O(n)，每个下标只在所属组里被访问两次；空间复杂度：O(n)，哈希表保存全部分组下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> distance(vector<int>& nums) {  // nums 是输入数组；返回每个下标到同值下标距离之和
        int n = nums.size();  // 数组长度
        vector<long long> ans(n);  // 答案数组，距离和可能超过 int 范围所以用 long long
        unordered_map<int, vector<int>> d;  // 值 -> 该值出现的所有下标（按遍历顺序天然升序）
        for (int i = 0; i < n; ++i) {  // 一次遍历完成分组
            d[nums[i]].push_back(i);  // 把下标追加到对应值的列表末尾
        }  // 分组结束
        for (auto& [_, idx] : d) {  // 逐个值独立计算，不同值之间互不影响
            int m = idx.size();  // 该值出现的次数
            long long left = 0;  // 左侧贡献：当前元素左边所有同值元素到它的距离和
            long long right = -1LL * m * idx[0];  // 右侧贡献初值 sum(idx) - m * idx[0]，下面再把 sum 累加进来
            for (int i : idx) {  // 累加该组所有下标
                right += i;  // 累加完成后 right 恰为 idx[0] 的右侧距离和
            }  // 累加结束
            for (int i = 0; i < m; ++i) {  // 按出现顺序依次求每个下标的答案
                ans[idx[i]] = left + right;  // 左右贡献相加即为该下标的总距离和
                if (i + 1 < m) {  // 还有下一个同值下标，需要把贡献从 i 迁移到 i + 1
                    left += (idx[i + 1] - idx[i]) * 1LL * (i + 1);  // 左侧 i+1 个元素各被拉远 gap，贡献增加 gap*(i+1)
                    right -= (idx[i + 1] - idx[i]) * 1LL * (m - i - 1);  // 右侧剩余 m-i-1 个元素各被拉近 gap，贡献减少 gap*(m-i-1)
                }  // 迁移结束
            }  // 组内枚举结束
        }  // 所有值处理完毕
        return ans;  // 返回所有下标的结果
    }  // 方法结束
};  // 题解类结束