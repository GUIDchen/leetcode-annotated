// 题目：303. 区域和检索 - 数组不可变（Range Sum Query - Immutable）
// 思路：构造函数里预处理前缀和数组 s，s[i] 表示前 i 个元素之和，查询时两个前缀和相减。
// 时间复杂度：构造 O(n)、每次查询 O(1)；空间复杂度：O(n)，存 n+1 个前缀和。
class NumArray {  // LeetCode 约定的题解类
public:  // 对外接口
    NumArray(vector<int>& nums) {  // 构造函数：nums 是输入数组
        int n = nums.size();  // 元素个数
        s.resize(n + 1);  // 前缀和数组需要 n+1 个位置，s[0] 天然为 0
        for (int i = 0; i < n; ++i) {  // 一次遍历构造前缀和
            s[i + 1] = s[i] + nums[i];  // 前 i+1 项之和 = 前 i 项之和 + 当前元素
        }  // 循环结束
    }  // 构造函数结束

    int sumRange(int left, int right) {  // 查询闭区间 [left, right] 的元素和
        return s[right + 1] - s[left];  // 减去前 left 项，剩下的正好是区间内的和
    }  // sumRange 结束

private:  // 私有数据成员
    vector<int> s;  // 前缀和数组，长度 n+1
};  // NumArray 类结束

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */