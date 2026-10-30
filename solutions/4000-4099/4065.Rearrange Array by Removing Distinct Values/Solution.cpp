// 4065. 移除不同值重排数组  Rearrange Array by Removing Distinct Values
// 核心思路：统计每个数值的出现次数，然后一轮轮按数值升序把剩余元素依次取出，即可让相等的数尽量不相邻。
// 复杂度：时间 O(n * mx)，空间 O(mx)，其中 mx 为数组最大值。

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {  // 返回重排后的数组
        int mx = ranges::max(nums);  // 数组中的最大值，用于确定计数数组大小
        vector<int> cnt(mx + 1);  // 计数数组，统计每个数值出现的次数
        for (int x : nums) {  // 遍历原数组做计数
            cnt[x]++;  // 数值 x 的计数加一
        }

        vector<int> ans;  // 存放重排结果
        while (ans.size() < nums.size()) {  // 结果长度不足时继续按轮次填充
            for (int x = 1; x <= mx; x++) {  // 每轮按数值升序枚举
                if (cnt[x]) {  // 该数值还有剩余
                    ans.push_back(x);  // 追加到结果末尾
                    cnt[x]--;  // 剩余数量减一
                }
            }
        }
        return ans;  // 返回重排后的数组
    }
};