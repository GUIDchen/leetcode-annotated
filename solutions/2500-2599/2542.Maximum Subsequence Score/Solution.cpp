// 题目：2542. 最大子序列的分数（Maximum Subsequence Score）
// 思路：把 (nums2, nums1) 按 nums2 降序排序后逐个加入，用最小堆维护最大的 k 个 nums1；此时当前 nums2 就是所选集合的最小值。
// 时间复杂度：O(n log n)，排序加堆操作；空间复杂度：O(n)，存放二元组与堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {  // 返回选 k 个下标时 sum(nums1) * min(nums2) 的最大值
        int n = nums1.size();  // 数组长度，两个数组等长
        vector<pair<int, int>> nums(n);  // 把两个数组打包成 (值, 权重) 二元组数组，便于一起排序
        for (int i = 0; i < n; ++i) {  // 按下标逐个打包
            nums[i] = {-nums2[i], nums1[i]};  // 把 nums2 取负当第一关键字，这样默认升序排序就等价于按 nums2 降序
        }  // 结束打包
        sort(nums.begin(), nums.end());  // 排序后 nums2 从大到小排列，第一个被选中的元素就是当前集合里 nums2 最小的那个
        priority_queue<int, vector<int>, greater<int>> q;  // 小顶堆，保存当前选中的 nums1 值，堆顶是最小值，方便淘汰
        long long ans = 0, s = 0;  // ans 记录历史最优分数，s 维护堆中元素之和
        for (auto& [a, b] : nums) {  // 按 nums2 从大到小遍历；a 是 -nums2，b 是 nums1
            s += b;  // 把当前 nums1 计入候选和
            q.push(b);  // 同时压入小顶堆，堆里始终是已选中的 nums1
            if (q.size() == k) {  // 凑满 k 个元素就尝试更新答案
                ans = max(ans, s * -a);  // 分数 = 选中的 nums1 之和 × 选中集合中最小的 nums2，即 s * (-a)
                s -= q.top();  // 为了给后面的元素腾位置，先减去堆中最小的 nums1
                q.pop();  // 再把它从堆里弹出
            }  // 结束答案更新
        }  // 结束遍历
        return ans;  // 返回最大分数
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，保持原样）