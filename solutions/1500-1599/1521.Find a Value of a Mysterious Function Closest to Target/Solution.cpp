// 题目：1521. 找到最接近目标值的函数值（Find a Value of a Mysterious Function Closest to Target）
// 核心思路：以 i 结尾的子数组按位与只有 O(log V) 种不同取值；用集合滚动维护「以上一位置结尾的所有与值」，逐轮与 target 比较距离。
// 时间复杂度：O(n log V)，每个位置最多保留约 30 种不同的与值；空间复杂度：O(log V)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int closestToTarget(vector<int>& arr, int target) {  // arr：输入数组；target：目标值
        int ans = abs(arr[0] - target);  // 答案先取只含第一个元素的区间
        unordered_set<int> pre;  // pre：以上一个位置结尾的所有可能按位与结果
        pre.insert(arr[0]);  // 初始化：只含 arr[0] 的区间
        for (int x : arr) {  // 枚举每个元素作为区间右端点
            unordered_set<int> cur;  // cur：以当前位置结尾的所有按位与结果
            cur.insert(x);  // 只含 x 自身的区间
            for (int y : pre) {  // 把 x 与「以 i-1 结尾」的每种结果再做按位与
                cur.insert(x & y);  // 按位与只会让值变小，不同取值的个数非常少
            }  // 内层循环结束
            for (int y : cur) {  // 用本轮所有结果更新答案
                ans = min(ans, abs(y - target));  // 取与 target 距离更小的那个
            }  // 循环结束
            pre = move(cur);  // 滚动到下一轮（move 避免整体拷贝）
        }  // 外层循环结束
        return ans;  // 返回最小差值
    }  // 方法结束
};  // 类定义结束