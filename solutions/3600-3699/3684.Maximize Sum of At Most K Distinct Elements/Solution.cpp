// 3684. Maximize Sum of At Most K Distinct Elements（3684. 至多 K 个不同元素的最大和）
// 核心思路：先升序排序，再从后往前挑选最大的 k 个互不相同的元素，跳过与前一个位置重复的值。
// 复杂度：时间 O(n log n)，空间 O(k)。
class Solution {  // 题解类
public:  // 公有接口，供判题器调用
    vector<int> maxKDistinct(vector<int>& nums, int k) {  // 返回和最大的至多 k 个不同元素
        ranges::sort(nums);  // 升序排序，方便从最大值开始挑选
        int n = nums.size();  // 数组长度
        vector<int> ans;  // 保存选出的答案
        for (int i = n - 1; ~i; --i) {  // 从末尾（最大值）向前遍历，~i 等价于 i >= 0
            if (i + 1 < n && nums[i] == nums[i + 1]) {  // 与后一个位置的值重复，跳过以保证元素互不相同
                continue;  // 继续看下一个更小的值
            }
            ans.push_back(nums[i]);  // 选入这个不重复的大值
            if (--k == 0) {  // 剩余可选个数减一，已选够 k 个
                break;  // 提前结束
            }
        }
        return ans;  // 返回选出的元素
    }
};
