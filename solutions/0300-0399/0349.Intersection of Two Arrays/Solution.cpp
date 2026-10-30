// 题目：349. 两个数组的交集（Intersection of Two Arrays）
// 思路：数值范围是 0..1000，用布尔数组标记 nums1 中出现过的值；再扫 nums2，命中就收集并立刻清除标记以保证结果去重。
// 时间复杂度：O(n + m)，两个数组各扫一遍；空间复杂度：O(1)，布尔数组大小固定为 1001。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：两个输入数组；返回它们的交集（元素唯一且顺序不限）
        bool s[1001];  // 值域 0..1000，用 1001 个布尔位标记某个值是否在 nums1 中出现过
        memset(s, false, sizeof(s));  // 整体清零，初始全部标记为「未出现」
        for (int x : nums1) {  // 遍历 nums1，把出现过的值打上标记
            s[x] = true;  // 该值出现过，置为 true
        }  // 标记阶段结束
        vector<int> ans;  // 存放交集的答案数组
        for (int x : nums2) {  // 遍历 nums2，检查每个值是否在 nums1 中出现过
            if (s[x]) {  // 命中标记说明该值同时属于两个数组
                ans.push_back(x);  // 收集到答案中
                s[x] = false;  // 立刻清除标记，保证同一个值只被收集一次，实现去重
            }  // if 结束
        }  // 遍历结束
        return ans;  // 返回交集结果
    }  // 方法体结束
};  // 类定义结束