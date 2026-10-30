// 题目：11. 盛最多水的容器（Container With Most Water）
// 思路：双指针从两端向中间收缩；面积由较矮的一侧决定，所以每次只移动较矮的指针，才可能遇到更高的边界。
// 时间复杂度：O(n)，每个下标最多被访问一次；空间复杂度：O(1)，只用常数个变量。
int min(int a, int b) {  // 手写 min，避免依赖标准库实现
    return a < b ? a : b;  // 返回两者中的较小值
}

int max(int a, int b) {  // 手写 max，用来更新当前最大面积
    return a > b ? a : b;  // 返回两者中的较大值
}

int maxArea(int* height, int heightSize) {  // height 是每条竖线的高度，heightSize 是竖线条数
    int l = 0, r = heightSize - 1;  // 左右指针分别指向最左、最右的竖线
    int ans = 0;  // 记录目前能盛的最大水量
    while (l < r) {  // 两指针未相遇，还能围成一个容器
        int t = min(height[l], height[r]) * (r - l);  // 面积 = 较矮一侧的高度 × 两指针的下标间距
        ans = max(ans, t);  // 用当前面积刷新答案
        if (height[l] < height[r]) {  // 左边更矮，它限制了容量
            ++l;  // 左指针右移，去试更高的左边，才可能得到更大面积
        } else {  // 右边更矮或两边等高
            --r;  // 右指针左移，去试更高的右边
        }
    }
    return ans;  // 返回最大面积
}
