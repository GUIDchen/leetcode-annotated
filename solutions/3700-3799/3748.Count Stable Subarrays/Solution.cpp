// 题目：3748. 统计稳定子数组的数目（Count Stable Subarrays）
// 核心思路：稳定子数组即非降序子数组，先把 nums 按降序断点切成若干非降序段，记录每段起点与「段内答案数」的前缀和；对每个查询用两次二分定位左右端点所属的段，同一段内直接算三角形数，跨段时用「左残段 + 中间整段前缀和之差 + 右残段」拼出答案。
// 复杂度：时间 O(n + q log n)，扫描一遍分段、每个查询两次二分；空间 O(n)，段起点数组与答案前缀和数组各占一份。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {  // nums 为原数组，queries 的每个元素是 [l, r]，返回每个查询内稳定子数组的个数
        int n = nums.size();  // n 是数组长度
        vector<int> seg;  // seg 记录每个非降序段的起始下标，起点天然递增，便于二分
        vector<long long> s = {0};  // s 是段内稳定子数组个数的前缀和，s[k] 表示前 k 段的答案之和

        int l = 0;  // l 是当前非降序段的左端点
        for (int r = 0; r < n; ++r) {  // r 从左到右扫描，寻找每一段的右端点
            if (r == n - 1 || nums[r] > nums[r + 1]) {  // 已到末尾，或出现降序断点，说明当前段在 r 处结束
                seg.push_back(l);  // 记下这一段的起始下标
                long long k = r - l + 1;  // k 是这一段的长度
                s.push_back(s.back() + k * (k + 1) / 2);  // 长度为 k 的段内共有 k(k+1)/2 个非降序子数组，累加进前缀和
                l = r + 1;  // 下一段的左端点从 r+1 开始
            }  // if 分支结束
        }  // 分段结束

        vector<long long> ans;  // ans 按查询顺序存放每个查询的答案
        for (auto& q : queries) {  // 依次处理每个查询
            int left = q[0], right = q[1];  // 查询区间是闭区间 [left, right]

            int i = upper_bound(seg.begin(), seg.end(), left) - seg.begin();  // i 是第一个起点大于 left 的段下标，说明 left 落在第 i-1 段里
            int j = upper_bound(seg.begin(), seg.end(), right) - seg.begin() - 1;  // j 是最后一个起点不大于 right 的段下标，说明 right 落在第 j 段里

            if (i > j) {  // i > j 说明 left 与 right 在同一段内，整个查询区间都是非降序的
                long long k = right - left + 1;  // k 是查询区间的长度
                ans.push_back(k * (k + 1) / 2);  // 区间内任意子数组都稳定，共 k(k+1)/2 个
            } else {  // 否则查询区间跨越多个段，需要拆成三部分计算
                long long a = seg[i] - left;  // a 是左端残段的长度（从 left 到第 i 段起点之前）
                long long b = right - seg[j] + 1;  // b 是右端残段的长度（从第 j 段起点到 right）
                ans.push_back(a * (a + 1) / 2 + s[j] - s[i] + b * (b + 1) / 2);  // 左残段 + 中间整段（前缀和之差）+ 右残段，各自套用三角形数
            }  // 分支结束
        }  // 查询处理结束

        return ans;  // 返回每个查询对应的稳定子数组个数
    }  // 方法结束
};  // 类定义结束
