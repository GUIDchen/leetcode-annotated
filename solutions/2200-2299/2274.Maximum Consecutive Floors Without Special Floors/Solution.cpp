// 题目：2274. 不含特殊楼层的最大连续楼层数（Maximum Consecutive Floors Without Special Floors）
// 思路：把特殊楼层排序，答案只可能出现在三段里：bottom 到首个特殊楼层前、相邻两特殊楼层之间、最后一个特殊楼层后到 top。
// 时间复杂度：O(m log m)，m 为特殊楼层数量（排序开销）；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxConsecutive(int bottom, int top, vector<int>& special) {  // bottom/top：楼层区间两端；special：特殊楼层列表
        ranges::sort(special);  // C++20 ranges 版排序，把特殊楼层升序排好才能用相邻差值切分区间
        int ans = max(special[0] - bottom, top - special.back());  // 先算两端的段长：bottom 到首个特殊楼层、末尾特殊楼层到 top
        for (int i = 1; i < special.size(); ++i) {  // 再遍历每一对相邻的特殊楼层
            ans = max(ans, special[i] - special[i - 1] - 1);  // 中间段长度要再减 1，因为两个端点本身都是特殊楼层，不能计入
        }
        return ans;  // 返回不含特殊楼层的最大连续楼层数
    }
};
