// 题目：2616. 最小化数对的最大差值（Minimize the Maximum Difference of Pairs）
// 思路：排序后最优配对一定发生在相邻元素之间；对答案 diff 二分，用贪心从左往右扫描，能配就配，判断「差值不超过 diff」能否凑出至少 p 对。
// 时间复杂度：O(n log n + n log(maxDiff))，排序加二分判定；空间复杂度：O(1)，只用常数个额外变量（排序本身不计入）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimizeMax(vector<int>& nums, int p) {  // nums 输入数组，p 是需要配成的对数；返回配对最大差值的最小可能值
        sort(nums.begin(), nums.end());  // 排序后最优配对只可能出现在相邻元素之间，贪心才成立
        int n = nums.size();  // 元素个数
        int l = 0, r = nums[n - 1] - nums[0] + 1;  // 答案单调：上限越大越容易凑够 p 对；r 取「最大差值 + 1」作为开区间右端
        auto check = [&](int diff) -> bool {  // 判断差值上限为 diff 时能否凑出至少 p 对
            int cnt = 0;  // 已凑出的对数
            for (int i = 0; i < n - 1; ++i) {  // 从左到右扫描相邻元素对
                if (nums[i + 1] - nums[i] <= diff) {  // nums 已升序，这一对相邻元素的差不超过上限，可以配成一对
                    ++cnt;  // 配对成功，计数加一
                    ++i;  // 每个下标只能用一次，跳过右端点继续往后找
                }  // 可配对分支结束
            }  // 扫描结束
            return cnt >= p;  // 贪心得到的就是该上限下的最大对数
        };  // lambda 定义结束
        while (l < r) {  // 在 [l, r) 上二分出第一个可行的 diff
            int mid = (l + r) >> 1;  // 中点；右移一位即向下取整除以 2
            if (check(mid)) {  // mid 可行，说明答案不超过 mid
                r = mid;  // 收缩右边界
            } else {  // mid 不可行
                l = mid + 1;  // 答案一定严格大于 mid
            }  // 二分分支结束
        }  // 二分结束
        return l;  // 循环结束时 l == r，即最小可行上限
    }  // 方法结束
};  // 题解类结束