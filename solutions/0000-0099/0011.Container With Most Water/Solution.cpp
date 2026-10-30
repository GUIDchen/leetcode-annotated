// 题目：11. 盛最多水的容器（Container With Most Water）
// 思路：双指针夹逼；容量由较矮的一侧决定，因此每次只向内移动较矮的指针，放弃不可能更优的组合。
// 时间复杂度：O(n)，每个下标最多被访问一次；空间复杂度：O(1)，只用几个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxArea(vector<int>& height) {  // height 是每条竖线的高度
        int l = 0, r = height.size() - 1;  // 左右指针分别指向最左、最右的竖线
        int ans = 0;  // 记录目前能盛的最大水量
        while (l < r) {  // 两指针未相遇，说明还能围成容器
            int t = min(height[l], height[r]) * (r - l);  // 面积 = 较矮一侧高度 × 指针间距
            ans = max(ans, t);  // 用当前面积刷新答案
            if (height[l] < height[r]) {  // 左边更矮，是当前的瓶颈
                ++l;  // 移动较矮的一侧，才可能让高度变大
            } else {  // 右边更矮或等高
                --r;  // 右指针左移
            }
        }
        return ans;  // 返回最大面积
    }
};
