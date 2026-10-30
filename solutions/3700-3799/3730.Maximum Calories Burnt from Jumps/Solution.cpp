// 3730. 跳跃燃烧的最大卡路里 🔒 / Maximum Calories Burnt from Jumps
// 核心思路：排序后让跳跃高度在最大值与最小值之间交替，每次摆动幅度最大，平方和最大；用双指针从两端向中间构造该顺序。
// 复杂度：时间 O(n log n)，空间 O(1)（排序所需栈空间除外）。
class Solution {  // 定义 LeetCode 解法类
public:  // 公有接口
    long long maxCaloriesBurnt(vector<int>& heights) {  // 返回依次跳跃能燃烧的最大卡路里
        ranges::sort(heights);  // 升序排序，便于从两端取极值
        long long ans = 0;  // 答案累加器，用 long long 防止平方溢出
        int pre = 0;  // 上一次落脚的高度，起点高度为 0
        int r = heights.size() - 1;  // 右指针指向当前最大高度
        for (int l = 0; l < r; ++l, --r) {  // l 指向最小值，r 指向最大值，向中间收缩
            ans += 1LL * (heights[r] - pre) * (heights[r] - pre);  // 先从当前最大值跳到上一落脚点
            ans += 1LL * (heights[l] - heights[r]) * (heights[l] - heights[r]);  // 再从当前最小值跳到最大值，形成最大落差
            pre = heights[l];  // 更新落脚高度为本次的最小值
        }  // 双指针循环结束
        ans += 1LL * (heights[r] - pre) * (heights[r] - pre);  // 最后从剩余高度跳回最后一次落脚点
        return ans;  // 返回总卡路里
    }  // 方法结束
};  // 类定义结束
