// 题目：2817. 限制条件下元素之间的最小绝对差（Minimum Absolute Difference Between Elements With Constraint）
// 思路：滑动窗口 + 有序集合。扫到下标 i 时把 nums[i-x] 放进 multiset，此时集合里全是与 i 下标差至少 x 的元素；在集合中找 nums[i] 的前驱和后继，二者之一即最优配对。
// 时间复杂度：O(n·log n)，每次插入与查找都是 O(log n)；空间复杂度：O(n)，有序集合最多保存 n 个元素。
class Solution {  // 题解类：有序集合维护合法前缀
public:  // 题解方法对外可见
    int minAbsoluteDifference(vector<int>& nums, int x) {  // nums：输入数组；x：下标至少要相差 x；返回满足约束的最小绝对差
        int ans = 1 << 30;  // 答案初值取 2^30，足够大且不会溢出 int
        multiset<int> s;  // 有序集合，元素自动升序，支持 lower_bound 查找与 O(log n) 插入
        for (int i = x; i < nums.size(); ++i) {  // i 从 x 开始，保证窗口里至少能放入一个合法的 j = i - x
            s.insert(nums[i - x]);  // 把下标 i-x 处的值加入窗口；窗口内元素与 i 的下标差都 >= x
            auto it = s.lower_bound(nums[i]);  // 找第一个大于等于 nums[i] 的位置，即「右侧最近的候选」
            if (it != s.end()) {  // 存在右侧候选
                ans = min(ans, *it - nums[i]);  // 右侧候选与 nums[i] 的差值参与取最小
            }
            if (it != s.begin()) {  // 左侧还有元素，说明存在比 nums[i] 小的候选
                --it;  // 回退一步，得到小于 nums[i] 的最大元素（前驱）
                ans = min(ans, nums[i] - *it);  // 前驱与 nums[i] 的差值参与取最小
            }
        }  // 窗口右移，继续处理下一个下标
        return ans;  // 返回最小绝对差
    }
};